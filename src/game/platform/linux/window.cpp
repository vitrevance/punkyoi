#include <core.h>

#if (CURRENT_PLATFORM == PLATFORM_LINUX)

#include <game/platform/linux/window.h>

namespace punkyoi::platform::linux {

    int LinuxWindow::s_isWindowInit = 0;

    LinuxWindow::LinuxWindow(WindowProps windowProps, std::shared_ptr<punkyoi_api::events::EventBus> eventBus) {
        m_windowProps = windowProps;
        m_eventBus = eventBus;
        init();
    }

    LinuxWindow::~LinuxWindow() {
        dispose();
    }

    void LinuxWindow::setVSync(bool state) {

    }

    void LinuxWindow::onUpdate() {
        glfwPollEvents();
    }

    void LinuxWindow::onRenderPre() {
        glClearColor(0.02, 0.02, 0.02, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void LinuxWindow::onRenderPost() {
        glfwSwapBuffers(m_glfwWindow);
    }

    void LinuxWindow::init() {
        if (LinuxWindow::s_isWindowInit <= 0) {
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
        LinuxWindow::s_isWindowInit++;
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

    void LinuxWindow::dispose() {
        LinuxWindow::s_isWindowInit--;
        glfwDestroyWindow(m_glfwWindow);
        if (LinuxWindow::s_isWindowInit <= 0) {
            glfwTerminate();
        }
    }

    void LinuxWindow::grabMouse() {
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void LinuxWindow::releaseMouse() {
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void LinuxWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        LinuxWindow* self = (LinuxWindow*)glfwGetWindowUserPointer(window);
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

    void LinuxWindow::window_close_callback(GLFWwindow* window) {
        LinuxWindow* self = (LinuxWindow*)glfwGetWindowUserPointer(window);
        punkyoi::events::WindowClosedEvent event;
        self->m_eventBus->postEvent(event);
    }

    void LinuxWindow::window_size_callback(GLFWwindow* window, int width, int height) {
        LinuxWindow* self = (LinuxWindow*)glfwGetWindowUserPointer(window);
        punkyoi::events::WindowResizedEvent event(width, height);
        self->m_eventBus->postEvent(event);
    }

    void LinuxWindow::window_moved_callback(GLFWwindow* window, int x, int y) {
        LinuxWindow* self = (LinuxWindow*)glfwGetWindowUserPointer(window);
        punkyoi::events::WindowMovedEvent event(x, y);
        self->m_eventBus->postEvent(event);
    }

    void LinuxWindow::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        LinuxWindow* self = (LinuxWindow*)glfwGetWindowUserPointer(window);
        if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_NORMAL) {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            glfwSetCursorPos(window, width / 2, height / 2);
            punkyoi::events::MouseMovedEvent event(xpos - width / 2, ypos - height / 2);
            self->m_eventBus->postEvent(event);
        }
    }

    void LinuxWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
        LinuxWindow* self = (LinuxWindow*)glfwGetWindowUserPointer(window);
        if (action == GLFW_PRESS) {
            punkyoi::events::MouseButtonPressedEvent event(button);
            self->m_eventBus->postEvent(event);
        }
        else if (action == GLFW_RELEASE) {
            punkyoi::events::MouseButtonReleasedEvent event(button);
            self->m_eventBus->postEvent(event);
        }
    }
}
#endif
