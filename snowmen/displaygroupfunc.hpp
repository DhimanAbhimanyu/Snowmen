#ifndef DISPLAYGROUPFUNC_HPP
#define DISPLAYGROUPFUNC_HPP

#include <stdlib.h>
#include <assert.h>

#include "display.hpp"

class DisplayGroupFunc {
	static const int DISPLAY_KINDS = 5;

	Display* display[DISPLAY_KINDS] = {NULL, NULL, NULL, NULL, NULL};
	int currDisplay;

	bool allocDisplay(void)
	{
		display[0] = new DisplayListOne();
		display[1] = new DisplayListInward();
		display[2] = new DisplayListOutward();
		display[3] = new DisplayListTangent();
		display[4] = new DisplayListGroup();

		for (int idx; idx < DISPLAY_KINDS; idx++)
			if (!display[idx])
				return false;
		return true;
	}

	void deallocDisplay(void)
	{
		for (int idx = 0; idx < DISPLAY_KINDS; idx++)
			if (display[idx]) {
				delete display[idx];
				display[idx] = NULL;
			}
	}

public:
	// Initialize the new instance
	DisplayGroupFunc(void)
	{
		assert(allocDisplay());
		selectRandDisplay();
	}

	Display*& operator[](size_t idx)
	{
		assert(idx >= 0 && idx < DISPLAY_KINDS);

		return display[idx];
	}

	void selectRandDisplay(void)
	{
		currDisplay = rand() % DISPLAY_KINDS;
		display[currDisplay]->init();
	}

	int getCurrDisplay(void)
	{
		return currDisplay;
	}

	Display* getDisplayCurr(void)
	{
		return display[currDisplay];
	}
	
	void selectDisplayListOne(void)
	{
		currDisplay = 0;
		display[currDisplay]->init();
	}

	void selectDisplayListInward(void)
	{
		currDisplay = 1;
		display[currDisplay]->init();
	}

	void selectDisplayListOutward(void)
	{
		currDisplay = 2;
		display[currDisplay]->init();
	}

	void selectDisplayListTangent(void)
	{
		currDisplay = 3;
		display[currDisplay]->init();
	}

	void selectDisplayListGroup(void)
	{
		currDisplay = 4;
		display[currDisplay]->init();
	}
};

#endif
