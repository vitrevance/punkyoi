#ifndef P_PLATFORM_WINDOW
#define P_PLATFORM_WINDOW

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <game/core.h>
#include <api/iwindow.h>
#include <api/events/eventbus.h>
#include <game/events/game_events.h>

namespace punkyoi::platform::linux {

    class LinuxWindow : public ::punkyoi_api::IWindow {
    public:
        LinuxWindow(::punkyoi_api::WindowProps windowProps, std::shared_ptr<punkyoi_api::events::EventBus> eventBus);

        virtual ~LinuxWindow();

        void onUpdate() override;

        void onRenderPre() override;

        void onRenderPost() override;

        void setVSync(bool state) override;
        
        void grabMouse() override;

        void releaseMouse() override;

        virtual int getWidth() override;

        virtual int getHeight() override;

        virtual bool isVSync() override;

        virtual bool isFullscreen() override;

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static void window_close_callback(GLFWwindow* window);

        static void window_size_callback(GLFWwindow* window, int width, int height);

        static void window_moved_callback(GLFWwindow* window, int x, int y);

        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    protected:
        static int s_isWindowInit;
        punkyoi_api::WindowProps m_windowProps;
        GLFWwindow* m_glfwWindow;
        std::shared_ptr<punkyoi_api::events::EventBus> m_eventBus;

        void init();
        void dispose();
    };
}

#endif
