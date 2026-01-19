#pragma once

#include <godot_cpp/variant/vector3.hpp>

using namespace godot;

class VaporPoint {
public:
	Vector3 source_position;
	Vector3 position;

	Vector3 direction;
	Vector3 up;

	float size = 0.0;

	void lerp(const VaporPoint &other, double t) {
		position = source_position.lerp(other.position, t);
	}
};
