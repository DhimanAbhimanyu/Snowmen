#ifndef SNOWMAN_HPP
#define SNOWMAN_HPP

#include "vectors.hpp"
#include "snowman_position.hpp"

class Snowman {
	enum BodyPart {LOWER_BODY, UPPER_BODY, HEAD, LEFT_ARM, RIGHT_ARM,
		       NOSE, HAT, NONE};

	Vector3f position;
	GLfloat rotation;
	Vector3f axis;

	SnowmanPosition snowmanPosition;
	int startTime = 0;
	bool startHit = false;

	void drawBodySegment(const Vector3f& pos,
			     const GLdouble& radius, const GLdouble& segs);
	BodyPart locateHitSegment(const Vector3f& hitPos,
				  int& startTime, bool& startHit);

	inline bool inSphere(const Vector3f& centre, GLfloat radius,
			     const Vector3f& hitPos)
	{
		Vector3f centre2HitPos = centre - hitPos;
		return centre2HitPos.sizeSquared() < radius * radius;
	}

	void drawLowerBody(void);
	void drawUpperBody(void);
	// Draw an arm of the snowman
	void drawArm(const Vector3f& pos, GLdouble angle,
		     const Vector3f& axis,
		     const Vector3f& start, const float length,
		     const Vector3f& dirVector);
	// Draw coat buttons for a snowman
	void drawButtons(const Vector3f& pos, const Vector3f& centre,
			 const float radius, const int num);
	// Draw a button upon the coat of the snowman
	void drawButton(const Vector3f& centre, const float radius,
			const float theta, const float inc);
	// Draw the eyes of the snowman
	void drawEyes(const Vector3f& pos, const Vector3f& trans,
		      const float radius, const float seperation);
	// Draw the nose of the snowman
	void drawNose(const Vector3f& pos,
		      const GLfloat angle, const Vector3f& axis);
	// Draw the mouth of the snowman
	void drawMouth(const Vector3f& pos, const Vector3f& centre);
	// Draw the hat of the snowman
	void drawHat(const Vector3f& pos, const Vector3f& centre,
		     const Vector3f& axis,
		     const float size, const float radius,
		     const float height, const float brimRadius);

public:
	Snowman(const Vector3f& initPosition = Vector3f(),
		const GLfloat initRotation = 0,
		const Vector3f& initAxis = Vector3f())
		: position(initPosition), rotation(initRotation),
		  axis(initAxis)
	{ }

	void setPosition(const Vector3f setPosition)
	{
		position = setPosition;
	}

	const Vector3f& getPosition(void) const
	{
		return position;
	}

	void setRotation(const GLfloat setRotation)
	{
		rotation = setRotation;
	}

	const GLfloat getRotation(void) const
	{
		return rotation;
	}

	void setAxis(const Vector3f setAxis)
	{
		axis = setAxis;
	}

	const Vector3f& getAxis(void) const
	{
		return axis;
	}

	// Draw the snowman
	void draw(bool hit = false, const Vector3f& hitPos = Vector3f());
};

#endif
