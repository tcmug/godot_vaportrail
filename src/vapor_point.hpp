#pragma once

#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/vector3.hpp>

using namespace godot;

#define LERP(a, b, t) (a + (b - a) * t)

class VaporPoint {
public:
	Vector3 position;
	Vector3 direction;
	Vector3 up;

	float u;
	float size;
	float time_curve_multiplier;
	Color time_color_multiplier;

	VaporPoint lerp(const VaporPoint &target, double t) const {
		VaporPoint point;
		point.position = position.lerp(target.position, t);
		point.size = LERP(size, target.size, t);
		point.up = up.lerp(target.up, t);
		point.direction = direction.lerp(target.direction, t);
		point.u = LERP(u, target.u, t);
		point.time_curve_multiplier = LERP(time_curve_multiplier, target.time_curve_multiplier, t);
		point.time_color_multiplier = time_color_multiplier.lerp(target.time_color_multiplier, t);
		return point;
	}
};
