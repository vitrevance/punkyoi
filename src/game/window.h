#pragma once

#include <game/core.h>
#include <api/iwindow.h>

namespace punkyoi {

    struct WindowProps {
        std::string title;
        int width, height;
        bool isVSYNC;
        bool isFullscreen;
    };

    class Window : public punkyoi_api::IWindow {
    public:
        virtual ~Window() {};

        static WindowProps getDefaultWindowProps() {
            return WindowProps{ "App", 1280, 720, false, false };
        }

        virtual int getWidth() override {
            return m_windowProps.width;
        }

        virtual int getHeight() override {
            return m_windowProps.height;
        }

        virtual bool isVSync() override {
            return m_windowProps.isVSYNC;
        }

        virtual bool isFullscreen() override {
            return m_windowProps.isFullscreen;
        }

        virtual void grabMouse() = 0;
        virtual void releaseMouse() = 0;

        virtual void setVSync(bool state) = 0;
        virtual void onUpdate() = 0;
        virtual void onRenderPre() = 0;
        virtual void onRenderPost() = 0;

        WindowProps m_windowProps;
    protected:
        inline Window() {};
    };
}