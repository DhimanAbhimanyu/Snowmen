#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP

#include <GL/glut.h>

class Vector3f
{
	GLfloat x;
	GLfloat y;
	GLfloat z;

public:
	Vector3f(const GLfloat initX = 0, const GLfloat initY = 0,
		 const GLfloat initZ = 0)
		: x(initX), y(initY), z(initZ)
	{
	}
	Vector3f(const Vector3f &vec) : x(vec.x), y(vec.y), z(vec.z)
	{
	}

	const GLfloat getX(void) { return x; }
	const GLfloat getY(void) { return y; }
	const GLfloat getZ(void) { return z; }

	void setX(const GLfloat newX) { x = newX; }
	void setY(const GLfloat newY) { y = newY; }
	void setZ(const GLfloat newZ) { z = newZ; }

	float size() const;

	static float angleRad(const Vector3f &vec1, const Vector3f &vec2);

	float operator *(const Vector3f &vec) const;
	Vector3f operator -(const Vector3f &vec1) const;
	Vector3f &operator =(const Vector3f& vec1);
	Vector3f &operator -=(const Vector3f& vec1);

	Vector3f rotate(Vector3f vec, const float &theta) const;
};

#endif		// VECTOR3F_HPP
