#include "Vector.h"

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3::Vector3(float _x, float _y)
{
	x = _x;
	y = _y;
	z = 0.f;
}

Vector3::Vector3(float _x)
{
	x = _x;
	y = 0.f;
	z = 0.f;
}

Vector3::Vector3()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

std::ostream& operator<<(std::ostream& out, const Vector3& vec)
{
	out << "Vector3: ";
	out << "( " << vec.x << ", " << vec.y << ", " << vec.z << " )" << std::endl;

	return out;
}