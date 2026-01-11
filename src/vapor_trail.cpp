#include "vapor_trail.hpp"
#include "vapor_trail_mesh.hpp"

#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

VaporTrail::VaporTrail() {
	props = Ref<VaporProps>(memnew(VaporProps));
	props->emitter = this;
}

VaporTrail::~VaporTrail() {
	props->emitter = nullptr;
}

int VaporTrail::get_alignment() const {
	return props->alignment;
}

void VaporTrail::set_alignment(int new_mode) {
	props->alignment = new_mode;
}

double VaporTrail::get_update_interval() const {
	return props->update_interval;
}

void VaporTrail::set_update_interval(double value) {
	props->update_interval = value;
}

void VaporTrail::set_geometry_root(NodePath nodepath) {
	geometry_root = nodepath;
}

NodePath VaporTrail::get_geometry_root() const {
	return geometry_root;
}

void VaporTrail::set_material(Ref<Material> new_material) {
	props->material = new_material;
}

Ref<Material> VaporTrail::get_material() const {
	return props->material;
}

void VaporTrail::set_curve(Ref<Curve> new_curve) {
	props->curve = new_curve;
}

Ref<Curve> VaporTrail::get_curve() const {
	return props->curve;
}

void VaporTrail::set_gradient(Ref<Gradient> new_gradient) {
	props->gradient = new_gradient;
}

Ref<Gradient> VaporTrail::get_gradient() const {
	return props->gradient;
}

void VaporTrail::set_num_points(int value) {
	props->num_points = value;
}

int VaporTrail::get_num_points() const {
	return props->num_points;
}

void VaporTrail::set_randomness(float value) {
	props->noise_scale = value;
}

float VaporTrail::get_randomness() const {
	return props->noise_scale;
}

void VaporTrail::set_size(float value) {
	props->size = value;
}

float VaporTrail::get_size() const {
	return props->size;
}

void VaporTrail::set_minimum_onscreen_size(float value) {
	props->minimum_onscreen_size = value;
}

float VaporTrail::get_minimum_onscreen_size() const {
	return props->minimum_onscreen_size;
}

void VaporTrail::set_uv_shift(double value) {
	props->uv_shift = value;
}

double VaporTrail::get_uv_shift() const {
	return props->uv_shift;
}

void VaporTrail::_ready() {
	Node *geometry_root_node = get_node_or_null(geometry_root);
	if (!geometry_root_node) {
		geometry_root_node = this;
	}
	VaporTrailMesh *trail_mesh = memnew(VaporTrailMesh);
	trail_mesh->props = props;
	trail_mesh->set_material_override(props->material);
	trail_mesh->set_as_top_level(true);
	geometry_root_node->call_deferred("add_child", trail_mesh);
}
