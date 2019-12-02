#ifndef DRAWING_HPP
#define DRAWING_HPP

#include "vectors.hpp"

// Draw an arc that passes 4 points.
extern void drawArc(const Vector3f& p0, const Vector3f& p1,
		    const Vector3f& p2, const Vector3f& p3,
		    int numPoints);
// Draw a cone about an axis
extern void drawCone(const Vector3f& start, const float base, const float height,
		     const Vector3f& axis, int segs);
// Return a vertex on a sphere, at a specified position
extern Vector3f getSphereVertex(const Vector3f& centre, const float radius,
				const float theta, const float phi);

#endif
