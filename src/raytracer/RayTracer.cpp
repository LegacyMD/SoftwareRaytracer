#include "RayTracer.h"

#include "object/Object.h"
#include "object/Sphere.h"
#include "util/Ray.h"
#include "util/Vector.h"
#include "util/Color.h"
#include "raytracer/Light.h"
#include "raytracer/Camera.h"

#include <algorithm>

inline RayTracer::TraceResults RayTracer::findFirstIntersectingObject(const Vec3f &rayStart, const Vec3f &rayPoint, const ObjectVector &objects) {
    Ray ray{rayStart, rayPoint};
    return findFirstIntersectingObject(ray, objects);
}

RayTracer::TraceResults RayTracer::findFirstIntersectingObject(const Ray &ray, const ObjectVector &objects) {
    RayTracer::TraceResults traceResults;
    Vec3f hitPoint;
    Vec3f hitPointNormal;
    for (auto object : objects) {
        if (object->intersectWithRay(ray, hitPoint, hitPointNormal)) {
            float distance2 = hitPoint.dist2(ray.getStart());
            if (distance2 < traceResults.closestDistanceToHitPoint2) {
                traceResults.closestDistanceToHitPoint2 = distance2;
                traceResults.closestHitPoint = hitPoint;
                traceResults.closestObjectHit = object;
                traceResults.normal = hitPointNormal;
            }
        }
    }
    return traceResults;
}

Color RayTracer::renderPixel(const Camera &camera, float screenX, float screenY, const ObjectVector &objects, const Light &light) {
    // hacky stuff to visualize light
    {
        Vec3f mockLight = light.getPosition();
        mockLight.z = 0;
        if (camera.getPointLookedAt(screenX, screenY).dist2(mockLight) < 16) {
            return Color::yellow();
        }
    }

   const Vec3f rayDirection = camera.getPointLookedAt(screenX, screenY);
   const Ray ray{camera.getPosition(), rayDirection};
   return trace(ray, objects, light, 0);
}

Color RayTracer::trace(const Ray &ray, const ObjectVector &objects, const Light &light, uint32_t depth) {
    // Find closest object we're looking at
    auto traceResults = findFirstIntersectingObject(ray, objects);

    // Return background color if we're not looking at anything
    if (traceResults.closestObjectHit == nullptr) {
        return Color::white();
    }

    if (dynamic_cast<const Sphere *>(traceResults.closestObjectHit) != nullptr && false) { // TODO HAAAAaAACKY WAY to make all spheres transparent
        //float refractionIndex = 1.3;
        //if (traceResults.normal.dot(rayDirection) > 0) {
        //    // We're inside of object
        //    refractionIndex = 1 / refractionIndex;
        //    traceResults.normal.scale(-1);
        //}

        //float cos = rayDirection.copy().normalize().dot(traceResults.normal);
        //float sin



        //if (depth == MAX_RAY_DEPTH)
        //    return Color::yellow();


        //auto raydir = ray.getDirection().copy();
        //bool inside = false;
        //if (traceResults.normal.dot(raydir) > 0) {
        //    // We're inside of object
        //    inside = true;
        //    traceResults.normal.scale(-1);
        //}
        //float ior = 1.1, eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
        //float cosi = -traceResults.normal.dot(raydir);
        //float k = 1 - eta * eta * (1 - cosi * cosi);
        //Vec3f refrdir = raydir * eta + traceResults.normal * (eta * cosi - sqrt(k));
        //refrdir.normalize();

        //Ray refractionRay{traceResults.closestHitPoint - traceResults.normal.copy().scale(10e-3), refrdir};
        //auto refractionColor = trace(refractionRay, objects, light, depth + 1);


        if (depth == MAX_RAY_DEPTH)
            return Color::yellow();


        const auto &I = ray.getDirection();
        const auto &N = traceResults.normal;

        float cosi = I.dot(N);
        float etai = 1, etat = 1.2f;
        Vec3f n = N;
        if (cosi < 0) {
            cosi = -cosi;
        } else {
            std::swap(etai, etat);
            n = N.copy().scale(-1);
        }
        float eta = etai / etat;
        float k = 1 - eta * eta * (1 - cosi * cosi);
        if (k < 0) {
            throw 3;
        }

        const Vec3f refractDir = I * eta + n * (eta * cosi - sqrtf(k)); 
        const Vec3f startPoint = traceResults.closestHitPoint - traceResults.normal.copy().scale(10e-2);
        const Vec3f endPoint = startPoint + refractDir;
        const Ray refractionRay{startPoint, endPoint};
        const auto refractionColor = trace(refractionRay, objects, light, depth + 1);


        // Transparent object
        return Color::mix(refractionColor, traceResults.closestObjectHit->getColor());
    } else {
        // Diffuse object
        // Offset hit point slightly in the direction of light to prevent the ray from colliding with the object itself
        const Vec3f lightDirection = (light.getPosition() - traceResults.closestHitPoint).normalize();
        traceResults.closestHitPoint.add(lightDirection.copy().scale(1e-3f));

        // Find closest object colliding with the ray
        auto shadowTraceResults = findFirstIntersectingObject(traceResults.closestHitPoint, light.getPosition(), objects);

        // If no object occludes the light, we see the color
        const float lightDistance2 = traceResults.closestHitPoint.dist2(light.getPosition());
        if (shadowTraceResults.closestObjectHit == nullptr || shadowTraceResults.closestDistanceToHitPoint2 > lightDistance2) {
            const float lightAngleFactor = std::max(0.f, traceResults.normal.dot(lightDirection));
            const Color &lightColor = light.getColor();
            const Color &objectColor = traceResults.closestObjectHit->getColor();
            return Color::mix(lightColor, objectColor).scale(lightAngleFactor);
        }

        // We are in shadow
        return Color::black();
    }
}