#ifndef P_PLATFORM_RENDERER
#define P_PLATFORM_RENDERER

#include <game/core.h>
#include <api/irenderer.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace punkyoi::platform::linux {

    class PlatformRenderer : public ::punkyoi_api::IRenderer {
    public:
        using Shader = uint32_t;

        PlatformRenderer();
        virtual ~PlatformRenderer();

        virtual void init(::punkyoi_api::IWindow*) override;
        virtual void deinit() override;

        virtual void onRenderPre() override;
        virtual void onRenderPost() override;

        virtual void push() override;
        virtual void pop() override;
        virtual void translate(vec2 origin) override;
        virtual void scale(vec2 scale) override;
        virtual void rotate(float angle) override;
        virtual void drawImage(const ::punkyoi_api::IImage& image) override;

    protected:
        Shader createShader(std::string vertexText, std::string fragmentText);

        uint32_t m_quadVAO;
        Shader m_currentShader;
    };
}

#endif