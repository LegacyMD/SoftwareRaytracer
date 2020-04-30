#pragma once

#include "util/Color.h"
#include "util/Vector.h"

class  Ray;

class Object {
public:
	Object(const Color &color) : color(color) {};
	Color getColor() const { return color; }
	virtual bool intersectWithRay(const Ray &ray, Vec3<float> &intersectionPoint, Vec3<float> &normal) const = 0;
private:
	Color color;
};