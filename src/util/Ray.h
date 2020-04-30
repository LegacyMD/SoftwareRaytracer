#pragma once 

#include "util/Vector.h"

class Ray {
public:
	Ray(const Vec3f &start, const Vec3f &point) : start(start), direction(point - start) {
		direction.normalize();
	}

	const Vec3f &getStart() const { return start; }
	const Vec3f &getDirection() const { return direction; }
private:
	Vec3f start;
	Vec3f direction;
};