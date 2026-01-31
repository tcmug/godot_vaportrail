
#include "godot_cpp/classes/global_constants.hpp"
#include "vapor_trail.hpp"

#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void VaporTrail::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_material", "new_material"), &VaporTrail::set_material);
	ClassDB::bind_method(D_METHOD("get_material"), &VaporTrail::get_material);
	ClassDB::bind_method(D_METHOD("set_curve", "new_curve"), &VaporTrail::set_curve);
	ClassDB::bind_method(D_METHOD("get_curve"), &VaporTrail::get_curve);
	ClassDB::bind_method(D_METHOD("set_gradient", "new_gradient"), &VaporTrail::set_gradient);
	ClassDB::bind_method(D_METHOD("get_gradient"), &VaporTrail::get_gradient);
	ClassDB::bind_method(D_METHOD("set_geometry_root", "nodepath"), &VaporTrail::set_geometry_root);
	ClassDB::bind_method(D_METHOD("get_geometry_root"), &VaporTrail::get_geometry_root);
	ClassDB::bind_method(D_METHOD("set_num_points", "value"), &VaporTrail::set_num_points);
	ClassDB::bind_method(D_METHOD("get_num_points"), &VaporTrail::get_num_points);
	ClassDB::bind_method(D_METHOD("set_randomness", "value"), &VaporTrail::set_randomness);
	ClassDB::bind_method(D_METHOD("get_randomness"), &VaporTrail::get_randomness);
	ClassDB::bind_method(D_METHOD("set_size", "value"), &VaporTrail::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &VaporTrail::get_size);
	ClassDB::bind_method(D_METHOD("set_minimum_onscreen_size", "value"), &VaporTrail::set_minimum_onscreen_size);
	ClassDB::bind_method(D_METHOD("get_minimum_onscreen_size"), &VaporTrail::get_minimum_onscreen_size);
	ClassDB::bind_method(D_METHOD("set_uv_shift", "value"), &VaporTrail::set_uv_shift);
	ClassDB::bind_method(D_METHOD("get_uv_shift"), &VaporTrail::get_uv_shift);
	ClassDB::bind_method(D_METHOD("set_uv_alignment", "value"), &VaporTrail::set_uv_alignment);
	ClassDB::bind_method(D_METHOD("get_uv_alignment"), &VaporTrail::get_uv_alignment);
	ClassDB::bind_method(D_METHOD("set_update_interval", "value"), &VaporTrail::set_update_interval);
	ClassDB::bind_method(D_METHOD("get_update_interval"), &VaporTrail::get_update_interval);
	//	ClassDB::bind_method(D_METHOD("offset_mesh_points", "amount"), &VaporTrail::offset_mesh_points);

	ClassDB::bind_method(D_METHOD("set_alignment", "value"), &VaporTrail::set_alignment);
	ClassDB::bind_method(D_METHOD("get_alignment"), &VaporTrail::get_alignment);

	ADD_GROUP("Config", "config");
	ADD_GROUP("Visual", "visual");

	ClassDB::add_property("VaporTrail", PropertyInfo(Variant::INT, "config/alignment", PROPERTY_HINT_ENUM, "Camera,X,Y,Z"), "set_alignment", "get_alignment");
	ClassDB::add_property("VaporTrail", PropertyInfo(Variant::NODE_PATH, "config/geometry_nodepath"), "set_geometry_root", "get_geometry_root");
	ClassDB::add_property("VaporTrail", PropertyInfo(Variant::INT, "config/num_points", PROPERTY_HINT_RANGE, "2,10000,1"), "set_num_points", "get_num_points");
	ClassDB::add_property("VaporTrail", PropertyInfo(Variant::FLOAT, "config/update_interval"), "set_update_interval", "get_update_interval");
	ClassDB::add_property("VaporTrail", PropertyInfo(Variant::FLOAT, "config/randomness"), "set_randomness", "get_randomness");
	ClassDB::add_property("VaporTrail", PropertyInfo(Variant::OBJECT, "visual/material", PROPERTY_HINT_RESOURCE_TYPE, "Material"), "set_material", "get_material");
	ClassDB::add_property("VaporTrail", PropertyInfo(Variant::FLOAT, "visual/size", PROPERTY_HINT_RANGE, "0.0,100.0,0.01"), "set_size", "get_size");
	ClassDB::add_property("VaporTrail", PropertyInfo(Variant::OBJECT, "visual/size_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_curve", "get_curve");
	ClassDB::add_property("VaporTrail", PropertyInfo(Variant::FLOAT, "visual/minimum_onscreen_size", PROPERTY_HINT_RANGE, "0.0,100.0,0.01"), "set_minimum_onscreen_size", "get_minimum_onscreen_size");
	ClassDB::add_property("VaporTrail", PropertyInfo(Variant::OBJECT, "visual/color_gradient", PROPERTY_HINT_RESOURCE_TYPE, "Gradient"), "set_gradient", "get_gradient");
	ClassDB::add_property("VaporTrail", PropertyInfo(Variant::FLOAT, "visual/uv_shift", PROPERTY_HINT_RANGE, "-100.0,100.0,0.001"), "set_uv_shift", "get_uv_shift");
	ClassDB::add_property("VaporTrail", PropertyInfo(Variant::INT, "visual/uv_alignment", PROPERTY_HINT_ENUM, "Plain,Distance"), "set_uv_alignment", "get_uv_alignment");
}

bool VaporTrail::_set(const StringName &p_name, const Variant &p_value) {
	// Migration from old config to new.
	if (p_name == StringName("num_points")) {
		set_num_points(p_value);
		return true;
	}
	if (p_name == StringName("size")) {
		set_size(p_value);
		return true;
	}
	if (p_name == StringName("geometry_nodepath")) {
		set_geometry_root(p_value);
		return true;
	}
	if (p_name == StringName("update_interval")) {
		set_update_interval(p_value);
		return true;
	}
	if (p_name == StringName("material")) {
		set_material(p_value);
		return true;
	}
	if (p_name == StringName("curve")) {
		set_curve(p_value);
		return true;
	}
	if (p_name == StringName("gradient")) {
		set_gradient(p_value);
		return true;
	}
	if (p_name == StringName("noise_scale")) {
		set_randomness(p_value);
		return true;
	}
	if (p_name == StringName("uv_shift")) {
		set_uv_shift(p_value);
		return true;
	}
	if (p_name == StringName("uv_alignment")) {
		set_uv_alignment(p_value);
		return true;
	}
	return false;
}

void VaporProps::_bind_methods() {
}
