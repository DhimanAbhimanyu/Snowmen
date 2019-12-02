#ifndef MOVING_OBJECT_HPP
#define MOVING_OBJECT_HPP

#include <GL/freeglut.h>
#include <GL/glut.h>

#include "vectors.hpp"
#include "rotation.hpp"

static const GLfloat MOVING_OBJ_ROTATION_DELTA = 0.1;
static const GLfloat GRAVITY = 9.8;

class MovingObj {
public:
	Vector3f pos;
	GLfloat rotation;
	Vector3f speed;

	MovingObj(const Vector3f& initPos = Vector3f(),
		  const GLfloat initRotation = 0,
		  const Vector3f& initSpeed = Vector3f())
		: pos(initPos), rotation(initRotation), speed(initSpeed)
	{ }

	void update(const int timeDelta)
	{
		rotation += timeDelta * MOVING_OBJ_ROTATION_DELTA;
		Rotation::adjustTheta(rotation);

		speed.setY(speed.getY() * timeDelta + GRAVITY * timeDelta * timeDelta);

		pos.setX(pos.getX() + speed.getX() * timeDelta);
		pos.setY(pos.getY() + speed.getY() * timeDelta);
		pos.setZ(pos.getZ() + speed.getZ() * timeDelta);
	}
};

#endif
