#pragma once

#include <godot_cpp/variant/vector3.hpp>

using namespace godot;

#define LERP(a, b, t) (a + (b - a) * t)

class VaporPoint {
public:
	Vector3 position;
	Vector3 direction;
	Vector3 up;

	float size;

	VaporPoint lerp(const VaporPoint &target, double t) const {
		VaporPoint point;
		point.position = position.lerp(target.position, t);
		point.size = LERP(size, target.size, t);
		point.up = up.lerp(target.up, t);
		point.direction = direction.lerp(target.direction, t);
		return point;
	}
};
