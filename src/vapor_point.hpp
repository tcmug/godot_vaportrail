#pragma once

#include <godot_cpp/variant/vector3.hpp>

using namespace godot;

#define LERP(a, b, t) (a + (b - a) * t)

class VaporPoint {
public:
	Vector3 source_position;
	Vector3 position;

	Vector3 direction;
	Vector3 up;

	float size;

	void lerp(const VaporPoint &other, double t) {
		position = source_position.lerp(other.position, t);
	}

	VaporPoint xlerp(const VaporPoint &target, double t) const {
		VaporPoint point;
		point.position = position.lerp(target.position, t);
		point.size = LERP(size, target.size, t);
		point.up = up.lerp(target.up, t);
		point.direction = direction.lerp(target.direction, t);
		return point;
	}
};
