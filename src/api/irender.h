#ifndef P_IRENDER
#define P_IRENDER

#include "irendercontext.h"

namespace punkyoi_api {

    class IRenderBase {
    public:
        virtual ~IRenderBase() = default;
        virtual void render(void*, IRenderContext&) = 0;
    };

    template<class RenderTarget>
    class IRender : public IRenderBase {
    public:
        virtual ~IRender() = default;
        
        virtual void render(void* ptr, IRenderContext& context) override {
            render(*static_cast<RenderTarget*>(ptr), context);
        }

        virtual void render(RenderTarget&, IRenderContext&) = 0;
    };
}

#endif
