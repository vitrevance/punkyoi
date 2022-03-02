#pragma once

#include "vec2d.h"
#include <cmath>

namespace punkyoi_api {
	
	vec2::vec2() : x(0), y(0) {}
	vec2::vec2(float v) : x(v), y(v) {}
	vec2::vec2(float x, float y) : x(x), y(y) {}

	vec2& vec2::operator+=(const vec2& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	vec2& vec2::operator-=(const vec2& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	vec2& vec2::operator*=(float rhs) {
		x *= rhs;
		y *= rhs;
		return *this;
	}

	vec2& vec2::operator/=(float rhs) {
		x /= rhs;
		y /= rhs;
		return *this;
	}

	vec2 vec2::operator-() const {
		return vec2(-x, -y);
	}

	float vec2::dot(const vec2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	float vec2::length() const {
		return std::sqrt(x * x + y * y);
	}

	vec2& vec2::normalize() {
		return (*this) /= length();
	}

	vec2 vec2::normalized() const {
		return vec2(*this).normalize();
	}

	vec2 operator+(const vec2& lhs, const vec2& rhs) {
		return vec2(lhs) += rhs;
	}

	vec2 operator-(const vec2& lhs, const vec2& rhs) {
		return vec2(lhs) -= rhs;
	}

	vec2 operator*(const vec2& lhs, float rhs) {
		return vec2(lhs) *= rhs;
	}

	vec2 operator/(const vec2& lhs, float rhs) {
		return vec2(lhs) /= rhs;
	}

	vec2 operator*(float lhs, const vec2& rhs) {
		return vec2(rhs) *= lhs;
	}

	vec2 operator/(float lhs, const vec2& rhs) {
		return vec2(rhs) /= lhs;
	}
}
