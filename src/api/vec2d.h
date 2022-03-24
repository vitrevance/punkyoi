#ifndef P_VEC2
#define P_VEC2

#include <cmath>

namespace punkyoi_api::math {
    
    class vec2 {
    public:
        vec2();
        explicit vec2(float v);
        vec2(float x, float y);

        vec2& operator+=(const vec2& rhs);
        vec2& operator-=(const vec2& rhs);
        vec2& operator*=(float rhs);
        vec2& operator/=(float rhs);
        vec2 operator-() const;
        bool operator==(const vec2& rhs) const;
        bool operator!=(const vec2& rhs) const;
        float dot(const vec2& rhs) const;
        float length() const;
        vec2& normalize();
        vec2 normalized() const;
        vec2 left() const;

        float x;
        float y;
    };

    vec2 operator+(const vec2& lhs, const vec2& rhs);
    vec2 operator-(const vec2& lhs, const vec2& rhs);
    vec2 operator*(const vec2& lhs, float rhs);
    vec2 operator/(const vec2& lhs, float rhs);
    vec2 operator*(float lhs, const vec2& rhs);
    vec2 operator/(float lhs, const vec2& rhs);
}

#endif