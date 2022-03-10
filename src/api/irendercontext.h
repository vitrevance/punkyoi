#pragma once

#include "vec2d.h"
#include "iimage.h"

namespace punkyoi_api {

	class IRenderContext {
	public:
		virtual ~IRenderContext() = 0;

		virtual void push() = 0;
		virtual void pop() = 0;
		virtual void translate(vec2 origin) = 0;
		virtual void scale(vec2 scale) = 0;
		virtual void rotate(float angle) = 0;
		virtual void drawImage(const IImage& image) = 0;
	};
}
