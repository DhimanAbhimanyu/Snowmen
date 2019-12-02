#include <iostream>
#include <cmath>

#include <GL/freeglut.h>
#include <GL/glut.h>

#include <stdio.h>

#include "drawing.hpp"
#include "rotation.hpp"
#include "globals.hpp"

// Draw a cone about an axis
void drawCone(const Vector3f& start, const float base, const float height,
	      const Vector3f& axis, int segs)
{
	//printf("start (%f, %f, %f), base %f, height %f, axis (%f, %f, %f)\n",
	//       start.getX(), start.getY(), start.getZ(),
	//       base, height,
	//       axis.getX(), axis.getY(), axis.getZ());

	Vector3f pos = Vector3f(0, 0, height / 4);
	float angle = Vector3f::angleRad(axis, Vector3f(0, 0, 1));

	// Rotate pos vector by using axis and angle
	pos.rotate(Vector3f(axis.getY(), axis.getX(), 0), angle);
	Vector3f newStart = start - pos;

	//printf("newStart (%f, %f, %f), angle %f\n",
	//       newStart.getX(), newStart.getY(), newStart.getZ(), angle);

	glPushMatrix();

	// Get to the start of the cone
	glTranslatef(newStart.getX(), newStart.getY(), newStart.getZ());
	// Rotate everything else to ensure that the
	// newly created cone is looking in the right direction
	glRotatef(Rotation::rad2Deg(angle), axis.getY(), axis.getX(), 0);

	// Draw the cone
	drawCurr->drawCone(base, height, segs, segs);

	glPopMatrix();
}

// Draw an Arc on a Sphere by Using a Cubic Bezier Curve from 4 sample points
// ref. https://en.wikipedia.org/wiki/B%C3%A9zier_curve#Cubic_B%C3%A9zier_curves
void drawArc(const Vector3f& p0, const Vector3f& p1,
	     const Vector3f& p2, const Vector3f& p3,
	     int numPoints)
{
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	for (int idx = 0; idx <= numPoints; idx++) {
		float t = ((float) idx) / numPoints;
		float a = (1 - t) * (1 - t) * (1 - t);
		float b = 3 * (1 - t) * (1 - t) * t;
		float c = 3 * (1 - t) * t * t;
		float d = t * t * t * t;
		glVertex3f(a * p0.getX() + b * p1.getX()
			   + c * p2.getX() + d * p3.getX(),
			   a * p0.getY() + b * p1.getY()
			   + c * p2.getY() + d * p3.getY(),
			   a * p0.getZ() + b * p1.getZ()
			   + c * p2.getZ() + d * p3.getZ());
	}
	glEnd();
	glPopMatrix();
}

// Get tbe co-ordinate of a point upon a sphere
// ref. https://en.wikipedia.org/wiki/Sphere#Equations_in_three-dimensional_space
Vector3f getSphereVertex(const Vector3f& centre, const float radius,
			 const float theta, const float phi)
{
	return Vector3f(centre.getX() + radius * sin(theta) * cos(phi),
			centre.getY() + radius * sin(theta) * sin(phi),
			centre.getZ() + radius * cos(theta));
}
