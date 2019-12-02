#ifndef VERTEX_HPP
#define VERTEX_HPP

class Vertex
{
	float x;
	float y;
	float z;

public:
	Vertex(const float initX = 0, const float initY = 0,
	       const float initZ = 0)
		: x(initX), y(initY), z(initZ)
	{
	}

	float getX(void) { return x; }
	float getY(void) { return y; }
	float getZ(void) { return z; }

	void setX(const float newX) { x = newX; }
	void setY(const float newY) { y = newY; }
	void setZ(const float newZ) { z = newZ; }
};

#endif		// VERTEX_HPP
