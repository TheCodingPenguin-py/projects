#pragma once
#include <cmath>
#include <iostream>

namespace Engine {
    struct Vec2 {
        float x, y;

        // Compound assignments inside the struct (8 bytes total size)
        inline Vec2& operator+=(const Vec2& b) { x += b.x; y += b.y; return *this; }
        inline Vec2& operator-=(const Vec2& b) { x -= b.x; y -= b.y; return *this; }
        inline Vec2& operator*=(float s) { x *= s;   y *= s;   return *this; }
    };
    struct AABB {
        Vec2 min; // The "smallest" corner (top-left: 0,0)
        Vec2 max; // The "largest" corner (bottom-right: 100,100)

        // Check if a point is inside
        inline bool contains(Vec2 p) const {
            return (p.x >= min.x && p.x <= max.x &&
                p.y >= min.y && p.y <= max.y);
        }

        // Check if another box overlaps this one
        inline bool overlaps(const AABB& b) const {
            // "Is NOT separated on X" AND "is NOT separated on Y"
            return (min.x <= b.max.x && max.x >= b.min.x) &&
                (min.y <= b.max.y && max.y >= b.min.y);
        }
    };


    // Standard raw dot product
    inline float dot(Vec2 a, Vec2 b) {
        return (a.x * b.x) + (a.y * b.y);
    }

    // Optimized: Returns squared length to skip the slow sqrt()
    inline float length(Vec2 a) {
        return dot(a, a);
    }

    // Scales a vector to a length of 1.0
    inline Vec2 normalize(Vec2 a) {
        float lenSq = length(a);
        if (lenSq > 0) {
            // We must use sqrt here because normalization requires the real magnitude
            float actualLen = std::sqrt(lenSq);
            return { a.x / actualLen, a.y / actualLen };
        }
        return { 0, 0 };
    }

    inline Vec2 rotate(Vec2 a, float angle) {
        float c = std::cos(angle);
        float s = std::sin(angle);
        return { (a.x * c) - (a.y * s), (a.x * s) + (a.y * c) };
    }

    inline float dot_norm(Vec2 a, Vec2 b) {
        return dot(normalize(a), normalize(b));
    }

    template <typename T>
    inline T input(const char* message) {
        std::cout << message << std::flush;
        T val;
        std::cin >> val;
        return val;
    }

    // Arithmetic Operators using the new struct logic
    inline Vec2 operator+(Vec2 a, const Vec2& b) { return a += b; }
    inline Vec2 operator-(Vec2 a, const Vec2& b) { return a -= b; }
    inline Vec2 operator*(Vec2 a, float s) { return a *= s; }
    inline Vec2 operator*(float s, Vec2 a) { return a *= s; }

} // namespace Engine
