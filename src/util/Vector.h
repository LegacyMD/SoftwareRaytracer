#pragma once

#include <cmath>

template <typename T>
struct Vec3 {
    T x, y, z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    Vec3(const Vec3<T> &) = default;
    Vec3(Vec3<T> &&) = default;
    Vec3<T> &operator=(const Vec3<T> &) = default;
    Vec3<T> &operator=(Vec3<T> &&) = default;

    // Getter methods
    Vec3<T> copy() const {
        return Vec3<T>{*this};
    }
    static T len2(T x, T y, T z) {
        return x * x + y * y + z * z;
    }
    static T len(T x, T y, T z) {
        return sqrt(len2(x, y, z));
    }
    T len2() const {
        return len2(x, y, z);
    }
    T len() const {
        return len(x, y, z);
    }
    T dist2(const Vec3<T> &other) const {
        const T x = this->x - other.x;
        const T y = this->y - other.y;
        const T z = this->z - other.z;
        return len2(x, y, z);
    }
    T dist(const Vec3<T> &other) const {
        return sqrt(dist2(other));
    }

    // Miscellaneous methods changing existing objects
    Vec3<T> &normalize() {
        T length = len();
        x /= length;
        y /= length;
        z /= length;
        return *this;
    }
    Vec3<T> &set(T argX, T argY, T argZ) {
        this->x = argX;
        this->y = argY;
        this->z = argZ;
        return *this;
    }
    Vec3<T> &set(const Vec3<T> &other) {
        return set(other.x, other.y, other.z);
    }

    // Arithmetic operations changing existing objects
    Vec3<T> &add(const Vec3<T> &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    Vec3<T> &subtract(const Vec3<T> &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    Vec3<T> &scale(T arg) {
        x *= arg;
        y *= arg;
        z *= arg;
        return *this;
    }

    // Arithmetic operations creating new objects
    Vec3<T> operator+(const Vec3<T> &other) const {
        Vec3<T> result{*this};
        result.add(other);
        return result;
    }
    Vec3<T> operator-(const Vec3<T> &other) const {
        Vec3<T> result{*this};
        result.subtract(other);
        return result;
    }
    Vec3<T> operator*(float factor) const {
        Vec3<T> result{*this};
        result.scale(factor);
        return result;
    }

    // Vector multiplication
    T dot(const Vec3<T> &other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    Vec3<T> cross(const Vec3<T> &other) const {
        const T x = this->y * other.z - this->z * other.y;
        const T y = this->z * other.x - this->x * other.z;
        const T z = this->x * other.y - this->y * other.x;
        return Vec3<T>{x, y, z};
    }
};

using Vec3f = Vec3<float>;
