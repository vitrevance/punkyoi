#include <game/core.h>

#if (CURRENT_PLATFORM == PLATFORM_LINUX)

#include <game/platform/linux/window.h>

namespace punkyoi::platform::linux {

    int PlatformWindow::s_isWindowInit = 0;

    PlatformWindow::PlatformWindow(punkyoi_api::WindowProps windowProps, std::shared_ptr<punkyoi_api::events::EventBus> eventBus) {
        m_windowProps = windowProps;
        m_eventBus = eventBus;
        init();
    }

    PlatformWindow::~PlatformWindow() {
        dispose();
    }

    void PlatformWindow::setVSync(bool state) {

    }

    void PlatformWindow::onUpdate() {
        glfwPollEvents();
    }

    void PlatformWindow::onRenderPre() {
        glClearColor(0.02, 0.02, 0.02, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void PlatformWindow::onRenderPost() {
        glfwSwapBuffers(m_glfwWindow);
    }

    void PlatformWindow::init() {
        if (PlatformWindow::s_isWindowInit <= 0) {
            if (glfwInit()) {
                log::console() << "GLFW initialized" << log::endl;
            }
            else {
                log::console() << "GLFW initialization failed" << log::endl;
            }
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        PlatformWindow::s_isWindowInit++;
        m_glfwWindow = glfwCreateWindow(m_windowProps.width, m_windowProps.height, m_windowProps.title.c_str(),
            m_windowProps.isFullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
        if (!m_glfwWindow) {
            log::console() << "GLFW window creation failed" << log::endl;
        }
        glfwMakeContextCurrent(m_glfwWindow);
        glewExperimental = GL_TRUE;
        if (glewInit() == GLEW_OK) {
            log::console() << "GLEW initialized" << log::endl;
        }
        else {
            log::console() << "GLEW initialization failed" << log::endl;
        }
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetWindowUserPointer(m_glfwWindow, this);
        glfwSetKeyCallback(m_glfwWindow, key_callback);
        glfwSetWindowCloseCallback(m_glfwWindow, window_close_callback);
        glfwSetWindowSizeCallback(m_glfwWindow, window_size_callback);
        glfwSetWindowPosCallback(m_glfwWindow, window_moved_callback);
        glfwSetCursorPosCallback(m_glfwWindow, mouse_callback);
        glfwSetMouseButtonCallback(m_glfwWindow, mouse_button_callback);
    }

    void PlatformWindow::dispose() {
        PlatformWindow::s_isWindowInit--;
        glfwDestroyWindow(m_glfwWindow);
        if (PlatformWindow::s_isWindowInit <= 0) {
            glfwTerminate();
        }
    }

    void PlatformWindow::grabMouse() {
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void PlatformWindow::releaseMouse() {
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void PlatformWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        PlatformWindow* self = (PlatformWindow*)glfwGetWindowUserPointer(window);
        if (action == GLFW_PRESS) {
            punkyoi::events::KeyPressedEvent event(key, 0);
            self->m_eventBus->postEvent(event);
        }
        if (action == GLFW_REPEAT) {
            punkyoi::events::KeyPressedEvent event(key, 1);
            self->m_eventBus->postEvent(event);
        }
        if (action == GLFW_RELEASE) {
            punkyoi::events::KeyReleasedEvent event(key);
            self->m_eventBus->postEvent(event);
        }
    }

    void PlatformWindow::window_close_callback(GLFWwindow* window) {
        PlatformWindow* self = (PlatformWindow*)glfwGetWindowUserPointer(window);
        punkyoi::events::WindowClosedEvent event;
        self->m_eventBus->postEvent(event);
    }

    void PlatformWindow::window_size_callback(GLFWwindow* window, int width, int height) {
        PlatformWindow* self = (PlatformWindow*)glfwGetWindowUserPointer(window);
        punkyoi::events::WindowResizedEvent event(width, height);
        self->m_eventBus->postEvent(event);
    }

    void PlatformWindow::window_moved_callback(GLFWwindow* window, int x, int y) {
        PlatformWindow* self = (PlatformWindow*)glfwGetWindowUserPointer(window);
        punkyoi::events::WindowMovedEvent event(x, y);
        self->m_eventBus->postEvent(event);
    }

    void PlatformWindow::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        PlatformWindow* self = (PlatformWindow*)glfwGetWindowUserPointer(window);
        if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_NORMAL) {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            glfwSetCursorPos(window, width / 2, height / 2);
            punkyoi::events::MouseMovedEvent event(xpos - width / 2, ypos - height / 2);
            self->m_eventBus->postEvent(event);
        }
    }

    void PlatformWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
        PlatformWindow* self = (PlatformWindow*)glfwGetWindowUserPointer(window);
        if (action == GLFW_PRESS) {
            punkyoi::events::MouseButtonPressedEvent event(button);
            self->m_eventBus->postEvent(event);
        }
        else if (action == GLFW_RELEASE) {
            punkyoi::events::MouseButtonReleasedEvent event(button);
            self->m_eventBus->postEvent(event);
        }
    }

    int PlatformWindow::getWidth() {
        return m_windowProps.width;
    }

    int PlatformWindow::getHeight() {
        return m_windowProps.height;
    }

    bool PlatformWindow::isVSync() {
        return m_windowProps.isVSYNC;
    }

    bool PlatformWindow::isFullscreen() {
        return m_windowProps.isFullscreen;
    }
}
#endif
