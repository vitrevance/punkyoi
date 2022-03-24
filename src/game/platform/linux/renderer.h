#ifndef P_PLATFORM_RENDERER
#define P_PLATFORM_RENDERER

#include <game/core.h>
#include <map>
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
        virtual void drawImage(::punkyoi_api::IImage& image) override;

    protected:
        Shader createShader(std::string vertexText, std::string fragmentText);

        ::punkyoi_api::IWindow* m_window;
        uint32_t m_quadVAO;
        Shader m_currentShader;
        std::map<void*, unsigned int> m_texturesMap;
        std::vector<mat4> m_matrices;
        vec2 m_windowRatio;
    };
}

#endif