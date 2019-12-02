#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <cmath>
#include <assert.h>

#include <GL/freeglut.h>
#include <GL/glut.h>

/*
  A class for wrapping up (x, y, z), which can be the co-ordinates
  for a point or a vector too.
 */
class Vector3f
{
protected:
	// Data members
	GLfloat x;	// X component
	GLfloat y;	// Y component
	GLfloat z;	// Z component

public:
	// Construct an instance from 3 floats
	Vector3f(const GLfloat initX = 0, const GLfloat initY = 0,
		 const GLfloat initZ = 0) : x(initX), y(initY), z(initZ)
	{
	}

	// Construct an instance from by copying over
	// the values from another instance
	Vector3f(const Vector3f &vec) : x(vec.x), y(vec.y), z(vec.z)
	{
	}

	// Get the values of the data members
	const GLfloat getX(void) const { return x; }
	const GLfloat getY(void) const { return y; }
	const GLfloat getZ(void) const { return z; }

	// Set the values of the data members
	void setX(const GLfloat newX) { x = newX; }
	void setY(const GLfloat newY) { y = newY; }
	void setZ(const GLfloat newZ) { z = newZ; }

	float sizeSquared() const
	{
		return x * x + y * y + z * z;
	}

	// Get the size (or length) of the instance,
	// assuming it is a vector
	float size() const
	{
		return sqrt(sizeSquared());
	}

	// Calculate the angle between two instances
	static float angleRad(const Vector3f &vec1, const Vector3f &vec2)
	{
		return acos((vec1 * vec2) / (vec1.size() * vec2.size()));
	}

	// Return the size (or the length) of this vector
	float operator *(const Vector3f &vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	// Return an instance created by multiplying this vector by a float
	Vector3f operator *(float multi) const
	{
		return Vector3f(x * multi, y * multi, z * multi);
	}

	// Return an instance created by dividing this vector by a float
	Vector3f operator /(float multi) const
	{
		assert(multi != 0);
		return Vector3f(x / multi, y / multi, z / multi);
	}

	// Return an instance of Vector3f created by
	// the subtracting this instance from a passed instance
	Vector3f operator -(const Vector3f &vec1) const
	{
		return Vector3f(x - vec1.x, y - vec1.y, z - vec1.z);
	}

	// Set the data members of this instance to
	// the data members of a passed instance
	Vector3f& operator =(const Vector3f& vec1)
	{
		x = vec1.x;
		y = vec1.y;
		z = vec1.z;

		return *this;
	}

	// Add the data members of a passed instance
	// from the data members of this instance
	Vector3f& operator +=(const Vector3f& vec1)
	{
		x += vec1.x;
		y += vec1.y;
		z += vec1.z;

		return *this;
	}

	// Subract the data members of a passed instance
	// from the data members of this instance
	Vector3f& operator -=(const Vector3f& vec1)
	{
		x -= vec1.x;
		y -= vec1.y;
		z -= vec1.z;

		return *this;
	}

	// Return a reference to this instance after multiplying it by a float
	Vector3f& operator *=(float multi)
	{
		x *= multi;
		y *= multi;
		z *= multi;

		return *this;
	}

	// Return a reference to this instance after dividing it by a float
	Vector3f& operator /=(float div)
	{
		assert(div != 0);

		x /= div;
		y /= div;
		z /= div;

		return *this;
	}

	// Rotate this instance by angle radians,
	// towards the passed vector
	void rotate(Vector3f vec, const float &angle)
	{
		// Calculate the x-component of the vector
		float xr = (cos(angle) + (vec.x * vec.x)
			    * (1 - cos(angle))) * x
			+ (vec.x * vec.y * (1 - cos(angle))
			   - vec.z * sin(angle)) * y
			+ (vec.x * vec.z * (1 - cos(angle))
			   + vec.y * sin(angle)) * z;

		// Calculate the y-component of the vector
		float yr = (vec.y * vec.x * (1 - cos(angle))
			    + vec.z * sin(angle)) * x
			+ (cos(angle) + vec.y * vec.y * (1 - cos(angle))) * y
			+ (vec.y * vec.z * (1 - cos(angle))
			   - vec.x * sin(angle)) * z;

		// Calculate the z-component of the vector
		float zr = (vec.z * vec.x * (1 - cos(angle))
			    - vec.y * sin(angle)) * x
			+ (vec.z * vec.y * (1 - cos(angle))
			   + vec.x * sin(angle)) * y
			+ (cos(angle) + vec.z * vec.z * (1 - cos(angle))) * z;

		// Update this instance
		x = xr, y = yr, z = zr;
	}

	// Return the vector normalized
	Vector3f normalize(void) const
	{
		float sz = size();
		if (sz != 0)
			return *this / sz;
		else
			return *this;
	}
};

/*
  A class for wrapping up (x, y, z, w)
  for a point or a vector too.
 */
class Vector4f : public Vector3f {
protected:
	// Data members
	GLfloat w;	// W component

public:
	// Construct an instance from 3 floats
	Vector4f(const GLfloat initX = 0, const GLfloat initY = 0,
		 const GLfloat initZ = 0, const GLfloat initW = 0)
		: Vector3f(initX, initY, initZ), w(initW)
	{
	}

	// Construct an instance from by copying over
	// the values from another instance
	Vector4f(const Vector4f &vec) : Vector3f(vec), w(vec.w)
	{
	}

	// Get the values of the data members
	const GLfloat getW(void) const { return w; }

	// Set the values of the data members
	void setW(const GLfloat newW) { w = newW; }

	// Get the size (or length) of the instance,
	// assuming it is a vector
	float size() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	// Return an instance created by multiplying this vector by a float
	Vector4f operator *(float multi) const
	{
		return Vector4f(x * multi, y * multi, z * multi, w * multi);
	}

	// Return an instance created by dividing this vector by a float
	Vector4f operator /(float multi) const
	{
		assert(multi != 0);
		return Vector4f(x / multi, y / multi, z / multi, w / multi);
	}

	// Return an instance of Vector4f created by
	// the subtracting this instance from a passed instance
	Vector4f operator -(const Vector4f &vec1) const
	{
		return Vector4f(x - vec1.x, y - vec1.y, z - vec1.z, w - vec1.w);
	}

	// Set the data members of this instance to
	// the data members of a passed instance
	Vector4f& operator =(const Vector4f& vec1)
	{
		x = vec1.x;
		y = vec1.y;
		z = vec1.z;
		w = vec1.w;

		return *this;
	}

	// Add the data members of a passed instance
	// from the data members of this instance
	Vector4f& operator +=(const Vector4f& vec1)
	{
		x += vec1.x;
		y += vec1.y;
		z += vec1.z;
		w += vec1.w;

		return *this;
	}

	// Subract the data members of a passed instance
	// from the data members of this instance
	Vector4f& operator -=(const Vector4f& vec1)
	{
		x -= vec1.x;
		y -= vec1.y;
		z -= vec1.z;
		w -= vec1.w;

		return *this;
	}

	// Return a reference to this instance after multiplying it by a float
	Vector4f& operator *=(float multi)
	{
		x *= multi;
		y *= multi;
		z *= multi;
		w *= multi;

		return *this;
	}

	// Return a reference to this instance after dividing it by a float
	Vector4f& operator /=(float div)
	{
		assert(div != 0);

		x /= div;
		y /= div;
		z /= div;
		w /= div;

		return *this;
	}

	// Return the vector normalized
	Vector4f normalize(void) const
	{
		float sz = size();
		if (sz != 0)
			return *this / sz;
		else
			return *this;
	}
};

#endif
