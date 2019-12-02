#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <iostream>
#include <cmath>

#include <assert.h>
#include <stdlib.h>

#include <GL/freeglut.h>
#include <GL/glut.h>

#include "vectors.hpp"
#include "snowman.hpp"
#include "rotation.hpp"

// The number of snowmen in a circle
static const int NUM_SNOWMEN = 8;
// The radius of the circle for the snowmen
static const int RADIUS_SNOWMEN = 2;

// The number of groups of snowmen
static const int NUM_SNOWMEN_GROUP = 8;
// The radius of the groups of snowmen
static const float RADIUS_SNOWMEN_GROUP = 8;

class Display {
protected:
	GLfloat radius;
	int num;

	Vector3f position;

public:
	Display(const Vector3f& initPosition = Vector3f(),
		const GLfloat initRadius = RADIUS_SNOWMEN,
		const int initNum = NUM_SNOWMEN)
		: radius(initRadius), num(initNum), position(initPosition)
	{
		assert(num > 0);
	}

	virtual ~Display()
	{
	}

	virtual void draw(bool hit = false,
			  const Vector3f& hitPos = Vector3f())
	{
	}

	virtual void init(void)
	{
	}

	void setPosition(const Vector3f& newPosition)
	{
		position = newPosition;
	}

	const Vector3f& getPosition(void) const
	{
		return position;
	}

	void setRadius(const GLfloat newRadius)
	{
		radius = newRadius;
	}

	const GLfloat getRadius(void) const
	{
		return radius;
	}

	void setNum(const int newNum)
	{
		num = newNum;
	}

	const int getNum(void) const
	{
		return num;
	}
};

class DisplayList : public Display {
protected:
	Snowman* snowmen;

	bool allocSnowmen(void)
	{
		deallocSnowmen();
		snowmen = new Snowman[num];
		return snowmen != NULL;
	}

	void deallocSnowmen(void)
	{
		if (snowmen) {
			delete[] snowmen;
			snowmen = NULL;
		}
	}

public:
	DisplayList(const Vector3f& initPosition = Vector3f(),
		    const GLfloat initRadius = RADIUS_SNOWMEN,
		    const int initNum = NUM_SNOWMEN)
		: Display(initPosition, initRadius, initNum), snowmen(NULL)
	{
		assert(allocSnowmen());
	}

	~DisplayList()
	{
		deallocSnowmen();
	}
};

// Display a single snowman
class DisplayListOne : public DisplayList {
public:
	DisplayListOne(const Vector3f& initPosition = Vector3f())
		: DisplayList(initPosition)
	{
		init();
	}

	void init(void)
	{
		snowmen->setPosition(position);
	}

	void draw(bool hit = false,
		  const Vector3f& hitPos = Vector3f());
};

// Display a group of snowmen around a circle, making them face inward
class DisplayListInward : public DisplayList {
public:
	DisplayListInward(const Vector3f& initPosition = Vector3f(),
			  const GLfloat initRadius = RADIUS_SNOWMEN,
			  const int initNum = NUM_SNOWMEN)
		: DisplayList(initPosition, initRadius, initNum)
	{
		init();
	}

	void init(void)
	{
		assert(radius > 0);

		// The amount by which the angle will vary for each snowman
		GLfloat deltaTheta = M_PI * 2 / num;
		// The angle for the current snowman
		GLfloat theta = 0.0;
		// Init the snowmen
		for(int idx = 0; idx < num; idx++, theta += deltaTheta) {
			// Calculate the centre for the current snowman
			// and the amount by which it needs to be rotated
			Vector3f centre(radius * cosf(theta), 0,
					radius * sinf(theta));
			Vector3f pos = Vector3f(0, radius / 2);
			// origin to centre
			Vector3f axis = Vector3f() - centre;
			float angle = Vector3f::angleRad(
				axis, Vector3f(0, 0, 1));
			pos.rotate(Vector3f(axis.getY(),
					    axis.getX(), 0), angle);
			centre -= pos;

			// Init the current snowman
			snowmen[idx].setPosition(
				Vector3f(position.getX() + centre.getX(),
					 position.getY(),
					 position.getZ() + centre.getZ()));
			snowmen[idx].setRotation(
				Rotation::rad2Deg(angle));
			snowmen[idx].setAxis(
				Vector3f(axis.getY(), axis.getX(), 0));
		}
	}

	void draw(bool hit = false,
		  const Vector3f& hitPos = Vector3f());
};

// Display a group of snowmen around a circle, making them face outward
class DisplayListOutward : public DisplayList {
public:
	DisplayListOutward(const Vector3f& initPosition = Vector3f(),
			   const GLfloat initRadius = RADIUS_SNOWMEN,
			   const int initNum = NUM_SNOWMEN)
		: DisplayList(initPosition, initRadius, initNum)
	{
		init();
	}

	void init(void)
	{
		assert(radius > 0);

		// The amount by which the angle will vary for each snowman
		float deltaTheta = 2 * M_PI / num;
		// The angle for the current snowman
		float theta = 0.0;
		// Draw num number of snowmen
		for(int idx = 0; idx < num; idx++, theta += deltaTheta) {
			// Calculate the centre for the current snowman
			// and the amount by which it needs to be rotated
			Vector3f centre(radius * cosf(theta), 0,
					radius * sinf(theta));
			Vector3f pos = Vector3f(0, radius / 2);
			// centre to origin
			Vector3f axis = centre - Vector3f();
			float angle = Vector3f::angleRad(
				axis, Vector3f(0, 0, 1));
			pos.rotate(Vector3f(axis.getY(), axis.getX(), 0),
				   angle);
			centre -= pos;

			// Init the current snowman
			snowmen[idx].setPosition(
				Vector3f(position.getX() + centre.getX(),
					 position.getY(),
					 position.getZ() + centre.getZ()));
			snowmen[idx].setRotation(Rotation::rad2Deg(angle));
			snowmen[idx].setAxis(
				Vector3f(axis.getY(), axis.getX(), 0));
		}
	}

	void draw(bool hit = false,
		  const Vector3f& hitPos = Vector3f());
};

// Display a group of snowmen around a circle,
// making them face along the tangent
class DisplayListTangent : public DisplayList {
public:
	DisplayListTangent(const Vector3f& initPosition = Vector3f(),
			   const GLfloat initRadius = RADIUS_SNOWMEN,
			   const int initNum = NUM_SNOWMEN)
		: DisplayList(initPosition, initRadius, initNum)
	{
		init();
	}

	void init(void)
	{
		assert(radius > 0);

		// The amount by which the angle will vary for each snowman
		float deltaTheta = 2 * M_PI / num;
		// The angle for the current snowman
		float theta = 0.0;
		// Draw num number of snowmen
		for(int idx = 0; idx < num; idx++, theta += deltaTheta) {
			// Calculate the centre for the current snowman
			// and the amount by which it needs to be rotated
			Vector3f centre(radius * cosf(theta), 0,
					radius * sinf(theta));
			Vector3f pos = Vector3f(0, radius / 2);
			// centre to origin
			Vector3f axis = centre - Vector3f();
			axis.rotate(Vector3f(0, 1, 0), M_PI / 2);
			float angle = Vector3f::angleRad(axis,
							 Vector3f(0, 0, 1));
			pos.rotate(Vector3f(axis.getY(), axis.getX(), 0),
				   angle);
			centre -= pos;

			// Init the current snowman
			snowmen[idx].setPosition(
				Vector3f(position.getX() + centre.getX(),
					 position.getY(),
					 position.getZ() + centre.getZ()));
			snowmen[idx].setRotation(Rotation::rad2Deg(angle));
			snowmen[idx].setAxis(
				Vector3f(axis.getY(), axis.getX(), 0));
		}
	}

	void draw(bool hit = false,
		  const Vector3f& hitPos = Vector3f());
};

// Display groups of snowmen
class DisplayListGroup : public Display {
protected:
	// A list of possible DisplayList classes
	static const size_t DISPLAY_LIST_KINDS = 4;

	int numDisplayList;
	DisplayList** displayList;
	GLfloat displayListRadius;

	bool allocDisplayList(void)
	{
		deallocDisplayList();
		displayList = (__typeof__(displayList))
			malloc(sizeof(displayList) * num);
		if (displayList == NULL)
			return false;

		bool success = true;
		for (int idx = 0; idx < num; idx++) {
			switch (rand() % DISPLAY_LIST_KINDS) {
			case 0:
				displayList[idx] = new DisplayListOne();
				break;
			case 1:
				displayList[idx] = new DisplayListInward();
				break;
			case 2:
				displayList[idx] = new DisplayListOutward();
				break;
			case 3:
				displayList[idx] = new DisplayListTangent();
				break;
			default:
				displayList[idx] = NULL;
				break;
			}
			if (displayList[idx] == NULL)
				success = false;
		}
		return success;
	}

	void deallocDisplayList(void)
	{
		if (displayList) {
			for (int idx = 0; idx < num; idx++)
				if (displayList[idx]) {
					delete displayList[idx];
					displayList[idx] = NULL;
				}

			free(displayList);
			displayList = NULL;
		}
	}

public:
	DisplayListGroup(const Vector3f& initPosition = Vector3f(),
			 const GLfloat initRadius = RADIUS_SNOWMEN,
			 const int initNum = NUM_SNOWMEN,
			 const int initNumDisplayList = NUM_SNOWMEN_GROUP,
			 const GLfloat initDisplayListRadius
			 = RADIUS_SNOWMEN_GROUP)
		: Display(initPosition, initRadius, initNum),
		  numDisplayList(initNumDisplayList),
		  displayList(NULL),
		  displayListRadius(initDisplayListRadius)
	{
		init();
	}

	void init(void)
	{
		assert(radius > 0);
		assert(displayListRadius > 0);

		deallocDisplayList();
		assert(allocDisplayList());
		// The amount by which the angle will vary for each group
		float deltaTheta = 2 * M_PI / numDisplayList;
		// The angle for the current snowman
		float theta = 0.0;
		// Draw NUM_SNOWMEN_GROUP groups of snowmen
		for (int idx = 0; idx < numDisplayList;
		     idx++, theta += deltaTheta) {
			// Calculate the centre for the current group
			Vector3f centre(displayListRadius * cos(theta),
					0,
					displayListRadius * sin(theta));

			// Init the current group
			displayList[idx]->setPosition(
				Vector3f(position.getX() + centre.getX(),
					 position.getY(),
					 position.getZ() + centre.getZ()));
			displayList[idx]->setRadius(radius);
			displayList[idx]->setNum(num);
			displayList[idx]->init();
		}
	}

	~DisplayListGroup()
	{
		deallocDisplayList();
	}
	
	void draw(bool hit = false,
		  const Vector3f& hitPos = Vector3f());
};

#endif
