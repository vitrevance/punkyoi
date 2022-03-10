#pragma once

#include "event.h"
#include <set>
#include <unordered_set>
#include <vector>
#include <memory>

namespace punkyoi_api::events {

    class EventBus {
    public:
        EventBus() = default;
        ~EventBus() = default;

        void subscribeEventListener(const std::shared_ptr<EventListenerBase>& eventListener) {
            std::unordered_map<EventType, void*>& callbacks = eventListener->getEventType();
            std::unordered_map<EventType, void*>::iterator it = callbacks.begin();
            for (it = callbacks.begin(); it != callbacks.end(); it++) {
                m_subscribedEventListeners[it->first].insert(it->second);
            }
        }

        void unsubscribeEventListener(const std::shared_ptr<EventListenerBase>& eventListener) {
            std::unordered_map<EventType, void*>& callbacks = eventListener->getEventType();
            std::unordered_map<EventType, void*>::iterator it = callbacks.begin();
            for (it = callbacks.begin(); it != callbacks.end(); it++) {
                m_subscribedEventListeners[it->first].erase(it->second);
            }
        }

        void attachEventBus(const std::shared_ptr<EventBus>& subEventBus) {
            m_subEventBuses.insert(subEventBus);
        }

        void detachEventBus(const std::shared_ptr<EventBus>& subEventBus) {
            m_subEventBuses.erase(subEventBus);
        }

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

            for (EventBus* it : m_subEventBuses) {
                it->postEvent(event);
            }
        }

    private:
        std::unordered_map<EventType, std::set<void*> > m_subscribedEventListeners;
        std::unordered_set<std::shared_ptr<EventBus> > m_subEventBuses;
    };
}
