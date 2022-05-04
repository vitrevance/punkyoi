#ifndef P_MATH_UTILS
#define P_MATH_UTILS

#include "vec2d.h"

namespace punkyoi_api::math {

    template <typename T>
    bool between(const T& boundry1, const T& boundry2, const T& value) {
        return (boundry1 <= boundry2 && boundry1 <= value && value <= boundry2)
            || (boundry2 <= boundry1 && boundry2 <= value && value <= boundry1);
    }

    struct AABB {
        AABB(vec2 pos, vec2 size) : pos(pos), size(size) {}

        inline bool contains(vec2 point) {
            return between(pos.x + size.x / 2, pos.x - size.x / 2, point.x) && between(pos.y + size.y / 2, pos.y - size.y / 2, point.y);
        }

        vec2 pos;
        vec2 size;
    };
}

#endif