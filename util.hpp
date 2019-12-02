#ifndef UTIL_HPP
#define UTIL_HPP

class Vertex3f
{
	GLfloat x;
	GLfloat y;
	GLfloat z;

public:
	Vertex3f(const GLfloat initX = 0, const GLfloat initY = 0,
		 const GLfloat initZ = 0)
		: x(initX), y(initY), z(initZ)
	{
	}

	const GLfloat getX(void) { return x; }
	const GLfloat getY(void) { return y; }
	const GLfloat getZ(void) { return z; }

	void setX(const GLfloat newX) { x = newX; }
	void setY(const GLfloat newY) { y = newY; }
	void setZ(const GLfloat newZ) { z = newZ; }
};

class Color3f
{
	GLfloat r;
	GLfloat g;
	GLfloat b;

public:
	Color3f(const GLfloat initR = 0, const GLfloat initG = 0,
		const GLfloat initB = 0)
		: r(initR), g(initG), b(initB)
	{
	}

	const GLfloat getR(void) { return r; }
	const GLfloat getG(void) { return g; }
	const GLfloat getB(void) { return b; }

	void setR(const GLfloat newR) { r = newR; }
	void setG(const GLfloat newG) { g = newG; }
	void setB(const GLfloat newB) { b = newB; }
};

#endif		// UTIL_HPP
