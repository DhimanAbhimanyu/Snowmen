#ifndef TREE_SET_HPP
#define TREE_SET_HPP

#include <assert.h>

#include "vectors.hpp"
#include "tree.hpp"

static const int TREES_SET_NUM = 9;
static const GLfloat TREE_RADIUS = 14.14213;

class TreeSet {
	int num;
	Tree* trees;

	bool allocTrees(void)
	{
		if (trees)
			deallocTrees();

		trees = new Tree[num];
		if (!trees)
			return false;

		return true;
	};

	void deallocTrees(void)
	{
		if (trees) {
			delete[] trees;
			trees = NULL;
		}
	};

public:
	TreeSet(const int initNum = TREES_SET_NUM)
		: num(initNum), trees(NULL)
	{
		assert(num > 0);

		assert(allocTrees());
		init();
	}

	void init(void)
	{
		GLfloat angle = 0, inc = 2 * M_PI / num;
		for (int idx = 0; idx < num; idx++, angle += inc)
			trees[idx].setPosition(
				Vector3f(TREE_RADIUS * sinf(angle), 0,
					 TREE_RADIUS * cosf(angle)));
	}

	~TreeSet(void)
	{
		deallocTrees();
	}

	void draw(void)
	{
		for (int idx = 0; idx < num; idx++)
			trees[idx].draw();
	}
			
	void setNum(const int newNum)
	{
		num = newNum;

		assert(allocTrees());
	}

	const GLfloat getNum(void) const
	{
		return num;
	}
};

#endif
