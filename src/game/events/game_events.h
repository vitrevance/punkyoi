#pragma once

#include <api/events/event.h>
#include <api/irendercontext.h>

namespace punkyoi::events {

    using punkyoi_api::events::Event;
    using punkyoi_api::events::EventType;
    using punkyoi_api::events::EventCategory;

    class KeyEvent : public Event {
	public:
		inline int getKeyCode() {
            return m_keyCode;
        }
	protected:
		int m_keyCode;

		KeyEvent(int keyCode) : m_keyCode(keyCode) {}
		~KeyEvent() {}

		EVENT_CLASS_CATEGORY(EventCategory::CategoryInput | EventCategory::CategoryKey)
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_repeatCount(repeatCount) {}
		~KeyPressedEvent() {}

		inline int getRepeatCount() {
            return m_repeatCount;
        }
		
		EVENT_CLASS_TYPE(EventType::KeyPressed)

	protected:
		int m_repeatCount;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}
		~KeyReleasedEvent() {}

		EVENT_CLASS_TYPE(EventType::KeyReleased)
	};

    class WindowResizedEvent : public Event {
	public:
		WindowResizedEvent(int width, int height) : m_width(width), m_height(height) {}
		~WindowResizedEvent() {}

		inline int getWidth() { return m_width; }
		inline int getHeight() { return m_height; }

		EVENT_CLASS_CATEGORY(EventCategory::CategoryWindow)
		EVENT_CLASS_TYPE(EventType::WindowResized)

	protected:
		int m_width, m_height;
	};

	class WindowMovedEvent : public Event {
	public:
		WindowMovedEvent(int x, int y) : m_x(x), m_y(y) {}
		~WindowMovedEvent() {}

		inline int getX() { return m_x; }
		inline int getY() { return m_y; }

		EVENT_CLASS_CATEGORY(EventCategory::CategoryWindow)
		EVENT_CLASS_TYPE(EventType::WindowMoved)

	protected:
		int m_x, m_y;
	};

	class WindowClosedEvent : public Event {
	public:
		WindowClosedEvent() {}
		~WindowClosedEvent() {}

		EVENT_CLASS_CATEGORY(EventCategory::CategoryWindow)
		EVENT_CLASS_TYPE(EventType::WindowClosed)
	};

	class WindowLostFocusEvent : public Event {
	public:
		WindowLostFocusEvent() {}
		~WindowLostFocusEvent() {}

		EVENT_CLASS_CATEGORY(EventCategory::CategoryWindow)
		EVENT_CLASS_TYPE(EventType::WindowLostFocus)
	};

    class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}
		~MouseMovedEvent() {}

		inline float getX() { return m_mouseX; }
		inline float getY() { return m_mouseY; }

		EVENT_CLASS_TYPE(EventType::MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategory::CategoryInput | EventCategory::CategoryMouse)

	protected:
		float m_mouseX, m_mouseY;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}
		~MouseScrolledEvent() {}

		inline float getXOffset() { return m_xOffset; }
		inline float getYOffset() { return m_yOffset; }

		EVENT_CLASS_CATEGORY(EventCategory::CategoryInput | EventCategory::CategoryMouse)
		EVENT_CLASS_TYPE(EventType::MouseScrolled);
	protected:
		float m_xOffset, m_yOffset;
	};

	class MouseButtonEvent : public Event {
	public:
		inline int getButton() { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategory::CategoryInput | EventCategory::CategoryMouse | EventCategory::CategoryMouseButton);
	protected:
		MouseButtonEvent(int button) : m_button(button) {}
		~MouseButtonEvent() {}

		int m_button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}
		~MouseButtonPressedEvent() {}

		EVENT_CLASS_TYPE(EventType::MouseButtonPressed);
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}
		~MouseButtonReleasedEvent() {}

		EVENT_CLASS_TYPE(EventType::MouseButtonReleased);
	};

	class TickEvent : public Event {
	public:
		TickEvent(float deltaTime) : m_deltaTime(deltaTime) {}
		~TickEvent() {}

		inline float getDeltaTime() { return m_deltaTime; }

		EVENT_CLASS_CATEGORY(EventCategory::CategoryApp)
		EVENT_CLASS_TYPE(EventType::Tick)

	protected:
		float m_deltaTime;
	};

	class RenderEvent : public Event {
	public:
		RenderEvent(punkyoi_api::IRenderContext& ctx) : m_context(ctx) {}
		~RenderEvent() {}

		inline punkyoi_api::IRenderContext& getContext() { return m_context; }

		EVENT_CLASS_CATEGORY(EventCategory::CategoryApp)
		EVENT_CLASS_TYPE(EventType::Render)

	protected:
		punkyoi_api::IRenderContext& m_context;
	};

	class GameStateEvent : public Event {
	public:
		GameStateEvent(int state) : m_state(state) {}
		~GameStateEvent() {}

		inline int getState() { return m_state; }

		EVENT_CLASS_CATEGORY(EventCategory::CategoryApp)
		EVENT_CLASS_TYPE(EventType::State)
	protected:
		int m_state;
	};
}