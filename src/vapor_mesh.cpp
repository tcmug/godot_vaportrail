#include "vapor_mesh.hpp"
#include "vapor_point.hpp"
// #include <godot_cpp/core/class_db.hpp>

#include <cassert>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/material.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

using namespace godot;

VaporMesh::VaporMesh() {
	fade_away_timer = 0.0;
	elapsed = 0.0;
	num_points = 0;
	total_elapsed = 0.0;
	trail_points = nullptr;
}

void VaporMesh::_bind_methods() {
}

void VaporMesh::initialize_arrays() {
	if (!props.is_valid()) {
		return;
	}

	// Trigger first emit immediately
	elapsed = props->update_interval;

	vertex_buffer.resize(num_points * 2);
	normal_buffer.resize(num_points * 2);
	tangent_buffer.resize(num_points * 2 * 4);
	uv_buffer.resize(num_points * 2);
	color_buffer.resize(num_points * 2);

	// Initialize points.
	if (trail_points) {
		delete[] trail_points;
	}
	trail_points = new VaporPoint[num_points];
	Transform3D emitter_transform = props->emitter->get_global_transform();
	for (int i = 0; i < num_points; i++) {
		Vector3 origin = emitter_transform.origin;
		trail_points[i].position = origin;
		trail_points[i].direction.zero();
		trail_points[i].up.zero();
		trail_points[i].size = props->size;
	}
}

void VaporMesh::offset_mesh_points(Vector3 offset) {
	if (!props.is_valid()) {
		return;
	}

	//Transform3D emitter_transform = props->emitter->get_global_transform();
	//	props->emitter_transform.origin += offset;
	//for (int i = 0; i < num_points; i++) {
	//		trail_points[i].center += offset;
	//	}
}

VaporMesh::~VaporMesh() {
	delete[] trail_points;
}

void VaporMesh::_ready() {
	if (!props.is_valid()) {
		UtilityFunctions::push_error("Spawned VaporTrailMesh without props, freeing");
		queue_free();
		return;
	}

	num_points = props->num_points;

	ArrayMesh *mesh = memnew(ArrayMesh);
	set_mesh(Ref(mesh));

	Transform3D emitter_transform = props->emitter->get_global_transform();
	vertex_buffer.fill(emitter_transform.origin);

	geometry.resize(ArrayMesh::ARRAY_MAX);
	geometry[ArrayMesh::ARRAY_VERTEX] = vertex_buffer;
	geometry[ArrayMesh::ARRAY_NORMAL] = normal_buffer;
	geometry[ArrayMesh::ARRAY_TANGENT] = tangent_buffer;
	geometry[ArrayMesh::ARRAY_TEX_UV] = uv_buffer;
	if (props->gradient.is_valid()) {
		geometry[ArrayMesh::ARRAY_COLOR] = color_buffer;
	}

	initialize_arrays();
}

float calculate_scaled_size(
		float size, // Size of the point in 3D space
		float d, // Distance from camera to point
		float fovY, // Camera's vertical FOV (radians)
		float screen_height, // Screen height (pixels)
		float min_size_pixels // Minimum size on screen (pixels)
) {
	float s_screen = (size * screen_height) / (d * tan(fovY / 2.0f));
	if (s_screen < min_size_pixels) {
		return (min_size_pixels * d * tan(fovY / 2.0f)) / screen_height;
	} else {
		return size;
	}
}

void VaporMesh::_process(double delta) {
	if (!props->emitter) {
		// Handle removal
		props->size = 0.0;
		fade_away_timer += delta;
		if (fade_away_timer >= num_points * props->update_interval) {
			queue_free();
		}
	}

	double uv_shift = props->uv_shift;
	double update_interval = props->update_interval;

	Viewport *viewport = get_viewport();

	if (!viewport) {
		UtilityFunctions::push_error("No viewport, try setting geometry nodepath?");
		set_process(false);
		return;
	}

	Camera3D *camera = viewport->get_camera_3d();

	if (!camera) {
		UtilityFunctions::push_error("No camera, try setting geometry nodepath?");
		set_process(false);
		return;
	}

	Transform3D previous_transform = props->emitter_transform;
	if (props->emitter) {
		props->emitter_transform = props->emitter->get_global_transform();
	}

	Vector3 latest_emitter_position = props->emitter_transform.origin;
	Transform3D inverse_transform = props->emitter_transform.inverse();
	Vector3 new_direction_vector = previous_transform.origin.direction_to(latest_emitter_position);

	if (new_direction_vector.length_squared() > 0.0) {
		latest_direction_vector = new_direction_vector;
	}

	int num_vertices = vertex_buffer.size();
	elapsed += delta;
	total_elapsed += delta;

	if (elapsed >= update_interval) {
		elapsed -= update_interval;
		memmove(&trail_points[1], trail_points, sizeof(VaporPoint) * (num_points - 1));
		// Initialize new point size;
		float spawn_size = props->size;
		if (props->noise_scale != 0.0) {
			spawn_size *= UtilityFunctions::randf_range(1.0 - props->noise_scale, 1.0 + props->noise_scale);
		}
		trail_points[0].size = spawn_size;
	}

	double update_fraction = elapsed / update_interval;

	// Update active point.
	trail_points[0].position = latest_emitter_position;
	trail_points[0].direction = latest_direction_vector;
	if (props->alignment > 0 && props->alignment < 4) {
		trail_points[0].up = inverse_transform.basis[props->alignment - 1];
	}

	Viewport *vp = camera->get_viewport();
	int viewport_height = vp->get_visible_rect().size.y;

	float fov = camera->get_fov(); // degrees
	float fov_rad = Math::deg_to_rad(fov);

	// Transform points to the vertex buffer.
	const Vector3 camera_position = to_local(camera->get_global_position());

	int vi = 0, ci = 0, ni = 0, uvi = 0, ti = 0;

	// These are for visibility AABB:
	Vector3 min_pos = Vector3(10000, 10000, 10000);
	Vector3 max_pos = Vector3(-10000, -10000, -10000);

	// Since points are fixed in space, animate uv (x) over the update interval.
	double uv_adjustment = (total_elapsed * uv_shift);

	for (int i = 0; i < num_points; i++) {
		VaporPoint point;

		if (i < 1) {
			point = trail_points[i];
		} else {
			point = trail_points[i].lerp(trail_points[i - 1], update_fraction);
		}

		// -1 ensures the last point sampled isn't somewhere beyond num_points.
		double fi = double(i) / (num_points - 1);

		Vector3 normal = point.position.direction_to(camera_position);
		Vector3 orientation;

		if (props->alignment == 0) {
			// Normalize for keeping sizes consistent.
			orientation = normal.cross(point.direction).normalized();
		} else {
			orientation = point.up;
		}

		Vector3 tangent = point.direction;
		Vector3 to_cam = camera_position - point.position;
		float dist = to_cam.length();

		double sz = point.size;
		sz = calculate_scaled_size(sz, dist, fov_rad, viewport_height, props->minimum_onscreen_size);
		if (props->curve.is_valid()) {
			assert(fi >= 0 && fi < num_points);
			sz *= props->curve->sample_baked(fi);
		}

		Vector3 edge_vector = orientation * (sz * 0.5);
		const Vector3 &position = point.position;

		// Keep track of min and max points.
		min_pos.x = min(position.x, min_pos.x);
		min_pos.y = min(position.y, min_pos.y);
		min_pos.z = min(position.z, min_pos.z);
		max_pos.x = max(position.x, max_pos.x);
		max_pos.y = max(position.y, max_pos.y);
		max_pos.z = max(position.z, max_pos.z);

		vertex_buffer[vi++] = position + edge_vector;
		vertex_buffer[vi++] = position - edge_vector;

		normal_buffer[ni++] = normal;
		normal_buffer[ni++] = normal;

		tangent_buffer[ti++] = tangent.x;
		tangent_buffer[ti++] = tangent.y;
		tangent_buffer[ti++] = tangent.z;
		tangent_buffer[ti++] = 1;
		tangent_buffer[ti++] = tangent.x;
		tangent_buffer[ti++] = tangent.y;
		tangent_buffer[ti++] = tangent.z;
		tangent_buffer[ti++] = 1;

		double ux = fi + uv_adjustment;
		uv_buffer[uvi++] = Vector2(ux, 0);
		uv_buffer[uvi++] = Vector2(ux, 1);

		if (props->gradient.is_valid()) {
			// Two vertices with same color.
			Color color = props->gradient->sample(fi);
			color_buffer[ci++] = color;
			color_buffer[ci++] = color;
		}
	}

	set_custom_aabb(AABB(min_pos, max_pos - min_pos));

	Ref<ArrayMesh> mesh = get_mesh();
	if (mesh.is_valid()) {
		mesh->clear_surfaces();
		geometry[ArrayMesh::ARRAY_VERTEX] = vertex_buffer;
		geometry[ArrayMesh::ARRAY_NORMAL] = normal_buffer;
		geometry[ArrayMesh::ARRAY_TANGENT] = tangent_buffer;
		geometry[ArrayMesh::ARRAY_TEX_UV] = uv_buffer;
		if (props->gradient.is_valid()) {
			geometry[ArrayMesh::ARRAY_COLOR] = color_buffer;
		}
		mesh->add_surface_from_arrays(Mesh::PrimitiveType::PRIMITIVE_TRIANGLE_STRIP, geometry);
	} else {
		UtilityFunctions::push_error("No mesh");
	}

	Ref<ShaderMaterial> material = get_material_override();
	if (material.is_valid()) {
		material->set_shader_parameter("MAX_VERTICES", float(num_vertices));
		material->set_shader_parameter("SPAWN_INTERVAL_SECONDS", float(update_interval));
	}
}
