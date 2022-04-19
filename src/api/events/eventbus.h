#ifndef P_EVENTBUS
#define P_EVENTBUS

#include "event.h"
#include <set>
#include <unordered_map>
#include <list>
#include <memory>

namespace punkyoi_api::events {

    class EventBus {
    public:
        EventBus() = default;
        ~EventBus() = default;

        void subscribeEventListener(const std::shared_ptr<EventListenerBase>& eventListener);

        void unsubscribeEventListener(const std::shared_ptr<EventListenerBase>& eventListener);

        void subscribeEventListener(EventListenerBase* eventListener);

        void unsubscribeEventListener(EventListenerBase* eventListener);

        void attachEventBus(const std::shared_ptr<EventBus>& subEventBus);

        void detachEventBus(const std::shared_ptr<EventBus>& subEventBus);

        template<typename T>
        void postEvent(T& event) {
            if (m_subscribedEventListeners.count(T::getStaticEventType())) {
                std::set<void*>& callbacks = m_subscribedEventListeners[T::getStaticEventType()];
                for (void* it : callbacks) {
                    std::function<void(T&)> callback = *((onEventWrapper<T>*)it);
                    callback(event);
                }
            }

            if (m_subscribedEventListeners.count(EventType::None)) {
                std::set<void*>& callbacks = m_subscribedEventListeners[EventType::None];
                for (void* it : callbacks) {
                    std::function<void(Event&)> callback = *((onEventWrapper<Event>*)it);
                    callback(event);
                }
            }

            for (std::shared_ptr<EventBus>& it : m_subEventBuses) {
                it->postEvent(event);
            }
        }

        template<typename... Args>
        static void release_ptr(Args...) {
        }

    private:
        std::unordered_map<EventType, std::set<void*> > m_subscribedEventListeners;
        std::list<std::shared_ptr<EventBus> > m_subEventBuses;
    };
}

#endif
