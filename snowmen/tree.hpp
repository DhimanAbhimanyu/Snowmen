#ifndef TREE_HPP
#define TREE_HPP

#include "vectors.hpp"
#include "tree_position.hpp"

class Tree {
	Vector3f position;

	GLfloat treeRadius;
	GLfloat treeHeight;

	GLfloat branchRadius;
	GLfloat branchLength;
	int branchSet;
	int branchesInSet;

	GLfloat leafRadius;
	GLfloat leafLength;
	int leavesSet;
	int leavesInSet;
	
	void drawTrunk(void);
	void drawBranches(void);
	void drawBranchSet(GLfloat start, GLfloat height,
			   GLfloat length, GLfloat angle);
	void drawBranch(GLfloat start, GLfloat theta,
			GLfloat branchLength, GLfloat branchRadius);
	void drawLeaves(GLfloat branchLength, int num, GLfloat leafLength);
	void drawLeafSet(GLfloat branchLength, GLfloat leafLength,
			 GLfloat rotation, int num);
	void drawLeaf(GLfloat leafLength, GLfloat rotate);

public:
	Tree(const Vector3f& initPosition = Vector3f(),
	     GLfloat initTreeRadius = TRUNK_RADIUS,
	     GLfloat initTreeHeight = TREE_HEIGHT,
	     GLfloat initBranchRadius = BRANCH_RADIUS,
	     GLfloat initBranchLength = TREE_BRANCH_LENGTH,
	     int initBranchSet = BRANCHES_SET_NUM,
	     int initBranchesInSet = BRANCHES_IN_SET,
	     GLfloat initLeafRadius = LEAF_RADIUS,
	     GLfloat initLeafLength = LEAF_LENGTH,
	     int initLeavesSet = LEAVES_SET_NUM,
	     int initLeavesInSet = LEAVES_IN_SET)
		: position(initPosition),
		  treeRadius(initTreeRadius),
		  treeHeight(initTreeHeight),
		  branchLength(initBranchLength),
		  branchSet(initBranchSet),
		  branchesInSet(initBranchesInSet),
		  leafRadius(initLeafRadius),
		  leafLength(initLeafLength),
		  leavesSet(initLeavesSet),
		  leavesInSet(initLeavesInSet)
	{ }

	// TBD Add set* & get* for the New Params!

	void setPosition(const Vector3f& newPosition)
	{
		position = newPosition;
	}

	const Vector3f& getPosition(void) const
	{
		return position;
	}

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

	void setLeafRadius(const GLfloat newLeafRadius)
	{
		leafRadius = newLeafRadius;
	}

	const GLfloat getLeafRadius(void) const
	{
		return leafRadius;
	}

	void draw(void);
};

#endif
