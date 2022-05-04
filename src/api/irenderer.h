#ifndef P_IRENDERER
#define P_IRENDERER

#include <api/irendercontext.h>
#include <api/iwindow.h>

namespace punkyoi_api {

    class IRenderer : public IRenderContext {
    public:
        virtual ~IRenderer() = default;

        virtual void init(IWindow*) = 0;
        virtual void deinit() = 0;
        virtual void onRenderPre() = 0;
        virtual void onRenderPost() = 0;
    };
}

#endif