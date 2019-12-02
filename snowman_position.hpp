#ifndef SNOWMAN_POSITION_HPP
#define SNOWMAN_POSITION_HPP

#include <GL/freeglut.h>
#include <GL/glut.h>

#include "vectors.hpp"
#include "moving_object.hpp"

static const Vector3f LOWER_BODY_POS = Vector3f(0, 0.5);
static const Vector3f UPPER_BODY_POS = Vector3f(0, 1);
static const Vector3f BUTTONS_POS = UPPER_BODY_POS;
static const Vector3f HEAD_POS = Vector3f(0, 1.5);
static const Vector3f LEFT_ARM_POS = Vector3f(0, 1, 0);
static const Vector3f RIGHT_ARM_POS = Vector3f(0, 1, 0);
static const Vector3f EYE_POS = Vector3f(0, 1.5);
static const Vector3f NOSE_POS = Vector3f(0, 1.5);
static const Vector3f MOUTH_POS = Vector3f(0, 1.5);
static const Vector3f HAT_POS = Vector3f(0, 1.7);

static const GLfloat LOWER_BODY_RADIUS = 0.5;
static const GLfloat UPPER_BODY_RADIUS = 0.375;
static const GLfloat BUTTONS_RADIUS = 0.375;
static const GLfloat HEAD_RADIUS = 0.25;
static const GLfloat EYES_RADIUS = 0.05;
static const GLfloat BUTTON_RADIUS = 0.0375;
static const GLfloat MOUTH_RADIUS = 0.25;

static const GLfloat ARM_LENGTH = 1;
static const GLfloat ARM_BASE = 0.06;
static const GLfloat FINGER_BASE = 0.015;
static const GLfloat FINGER_OFFSET = 0.1;
static const GLfloat FINGER_LENGTH_RATIO = 0.75;
static const GLfloat FINGER_HEIGHT_RATIO = 6;

static const Vector3f BUTTONS_CENTRE = Vector3f();
static const GLfloat BUTTON_THETA_RATIO_NUM = 3;
static const GLfloat BUTTON_THETA_RATIO_DEN = 8;
static const GLfloat BUTTON_THETA_RATIO = BUTTON_THETA_RATIO_NUM
	/ BUTTON_THETA_RATIO_DEN;

static const Vector3f LEFT_ARM_START = Vector3f(0.375);
static const Vector3f RIGHT_ARM_START = Vector3f(-0.375);
static const Vector3f LEFT_ARM_AXIS = Vector3f(0.707, 0, 0.707);
static const Vector3f RIGHT_ARM_AXIS = Vector3f(-0.707, 0, 0.707);

static const Vector3f EYE_TRANS = Vector3f(0.05, 0.10, 0.18);

static const GLfloat NOSE_ANGLE = 0;
static const Vector3f NOSE_AXIS = Vector3f(1);

static const Vector3f MOUTH_CENTRE = Vector3f(0, -0.1875, 0.025);

static const Vector3f HAT_CENTRE = Vector3f(0, 0, 0);
static const Vector3f HAT_AXIS = Vector3f(0, 1, 0);
static const GLfloat HAT_SIZE = 0.3;
static const GLfloat HAT_RADIUS = 0.15;
static const GLfloat HAT_HEIGHT = 0.375;
static const GLfloat HAT_BRIM_RADIUS = 0.006125;

class SnowmanPosition {
public:
	Vector3f lowerBodyPos;
	Vector3f upperBodyPos;
	Vector3f buttonsPos;
	Vector3f headPos;
	Vector3f leftArmPos;
	Vector3f rightArmPos;
	Vector3f nosePos;
	Vector3f mouthPos;
	Vector3f hatPos;

	Vector3f leftArmStart;
	Vector3f rightArmStart;
	Vector3f leftArmAxis;
	Vector3f rightArmAxis;

	GLfloat noseAngle;
	Vector3f noseAxis;

	Vector3f hatAxis;

	SnowmanPosition(void) : lowerBodyPos(LOWER_BODY_POS),
				upperBodyPos(UPPER_BODY_POS),
				buttonsPos(BUTTONS_POS),
				headPos(HEAD_POS),
				leftArmPos(LEFT_ARM_POS),
				rightArmPos(RIGHT_ARM_POS),
				nosePos(NOSE_POS),
				mouthPos(MOUTH_POS),
				hatPos(HAT_POS),
				leftArmStart(LEFT_ARM_START),
				rightArmStart(RIGHT_ARM_START),
				leftArmAxis(LEFT_ARM_AXIS),
				rightArmAxis(RIGHT_ARM_AXIS),
				noseAngle(NOSE_ANGLE),
				noseAxis(NOSE_AXIS),
				hatAxis(HAT_AXIS)
	{ }
};

#endif
