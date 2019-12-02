#ifndef COLORS_HPP
#define COLORS_HPP

#include <GL/freeglut.h>
#include <GL/glut.h>

/*
  A class to hold the normalized RGB colour values.
  That is each of the color value is >= 0 and <= 0.
 */
class Color3f {
protected:
	// Data members
	GLfloat r;	// Red
	GLfloat g;	// Green
	GLfloat b;	// Blue

public:
	// Constructer for the class
	Color3f(const GLfloat initR = 0, const GLfloat initG = 0,
		const GLfloat initB = 0)
		: r(initR), g(initG), b(initB)
	{
	}

	// Construct an instance from by copying over
	// the values from another instance
	Color3f(const Color3f &clr) : r(clr.r), g(clr.g), b(clr.b)
	{
	}

	// Get the values of the components
	const GLfloat getR(void) const { return r; }
	const GLfloat getG(void) const { return g; }
	const GLfloat getB(void) const { return b; }

	// Set the values of the components
	void setR(const GLfloat newR) { r = newR; }
	void setG(const GLfloat newG) { g = newG; }
	void setB(const GLfloat newB) { b = newB; }

	Color3f& operator=(const Color3f& obj)
	{
		r = obj.r;
		b = obj.b;
		g = obj.g;

		return *this;
	}
};

class Color4f : public Color3f {
protected:
	GLfloat a;	// Alpha

public:
	// Constructer for the class
	Color4f(const GLfloat initR = 0, const GLfloat initG = 0,
		const GLfloat initB = 0, const GLfloat initA = 0)
		: Color3f(initR, initG, initB), a(initA)
	{
	}

	// Get the values of the components
	const GLfloat getA(void) const { return a; }

	// Set the values of the components
	void setA(const GLfloat newA) { a = newA; }

	Color4f& operator=(const Color4f& obj)
	{
		r = obj.r;
		b = obj.b;
		g = obj.g;
		a = obj.a;

		return *this;
	}
};

#endif
