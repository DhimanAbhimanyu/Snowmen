#ifndef ROTATION_HPP
#define ROTATION_HPP

static const float ROTATION_Y = 0;
static const float ROTATION_DELTA = 0;
static const float ROTATION_X = 0;

// The amount to rotate by
static const float ROTATION_DELTA_DIFF = 0.003125;

class Rotation {
	// The current amount of rotation about the y-axis
	float rotationY;
	// The amount to add to the rotation around the y-axis
	float rotationYDelta;
	// The current amount of rotation about the x-axis
	float rotationX;
	// Should the snowmen be rotated about the y-axis?
	bool rotateY;
	int startTime;

public:
	// Convert degrees to radians
	static float deg2Rad(const float degree)
	{
		// The value of PI divided by 180
		const float byPI180 = M_PI / 180;

		return degree * byPI180;
	}

	// Convert radians to degrees
	static float rad2Deg(const float radian)
	{
		// The value of 180 divided by PI
		const float by180PI = 180 / M_PI;

		return radian * by180PI;
	}

	static void adjustTheta(float &theta)
	{
		if (theta > 360)
			while (theta > 360)
				theta -= 360;
		else if (theta < 0)
			while (theta < 0)
				theta += 360;
	}

	Rotation(const float initRotationY = ROTATION_Y,
		 const float initRotationYDelta = ROTATION_DELTA,
		 const float initRotationX = ROTATION_X)
		: rotationY(initRotationY), rotationYDelta(initRotationYDelta),
		  rotationX(initRotationX)
	{
		updateTime();
		updateRotateY();
	}

	void updateTime(void)
	{
		startTime = glutGet(GLUT_ELAPSED_TIME);
	}

	const float getRotationY(void) const
	{
		return rotationY;
	}

	const float getRotationX(void) const
	{
		return rotationX;
	}

	const float getRotateY(void) const
	{
		return rotateY;
	}

	const float getRotationYDelta(void) const
	{
		return rotationYDelta;
	}

	void update(void)
	{
		// Update the rotation about the Y axis
		if (rotateY && rotationYDelta != 0) {
			int time = glutGet(GLUT_ELAPSED_TIME);

			rotationY += (time - startTime) * rotationYDelta;
			startTime = time;
		}
	}

	bool rotating(void)
	{
		return rotateY;
	}

	void updateRotateY(void)
	{
		rotateY = rotationYDelta != 0;
	}

	void decRotationY(void)
	{
		rotationYDelta -= ROTATION_DELTA_DIFF;
		updateRotateY();
		updateTime();
	}

	void incRotationY(void)
	{
		rotationYDelta += ROTATION_DELTA_DIFF;
		updateRotateY();
		updateTime();
	}

	void reset(void)
	{
		rotationY = ROTATION_Y;
		rotationYDelta = ROTATION_DELTA;
		rotationX = ROTATION_X;
		updateTime();
	}

	void pauseAnimationY(void)
	{
		rotateY = false;
		rotationYDelta = ROTATION_DELTA;
	}

	void decRotationX(void)
	{
		rotationX -= ROTATION_DELTA_DIFF;
		updateRotateY();
		updateTime();
	}

	void incRotationX(void)
	{
		rotationX += ROTATION_DELTA_DIFF;
		updateRotateY();
		updateTime();
	}

	Rotation& operator=(const Rotation &obj)
	{
		rotationY = obj.rotationY;
		rotationYDelta = obj.rotationYDelta;
		rotateY = obj.rotateY;
		rotationX = obj.rotationX;
		startTime = obj.startTime;

		return *this;
	}
};

#endif
