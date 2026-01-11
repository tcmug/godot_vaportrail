#pragma once

#include <godot_cpp/variant/vector3.hpp>

using namespace godot;

class VaporTrailPoint {
public:
	Vector3 center;
	Vector3 direction;
	Vector3 up;
	float size = 0.0;
};
