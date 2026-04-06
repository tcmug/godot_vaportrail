#pragma once

#include "vapor_props.hpp"
#include <godot_cpp/classes/curve.hpp>
#include <godot_cpp/classes/gradient.hpp>
#include <godot_cpp/classes/material.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/packed_vector3_array.hpp>

namespace godot {

class VaporProps;

class VaporMesh;

class VaporTrail : public Node3D {
	GDCLASS(VaporTrail, Node3D)

private:
	Ref<VaporProps> props;
	VaporMesh *vapor_mesh;
	NodePath geometry_root;

protected:
	static void _bind_methods();

public:
	VaporTrail();
	~VaporTrail();

	void _ready() override;

	bool get_emitting() const;
	void set_emitting(bool value);

	NodePath get_geometry_root() const;
	void set_geometry_root(NodePath nodepath);

	Ref<Material> get_material() const;
	void set_material(const Ref<Material> material);

	int get_num_points() const;
	void set_num_points(int value);

	float get_size() const;
	void set_size(float value);

	float get_minimum_onscreen_size() const;
	void set_minimum_onscreen_size(float value);

	int get_alignment() const;
	void set_alignment(int new_mode);

	Ref<Curve> get_curve() const;
	void set_curve(const Ref<Curve> new_curve);

	Ref<Curve> get_time_curve() const;
	void set_time_curve(const Ref<Curve> new_curve);

	Ref<Gradient> get_time_color_gradient() const;
	void set_time_color_gradient(const Ref<Gradient> new_gradient);

	float get_current_time() const;
	void set_current_time(float value);

	Ref<Gradient> get_gradient() const;
	void set_gradient(const Ref<Gradient> new_gradient);

	float get_randomness() const;
	void set_randomness(float value);

	double get_uv_shift() const;
	void set_uv_shift(double value);
	int get_uv_alignment() const;
	void set_uv_alignment(int value);

	double get_update_interval() const;
	void set_update_interval(double value);

	Node3D *get_mesh_node();

protected:
	virtual bool _set(const StringName &p_name, const Variant &p_value);
};
} //namespace godot
