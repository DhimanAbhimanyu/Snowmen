#include <iostream>
#include <cmath>
#include <GL/glut.h>

#include "vector3f.hpp"
#include "consts.hpp"

float Vector3f::size() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3f::operator *(const Vector3f &vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

float Vector3f::angleRad(const Vector3f &vec1, const Vector3f &vec2)
{
	return acos((vec1 * vec2) / (vec1.size() * vec2.size()));
}

Vector3f Vector3f::operator -(const Vector3f &vec1) const
{
	return Vector3f(x - vec1.x, y - vec1.y, z - vec1.z);
}

Vector3f &Vector3f::operator =(const Vector3f& vec1)
{
	x = vec1.x;
	y = vec1.y;
	z = vec1.z;

	return *this;
}

Vector3f &Vector3f::operator -=(const Vector3f& vec1)
{
	x -= vec1.x;
	y -= vec1.y;
	z -= vec1.z;

	return *this;
}

Vector3f Vector3f::rotate(Vector3f vec, const float &theta) const
{
	float angle = (float)(theta * PIby180);

	float xr = (cos(angle) + (vec.x * vec.x) * (1 - cos(angle))) * x;
	xr += (vec.x * vec.y * (1 - cos(angle)) - vec.z * sin(angle)) * y;
	xr += (vec.x * vec.z * (1 - cos(angle)) + vec.y * sin(angle)) * z;

	float yr = (vec.y * vec.x * (1 - cos(angle)) + vec.z * sin(angle)) * x;
	yr += (cos(angle) + vec.y * vec.y * (1 - cos(angle))) * y;
	yr += (vec.y * vec.z * (1 - cos(angle)) - vec.x * sin(angle)) * z;

	float zr = (vec.z * vec.x * (1 - cos(angle)) - vec.y * sin(angle)) * x;
	zr += (vec.z * vec.y * (1 - cos(angle)) + vec.x * sin(angle)) * y;
	zr += (cos(angle) + vec.z * vec.z * (1 - cos(angle))) * z;

	return Vector3f(xr, yr, zr);
}
