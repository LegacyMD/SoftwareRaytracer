#include "object/Object.h"
#include "object/Sphere.h"
#include "object/Plane.h"
#include "util/Vector.h"
#include "util/Color.h"
#include "util/Ray.h"
#include "raytracer/RayTracer.h"
#include "raytracer/Camera.h"
#include "raytracer/Light.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include "TinyPngOut.hpp"

void go(uint8_t *pixels, size_t width, size_t height, size_t ymin, size_t ymax, const Camera &camera, const RayTracer::ObjectVector &spheres, const Light &light) {
    for (size_t y = ymin; y < ymax; y++) {
        for (size_t x = 0; x < width; x++) {
            const float screenX = static_cast<float>(x) - static_cast<float>(width) / 2;
            const float screenY = static_cast<float>(y) - static_cast<float>(height) / 2;
            if (x == 200 && y == 38) {
                int a = 0;
            }
            const Color color = RayTracer::renderPixel(camera, screenX, screenY, spheres, light);
            const auto arrayIndex = 3 * (y * height + x);
            pixels[arrayIndex + 0] = static_cast<uint8_t>(color.r * 255);
            pixels[arrayIndex + 1] = static_cast<uint8_t>(color.g * 255);
            pixels[arrayIndex + 2] = static_cast<uint8_t>(color.b * 255);
        }
    }
}

#include <thread>

void renderSpheres(const std::string &filename, const RayTracer::ObjectVector &spheres, const Light &light) {
    constexpr float screenZ = 0;
    constexpr int width = 400;
    constexpr int height = 400;
    const Camera camera{{0, 0, -1000}, {0, 0, 1}, {0, -1, 0}, 1000};

    std::ofstream file{filename, std::ios::binary};
    TinyPngOut pngout(static_cast<uint32_t>(width), static_cast<uint32_t>(height), file);
    uint8_t pixels[width * height * 3];

    std::thread t1(go, pixels, width, height, 0, 100, camera, spheres, light);
    std::thread t2(go, pixels, width, height, 100, 200, camera, spheres, light);
    std::thread t3(go, pixels, width, height, 200, 300, camera, spheres, light);
    std::thread t4(go, pixels, width, height, 300, 400, camera, spheres, light);
    t1.join();
    t2.join();
    t3.join();
    t4.join();


    //  go(pixels, width, height, 0, height - 1, camera, spheres, light);
    /* for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            const float screenX = static_cast<float>(x) - static_cast<float>(width) / 2;
            const float screenY = static_cast<float>(y) - static_cast<float>(height) / 2;
            if (x == 200 && y == 38) {
                int a = 0;
            }
            const Color color = RayTracer::renderPixel(camera, screenX, screenY, spheres, light);
            const auto arrayIndex = 3 * (y * height + x);
            pixels[arrayIndex + 0] = static_cast<uint8_t>(color.r * 255);
            pixels[arrayIndex + 1] = static_cast<uint8_t>(color.g * 255);
            pixels[arrayIndex + 2] = static_cast<uint8_t>(color.b * 255);
        }
    }*/
    pngout.write(pixels, width * height);
}

int main() {
    const int startFrame = 0;
    const int endFrame = 10;
    const float angle = 6.28f / static_cast<float>(endFrame - startFrame - 1);
    const float radius = 120.f;

    for (int i = startFrame; i < endFrame; i++) {
        const Vec3f lightPosition{(i * 0.1f) * radius * sin(i * angle), (i * 0.1f) * radius * cos(i * angle), 20.f};
        const Light light{lightPosition, Color{0.1f, 0.7f, 0.7f}};

        const Sphere s1{{-40.f, 0.f, 70.f}, 20.f, Color::blue()};
        const Sphere s2{{40.f, 0.f, 70.f}, 10.f, Color::green()};
        //    const Sphere s3{{40.f, 30.f, 70.f}, 10.f, Color::green()};
        //    const Sphere s4{{40.f, -30.f, 70.f}, 10.f, Color::green()};
        const Plane p1{{0.f, 0.f, 100.f}, {0.f, 0.f, -1.f}, Color::lightGray()};
        const RayTracer::ObjectVector objects{&p1, &s1, &s1};

        std::string filename = "out";
        filename.append(std::to_string(i));
        filename.append(".png");

        const auto startTime = std::chrono::steady_clock::now();
        renderSpheres(filename, objects, light);
        const auto endTime = std::chrono::steady_clock::now();
        std::cout << "Frame no. " << i << "\t time = " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms\n";
    }
    system("pause");
}
