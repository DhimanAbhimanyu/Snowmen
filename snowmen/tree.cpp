#include <iostream>

#include <GL/freeglut.h>
#include <GL/glut.h>

#include <stdio.h>

#include "tree.hpp"
#include "tree_position.hpp"
#include "display_colors.hpp"
#include "drawing.hpp"
#include "rotation.hpp"
#include "globals.hpp"

// Draw a tree at position and height
void Tree::draw(void)
{
	//printf("draw\n");

	glPushMatrix();

	glTranslatef(position.getX(), position.getY(), position.getZ());
	drawTrunk();
	drawBranches();

	glPopMatrix();
}

// Draw the trunk
void Tree::drawTrunk(void)
{
	// Set the color for the tree
	glColor3f(DISPLAY_COLOR_TREE_TRUNK.getR(),
		  DISPLAY_COLOR_TREE_TRUNK.getG(),
		  DISPLAY_COLOR_TREE_TRUNK.getB());

	glPushMatrix();

	glRotatef(-90, 1, 0, 0);
	drawCurr->drawCone(treeRadius, treeHeight, 15, 15);

	glPopMatrix();
}

// Draw the branches for the tree
void Tree::drawBranches(void)
{
	for (int curr = 0; curr < branchSet; curr++) {
		float currRatio = float(curr) / branchSet,
			currRatioMul = currRatio / 2 + 0.5;
		drawBranchSet(treeRadius * (1 - currRatioMul),
			      treeHeight * currRatioMul,
			      branchLength * currRatioMul,
			      currRatio * 360);
	}
}

// Draw a set of branches at a height
void Tree::drawBranchSet(GLfloat start, GLfloat height,
			 GLfloat length, GLfloat angle)
{
	glPushMatrix();

	glTranslatef(0, treeHeight, 0);
	// Draw the branch set
	glRotatef(angle, 0, 1, 0);
	for (GLfloat theta = 0, inc = GLfloat(360) / branchSet;
	     theta < 360; theta += inc)
		drawBranch(start, theta,
			   length * start, branchRadius * start);

	glPopMatrix();
}

// Draw a branch
void Tree::drawBranch(GLfloat start, GLfloat theta,
		      GLfloat branchLength, GLfloat branchRadius)
{
	// Set the color for the branch
	glColor3f(DISPLAY_COLOR_TREE_BRANCH.getR(),
		  DISPLAY_COLOR_TREE_BRANCH.getG(),
		  DISPLAY_COLOR_TREE_BRANCH.getB());

	glPushMatrix();

	GLfloat rad = Rotation::deg2Rad(theta);
	glTranslatef(start * sinf(rad), 0, start * cosf(rad));
	glRotatef(theta, 0, 1, 0);
	// Draw the branch
	drawCurr->drawCone(branchRadius, branchLength, 5, 5);
	// Draw the Leaves
	drawLeaves(leavesSet, leafLength);

	glPopMatrix();
}

// Draw leaves of length, upon a branch.
// The leaves are arranged in a set of leaves
void Tree::drawLeaves(int num, GLfloat leafLength)
{
	// Set the color for the leaves
	glColor3f(DISPLAY_COLOR_TREE_LEAVES.getR(),
		  DISPLAY_COLOR_TREE_LEAVES.getG(),
		  DISPLAY_COLOR_TREE_LEAVES.getB());

	GLfloat incBranchLength = branchLength / num,
		incLeafLength = leafLength / (num + 1),
		incRotation = 360 / num;

	for (int curr = 0; curr < num; curr++)
		drawLeafSet(curr * incBranchLength,
			    (num + 1 - curr) * incLeafLength,
			    curr * incRotation, leavesInSet);
}

// Draw a set of leaves of length
void Tree::drawLeafSet(GLfloat branchLength, GLfloat leafLength,
		       GLfloat rotation, int num)
{
	glPushMatrix();

	glTranslatef(0, 0, branchLength);
	glRotatef(-90, 1, 0, 0);
	glRotatef(rotation, 0, 1, 0);
	for (GLfloat angle = 0, inc = GLfloat(360) / num; angle < 360;
	     angle += inc)
		drawLeaf(angle, leafLength);

	glPopMatrix();
}

// Draw a leaf
void Tree::drawLeaf(GLfloat rotate, GLfloat length)
{
	glPushMatrix();

	glRotatef(rotate, 0, 1, 0);
	drawCurr->drawCone(leafRadius, length, 10, 10);

	glPopMatrix();
}
