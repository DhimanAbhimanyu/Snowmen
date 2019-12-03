#ifndef TREE_HPP
#define TREE_HPP

#include <GL/freeglut.h>
#include <GL/glut.h>

#include "object.hpp"
#include "vectors.hpp"
#include "tree_position.hpp"
#include "branch_position.hpp"
#include "branch.hpp"

class Tree : public Object {
	GLfloat treeRadius;
	GLfloat treeHeight;

	Branches branches;

	void drawTrunk(void);

public:
	Tree(const Vector3f& initPosition = Vector3f(),
	     GLfloat initTreeRadius = TRUNK_RADIUS,
	     GLfloat initTreeHeight = TREE_HEIGHT,
	     GLfloat initBranchRadius = BRANCH_RADIUS,
	     GLfloat initBranchLength = BRANCH_LENGTH,
	     int initBranchesNum = BRANCHES_NUM)
		: Object(initPosition),
		  treeRadius(initTreeRadius),
		  treeHeight(initTreeHeight),
		  branches(initPosition, initTreeRadius, initTreeHeight,
			   initBranchRadius, initBranchLength, initBranchesNum)
	{ }

	void setTreeHeight(GLfloat newTreeHeight)
	{
		treeHeight = newTreeHeight;
	}

	GLfloat getTreeHeight(void) const
	{
		return treeHeight;
	}

	void setTreeRadius(const GLfloat newTreeRadius)
	{
		treeRadius = newTreeRadius;
	}

	const GLfloat getTreeRadius(void) const
	{
		return treeRadius;
	}

	void draw(void);

	void initBranches(void)
	{
		branches.setTreeHeight(treeHeight);
		branches.setTreeRadius(treeRadius);
		branches.initBranches();
	}
};

#endif
