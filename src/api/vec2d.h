#pragma once

namespace punkyoi_api {
	
	class vec2 {
	public:
		vec2();
		vec2(float v);
		vec2(float x, float y);

		vec2& operator+=(const vec2& rhs);
		vec2& operator-=(const vec2& rhs);
		vec2& operator*=(float rhs);
		vec2& operator/=(float rhs);
		vec2 operator-() const;
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
	vec2 operator*(const vec2& lhs, const vec2& rhs);
	vec2 operator/(const vec2& lhs, const vec2& rhs);
	vec2 operator*(float lhs, const vec2& rhs);
	vec2 operator*(float lhs, const vec2& rhs);
}
