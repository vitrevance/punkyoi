#ifndef P_EVENT
#define P_EVENT

#include <functional>
#include <unordered_map>

namespace punkyoi_api::events {

    enum class EventType {
        None = 0,
        WindowClosed, WindowResized, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
        Tick, Render,
        EVENTTYPE_ITEMS
    };

    enum EventCategory {
        None                = 0,
        CategoryApp         = 1 << 0,
        CategoryWindow      = 1 << 1,
        CategoryInput       = 1 << 2,
        CategoryKey         = 1 << 3,
        CategoryMouse       = 1 << 4,
        CategoryMouseButton = 1 << 5
    };

    class Event {
    public:
        static EventType getStaticEventType() { return EventType::None; }

        virtual EventType getEventType() const = 0;
        virtual int getEventCategories() const = 0;
        virtual bool isEventInCategory(EventCategory category);

        bool isHandled();
        bool isCanceled();
        bool isCancelable();

        bool setCanceled(bool state);
        void setHandled();
    protected:
        bool m_isHandled = false;
        bool m_isCanceled = false;
        bool m_isCancelable = false;
    };

#define EVENT_CLASS_TYPE(type) virtual punkyoi_api::events::EventType getEventType() const override { return type; } static punkyoi_api::events::EventType getStaticEventType() { return type; }
#define EVENT_CLASS_CATEGORY(category) virtual int getEventCategories() const override { return category; }

    template<typename T>
    struct onEventWrapper {
        std::function<void(T&)> m_fun;
        inline onEventWrapper(std::function<void(T&)> fun) {
            this->m_fun = fun;
        }
        inline operator std::function<void(T&)>() const { return m_fun; }
    };

    class EventListenerBase {
    public:
        inline std::unordered_map<EventType, void*>& getEventType() {
            return this->m_eventTypes;
        }

    protected:
        std::unordered_map<EventType, void* > m_eventTypes;

        EventListenerBase() {}
        ~EventListenerBase() {}
    };

    template<typename T>
    class EventListener : virtual public EventListenerBase {
    public:
        EventListener() {
            static_assert(std::is_base_of<Event, T>::value, "T must inherit from Event");
            std::function<void(T&)> callback = std::bind(&EventListener<T>::onEvent, this, std::placeholders::_1);
            onEventWrapper<T>* fun = new onEventWrapper<T>(callback);
            this->m_eventTypes[T::getStaticEventType()] = (void*)fun;
        }

        virtual ~EventListener() {
            delete (onEventWrapper<T>*)this->m_eventTypes[T::getStaticEventType()];
            this->m_eventTypes.erase(T::getStaticEventType());
        }

        virtual void onEvent(T& event) = 0;
    };
}

#endif
