#pragma once

#include "PluginSettings.h"
#include <iostream>

struct PLUGIN_API Vector3
{
public:
	Vector3(float _x, float _y, float _z);
	Vector3(float _x, float _y);
	Vector3(float _x);
	Vector3();

	float x, y, z;

	friend std::ostream& operator<<(std::ostream& out, const Vector3& vec);
};