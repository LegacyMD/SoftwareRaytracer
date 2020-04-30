#include "Sphere.h"
#include "util/Ray.h"

#include <cmath>

Sphere::Sphere(const Vec3f & center, float radius, const Color & color)
	: Object(color), center(center), radius(radius) {}

bool Sphere::intersectWithRay(const Ray & ray, Vec3f & intersectionPoint, Vec3<float> &normal) const {
	const Vec3f L = this->getCenter() - ray.getStart();
	const float tca = L.dot(ray.getDirection());
	if (tca < 0)
		return false;

	const float d2 = L.dot(L) - tca * tca;
	const float r2 = this->getRadius() * this->getRadius();
	if (d2 > r2) {
		return false;
	}

	const float thc = sqrtf(r2 - d2);

	intersectionPoint.set(ray.getDirection()).scale(tca - thc).add(ray.getStart());
	normal.set(intersectionPoint).subtract(this->getCenter()).normalize();
	return true;
}
