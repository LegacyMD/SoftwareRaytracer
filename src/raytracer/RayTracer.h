#pragma once

#include <limits>
#include <vector>
#include "util/Vector.h"

class Camera;
class Object;
class Ray;
struct Color;
class Light;

struct RayTracer {
    using ObjectVector = std::vector<const Object *>;
    constexpr static auto INF = std::numeric_limits<float>::max();
    constexpr static uint32_t MAX_RAY_DEPTH = 8u;

    struct TraceResults {
        const Object *closestObjectHit = nullptr;
        float closestDistanceToHitPoint2 = INF;
        Vec3f closestHitPoint = {INF, INF, INF};
        Vec3f normal = {INF, INF, INF};
    };

    static TraceResults findFirstIntersectingObject(const Vec3f &rayStart, const Vec3f &rayPoint, const ObjectVector &objects);
    static TraceResults findFirstIntersectingObject(const Ray &ray, const ObjectVector &objects);
    static Color renderPixel(const Camera &camera, float screenX, float screenY, const ObjectVector &objects, const Light &light);
    static Color trace(const Ray &ray, const ObjectVector &objects, const Light &light, uint32_t depth);
};
