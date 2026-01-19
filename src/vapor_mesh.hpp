#pragma once

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/variant/packed_color_array.hpp>
#include <godot_cpp/variant/packed_vector3_array.hpp>

#include <vapor_point.hpp>
#include <vapor_trail.hpp>

namespace godot {

class VaporMesh : public MeshInstance3D {
	GDCLASS(VaporMesh, MeshInstance3D)

	friend class VaporTrail;

private:
	double elapsed;
	double total_elapsed;
	double fade_away_timer;

	Ref<VaporProps> props;

	Array geometry;
	Vector3 direction_vector;

	PackedVector3Array vertex_buffer;
	PackedVector3Array normal_buffer;
	PackedFloat32Array tangent_buffer;
	PackedVector2Array uv_buffer;
	PackedColorArray color_buffer;

	int num_points;
	VaporPoint *trail_points;

protected:
	static void _bind_methods();
	void initialize_arrays();
	void offset_mesh_points(Vector3 offset);

public:
	VaporMesh();
	~VaporMesh();

	void _ready() override;
	void _process(double delta) override;
};
} //namespace godot
