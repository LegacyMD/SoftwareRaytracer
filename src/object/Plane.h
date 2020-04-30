#pragma once

#include "object/Object.h"
#include "util/Vector.h"

class Plane : public Object {
public:
	Plane(const Vec3f &origin, const Vec3f &normal, const Color &color);
	bool intersectWithRay(const Ray &ray, Vec3f &intersectionPoint, Vec3<float> &normal) const override;

	const Vec3f &getOrigin() const { return origin; }
	const Vec3f &getNormal() const { return normal; }
private:
	Vec3f origin;
	Vec3f normal;
};
