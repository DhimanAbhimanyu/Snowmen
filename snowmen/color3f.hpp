#ifndef COLOR3F_HPP
#define COLOR3F_HPP

#include <GL/glut.h>

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

#endif		// COLOR3F_HPP
