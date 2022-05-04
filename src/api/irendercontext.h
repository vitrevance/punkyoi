#ifndef P_IRENDERCONTEXT
#define P_IRENDERCONTEXT

#include "math/vec2d.h"
#include "iimage.h"

namespace punkyoi_api {

    class IRenderContext {
    public:
        virtual ~IRenderContext() = default;

        virtual void push() = 0;
        virtual void pop() = 0;
        virtual void translate(math::vec2 origin) = 0;
        virtual void scale(math::vec2 scale) = 0;
        virtual void rotate(float angle) = 0;
        virtual void drawImage(IImage& image) = 0;
    };
}

#endif
