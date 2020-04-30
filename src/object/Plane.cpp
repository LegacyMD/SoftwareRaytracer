#include "Plane.h"
#include "util/Ray.h"

#include <cmath>

Plane::Plane(const Vec3f &origin, const Vec3f &normal, const Color &color) : Object(color), origin(origin), normal(normal) {
    this->normal.normalize();
}

bool Plane::intersectWithRay(const Ray &ray, Vec3f &intersectionPoint, Vec3<float> &normal) const {
    float denominator = ray.getDirection().dot(this->getNormal());
    if (std::fabs(denominator) > 1e-6) {
        Vec3f v;
        float numerator = v.set(this->getOrigin()).subtract(ray.getStart()).dot(this->getNormal());
        float t = numerator / denominator;
        intersectionPoint.set(ray.getDirection()).scale(t).add(ray.getStart());
        normal.set(this->getNormal());
        if (normal.dot(ray.getDirection()) > 0) {
            normal.scale(-1);
        }
        return t > 1e-6;
    }
    return false;
}
