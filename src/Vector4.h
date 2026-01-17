#pragma once
#include "Vector3.h"

//most likely used for color
class Vector4	{
public:
	Vector4(void) {
		x = y = z = w = 0.0f;
	}
	~Vector4(void){}
	Vector4(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector3 ToVector3() {
		return Vector3(x, y, z);
	}

	float x;
	float y;
	float z;
	float w;
};
	