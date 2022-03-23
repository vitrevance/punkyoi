#pragma once

namespace punkyoi_api {

    struct WindowProps {
        std::string title;
        int width, height;
        bool isVSYNC;
        bool isFullscreen;
    };
    
    class IWindow {
    public:
        virtual ~IWindow() = default;

        virtual int getWidth() = 0;
        virtual int getHeight() = 0;

        virtual bool isVSync() = 0;
        virtual bool isFullscreen() = 0;

        virtual void grabMouse() = 0;
        virtual void releaseMouse() = 0;

        virtual void setVSync(bool state) = 0;

        virtual void onUpdate() = 0;
        virtual void onRenderPre() = 0;
        virtual void onRenderPost() = 0;
    };
}
