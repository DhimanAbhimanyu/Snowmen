#include <iostream>

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

	gotoPosition();
	drawTrunk();
	branches.draw();

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
