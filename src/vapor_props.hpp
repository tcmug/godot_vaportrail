#pragma once

#include "godot_cpp/classes/curve.hpp"
#include "godot_cpp/classes/gradient.hpp"
#include "godot_cpp/classes/material.hpp"
#include "vapor_trail.hpp"
#include <godot_cpp/variant/vector3.hpp>

namespace godot {

class VaporTrail;

class VaporProps : public RefCounted {
	GDCLASS(VaporProps, RefCounted)

protected:
	static void _bind_methods();

public:
	int alignment = 0; // 0 = Camera, 1 = X, 2 = Y, 3 = Z.
	int num_points = 200;
	float noise_scale = 0.0;
	float size = 0.0;
	float minimum_onscreen_size = 0.0;

	Transform3D emitter_transform;
	VaporTrail *emitter = nullptr;

	double update_interval = 0.1;
	double uv_shift = 0.0;
	int uv_alignment = 0; // 0 = Plain (linear), 1 = Distance-based

	Ref<Gradient> gradient;
	Ref<Curve> curve;
	Ref<Material> material;
};
} //namespace godot
