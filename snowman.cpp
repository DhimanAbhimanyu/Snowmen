#include <iostream>
#include <cmath>

#include <GL/freeglut.h>
#include <GL/glut.h>

#include <stdio.h>

#include "snowman.hpp"
#include "consts.hpp"
#include "display_colors.hpp"
#include "globals.hpp"
#include "drawing.hpp"

// TBD Convert Using Snowman.Position in Params to Member Funcs!
// Draw the Snowman
void Snowman::draw(bool hit, const Vector3f& hitPos)
{
	BodyPart segment;

	if (hit && !startHit) {
		segment = locateHitSegment(hitPos, startTime, startHit);
		printf("startHit %d, segment %d, startTime %d\n",
		       startHit, segment, startTime);
	}

	if (startHit) {
		//printf("segment %d, startTime %d\n", segment, startTime);
		startTime = glutGet(GLUT_ELAPSED_TIME);
	}

	glPushMatrix();

	gotoPosition();
	glRotatef(rotation, axis.getX(), axis.getY(), axis.getZ());
	drawLowerBody();
	drawUpperBody();
	// Head
	drawBodySegment(snowmanPosition.headPos, HEAD_RADIUS, 10);
	// Arms
	drawArm(snowmanPosition.leftArmPos, 0, Vector3f(),
		snowmanPosition.leftArmStart, ARM_LENGTH,
		snowmanPosition.leftArmAxis);
	drawArm(snowmanPosition.rightArmPos, 0, Vector3f(),
		snowmanPosition.rightArmStart, ARM_LENGTH,
		snowmanPosition.rightArmAxis);
	// Eyes
	drawEyes(EYE_POS, EYE_TRANS, EYES_RADIUS, -0.15);
	// Nose
	drawNose(snowmanPosition.nosePos, snowmanPosition.noseAngle,
		 snowmanPosition.noseAxis);
	// Mouth
	drawMouth(snowmanPosition.mouthPos, MOUTH_CENTRE);
	// Hat
	drawHat(snowmanPosition.hatPos, HAT_CENTRE, snowmanPosition.hatAxis,
		HAT_SIZE, HAT_RADIUS, HAT_HEIGHT, HAT_BRIM_RADIUS);

	glPopMatrix();
}

void Snowman::drawLowerBody(void)
{
	// Lower Body
	drawBodySegment(snowmanPosition.lowerBodyPos,
			LOWER_BODY_RADIUS, 20);
}

void Snowman::drawUpperBody(void)
{
	// Upper Body
	drawBodySegment(snowmanPosition.upperBodyPos,
			UPPER_BODY_RADIUS, 15);
	// Buttons
	drawButtons(snowmanPosition.buttonsPos,
		    BUTTONS_CENTRE, BUTTONS_RADIUS, 5);
}

// TBD Calculate collision for Hat & Arms too!
Snowman::BodyPart Snowman::locateHitSegment(const Vector3f& hitPos,
					    int& startTime, bool& startHit)
{
	BodyPart segment;

	if (inSphere(snowmanPosition.lowerBodyPos,
		     LOWER_BODY_RADIUS, hitPos))
		segment = LOWER_BODY;
	else if (inSphere(snowmanPosition.upperBodyPos,
			  UPPER_BODY_RADIUS, hitPos))
		segment = UPPER_BODY;
	else if (inSphere(snowmanPosition.headPos, HEAD_RADIUS, hitPos))
		segment = HEAD;
	else {
		startHit = false;
		return NONE;
	}

	startHit = true;
	startTime = glutGet(GLUT_ELAPSED_TIME);
	return segment;
}

// Draw the num coat buttons. in a semicircle centered at centre
// and with passed radius. It is drawn by rotating a vector in the YZ plane
void Snowman::drawButtons(const Vector3f& pos, const Vector3f& centre,
			  const float radius, const int num)
{
	// Set the color for the coat buttons
	glColor3f(DISPLAY_COLOR_BUTTON.getR(), DISPLAY_COLOR_BUTTON.getG(),
		  DISPLAY_COLOR_BUTTON.getB());

	glPushMatrix();
	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	for (float theta = -M_PI * BUTTON_THETA_RATIO,
		     inc = M_PI * BUTTON_THETA_RATIO_NUM /
		     (BUTTON_THETA_RATIO_DEN * num);
	     theta <= M_PI * BUTTON_THETA_RATIO; theta += inc + inc)
		drawButton(centre, radius, theta, inc);

	glPopMatrix();
}

void Snowman::drawButton(const Vector3f& centre, const float radius,
			 const float theta, const float inc)
{
	// Figure out the centre of the current button
	// and the axis the button should be on
	Vector3f buttonCentre = getSphereVertex(
		centre, radius, theta + inc,
		copysignf(M_PI / 2, theta + inc));
	Vector3f axis = buttonCentre - centre;

	Vector3f pos = Vector3f(0, 0, radius / 2);
	float angle = Vector3f::angleRad(axis, Vector3f(0, 0, 1));

	// Rotate pos vector by using axis and angle
	pos.rotate(Vector3f(axis.getY(), axis.getX(), 0), angle);
	buttonCentre -= pos;

	glPushMatrix();

	// Get to the centre of the button
	glTranslatef(buttonCentre.getX(), buttonCentre.getY(),
		     buttonCentre.getZ());
	// Rotate everything else to ensure that the
	// newly created button is looking in the right direction
	glRotatef(Rotation::rad2Deg(theta), axis.getY(), axis.getX(), 0);

	// Drop a sphere to simulate the button
	// - it should be noted that only halt
	// of the sphere is outside the snowman's body
	drawCurr->drawSphere(BUTTON_RADIUS, 5, 5);

	glPopMatrix();
}

// Draw an arm of the snowman, started from start point,
// having a size of length and in the direction of dirVector
void Snowman::drawArm(const Vector3f& pos, GLdouble angle, const Vector3f& axis,
		      const Vector3f& start, const float length,
		      const Vector3f& dirVector)
{
	// Set the color for the arms
	glColor3f(DISPLAY_COLOR_ARM.getR(), DISPLAY_COLOR_ARM.getG(),
		  DISPLAY_COLOR_ARM.getB());

	glPushMatrix();
	//printf("pos (%f, %f, %f), dirVector (%f, %f, %f)\n",
	//       pos.getX(), pos.getY(), pos.getZ(),
	//       dirVector.getX(), dirVector.getY(), dirVector.getZ());
	glTranslatef(pos.getX(), pos.getY(), pos.getZ());
	if (angle) {
		//printf("angle %f, axis (%f, %f, %f)\n",
		//       angle, axis.getX(), axis.getY(), axis.getZ());
		glRotatef(angle, axis.getX(), axis.getY(), axis.getZ());
	}

	// Draw the arm
	drawCone(start, ARM_BASE, length, dirVector, 3);

	// Draw the fingers
	Vector3f end(start.getX() + dirVector.getX() * length * FINGER_LENGTH_RATIO,
		     start.getY(),
		     start.getZ() + dirVector.getZ() * length * FINGER_LENGTH_RATIO);
	drawCone(end, FINGER_BASE, length / FINGER_HEIGHT_RATIO,
		 Vector3f(end.getX() + FINGER_OFFSET, end.getY(),
			  end.getZ() + FINGER_OFFSET), 3);
	drawCone(end, FINGER_BASE, length / FINGER_HEIGHT_RATIO,
		 Vector3f(end.getX() - FINGER_OFFSET, end.getY(),
			  end.getZ() - FINGER_OFFSET), 3);

	glPopMatrix();
}

// Draw the eyes
void Snowman::drawEyes(const Vector3f& pos, const Vector3f& trans,
		       const float radius, const float seperation)
{
	// Set the color for the eyes
	glColor3f(DISPLAY_COLOR_EYE.getR(),
		  DISPLAY_COLOR_EYE.getG(),
		  DISPLAY_COLOR_EYE.getB());

	glPushMatrix();
	glTranslatef(pos.getX(), pos.getY(), pos.getZ());
	// Move to get to the location of an eye
	glTranslatef(trans.getX(), trans.getY(), trans.getZ());
	// Draw the eye
	drawCurr->drawSphere(radius, 5, 5);
	// Shift to location of the other eye
	glTranslatef(seperation, 0, 0);
	// Draw the eye
	drawCurr->drawSphere(radius, 5, 5);
	glPopMatrix();
}

// Draw the nose
void Snowman::drawNose(const Vector3f& pos,
		       const GLfloat angle, const Vector3f& axis)
{
	// Set the color for the nose
	glColor3f(DISPLAY_COLOR_NOSE.getR(),
		  DISPLAY_COLOR_NOSE.getG(),
		  DISPLAY_COLOR_NOSE.getB());

	glPushMatrix();
	glTranslatef(pos.getX(), pos.getY(), pos.getZ());
	if (angle)
		glRotatef(angle, axis.getX(), axis.getY(), axis.getZ());
	drawCurr->drawCone(0.08, 0.5, 5, 5);
	glPopMatrix();
}

// Draw the mouth
void Snowman::drawMouth(const Vector3f& pos, const Vector3f& centre)
{
	// Set the color for the mouth
	glColor3f(DISPLAY_COLOR_MOUTH.getR(), DISPLAY_COLOR_MOUTH.getG(),
		  DISPLAY_COLOR_MOUTH.getB());

	glPushMatrix();
	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	// Set the line width
	glLineWidth(3);

	drawArc(getSphereVertex(centre, MOUTH_RADIUS, -M_PI / 4, -M_PI / 4),
		getSphereVertex(centre, MOUTH_RADIUS, -M_PI / 8, -M_PI / 8),
		getSphereVertex(centre, MOUTH_RADIUS, M_PI / 8, M_PI / 8),
		getSphereVertex(centre, MOUTH_RADIUS, M_PI / 4, M_PI / 4),
		50);
	glPopMatrix();
}

void Snowman::drawBodySegment(const Vector3f& pos,
			      const GLdouble& radius, const GLdouble& segs)
{
	// Set the color for the snowman's body
	glColor3f(DISPLAY_COLOR_BODY.getR(),
		  DISPLAY_COLOR_BODY.getG(),
		  DISPLAY_COLOR_BODY.getB());

	glPushMatrix();
	// Draw Body Segment
	glTranslatef(pos.getX(), pos.getY(), pos.getZ());
	drawCurr->drawSphere(radius, segs, segs);
	glPopMatrix();
}

// Create the Hat of the Snowman
void Snowman::drawHat(const Vector3f& pos, const Vector3f& centre,
		      const Vector3f& axis, const float size,
		      const float radius, const float height,
		      const float brimRadius)
{
	glPushMatrix();
	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	Vector3f posn = Vector3f(0, 0, height / 2);
	float theta = Vector3f::angleRad(axis, Vector3f(0, 0, 1));

	posn.rotate(Vector3f(axis.getY(), axis.getX(), 0), theta);
	Vector3f newCentre = centre - posn;

	// Create the base cylinder for the hat
	glPushMatrix();
	glTranslatef(newCentre.getX(), newCentre.getY(), newCentre.getZ());
	glRotatef(Rotation::rad2Deg(theta), axis.getY(), axis.getX(), 0);
	glColor3f(DISPLAY_COLOR_HAT.getR(),
		  DISPLAY_COLOR_HAT.getG(),
		  DISPLAY_COLOR_HAT.getB());
	drawCurr->drawCube(radius * 2);
	glPopMatrix();

	// Add a puff to the hat
	glPushMatrix();
	glTranslatef(newCentre.getX(), newCentre.getY() + height / 2,
		     newCentre.getZ());
	glRotatef(Rotation::rad2Deg(theta), axis.getY(), axis.getX(), 0);
	glColor3f(DISPLAY_COLOR_HAT_BRIM.getR(),
		  DISPLAY_COLOR_HAT_BRIM.getG(),
		  DISPLAY_COLOR_HAT_BRIM.getB());
	drawCurr->drawTorus(radius, radius + brimRadius, 5, 5);
	glPopMatrix();

	glPopMatrix();
}
