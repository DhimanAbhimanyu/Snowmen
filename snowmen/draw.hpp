#ifndef DRAW_HPP
#define DRAW_HPP

#include <GL/freeglut.h>
#include <GL/glut.h>

// A class that contains pointers to the glut object primitives used
class Draw {
public:
	// Draw a sphere
	void (*drawSphere)(GLdouble, GLint, GLint);
	// Draw a cube
	void (*drawCube)(GLdouble);
	// Draw a torus
	void (*drawTorus)(GLdouble, GLdouble, GLint, GLint);
	// Draw a cone
	void (*drawCone)(GLdouble, GLdouble, GLint, GLint);

	// Initialize the object
	Draw(void (*initDrawSphere)(GLdouble, GLint, GLint),
	       void (*initDrawCube)(GLdouble),
	       void (*initDrawTorus)(GLdouble, GLdouble, GLint, GLint),
	       void (*initDrawCone)(GLdouble, GLdouble, GLint, GLint))
		: drawSphere(initDrawSphere),
		  drawCube(initDrawCube),
		  drawTorus(initDrawTorus),
		  drawCone(initDrawCone)
	{
	}
};

#endif
