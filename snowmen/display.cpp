#include <iostream>
#include <cmath>
#include <assert.h>

#include "display.hpp"

#include "consts.hpp"

// Display a single snowman
void DisplayListOne::draw(bool hit, const Vector3f& hitPos)
{
	snowmen->draw(hit, hitPos);
}

// Display a group of snowmen around a circle, making them face inward
void DisplayListInward::draw(bool hit, const Vector3f& hitPos)
{
	// Draw the snowmen
	for(int idx = 0; idx < num; idx++)
		snowmen[idx].draw(hit, hitPos);
}

// Display a group of snowmen around a circle, making them face outward
void DisplayListOutward::draw(bool hit, const Vector3f& hitPos)
{
	// Draw the snowmen
	for(int idx = 0; idx < num; idx++)
		snowmen[idx].draw(hit, hitPos);
}

// Display a group of snowmen around a circle,
// making them face along the tangent
void DisplayListTangent::draw(bool hit, const Vector3f& hitPos)
{
	// Draw the snowmen
	for(int idx = 0; idx < num; idx++)
		snowmen[idx].draw(hit, hitPos);
}

// Display groups of snowmen
void DisplayListGroup::draw(bool hit, const Vector3f& hitPos)
{
	// Draw numDisplayList groups of snowmen
	for (int idx = 0; idx < numDisplayList; idx++)
		displayList[idx]->draw(hit, hitPos);
}
