#pragma once

#include "irendercontext.h"

namespace punkyoi_api {

	template<class RenderTarget>
	class IRender {
	public:
		virtual IRender(const IRenderContext& renderContext) = 0;
		virtual ~IRender() = 0;

		virtual void render(RenderTarget& target) = 0;
		virtual IRenderContext& context() = 0;
	};
}
