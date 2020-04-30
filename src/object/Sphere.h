#pragma once

#include "object/Object.h"
#include "util/Vector.h"

class Sphere : public Object {
public:
	Sphere(const Vec3f &center, float radius, const Color &color);
	bool intersectWithRay(const Ray &ray, Vec3f &intersectionPoint, Vec3<float> &normal) const override;

	const Vec3f &getCenter() const { return center; }
	float getRadius() const { return radius; }
private:
	Vec3f center;
	float radius;
};