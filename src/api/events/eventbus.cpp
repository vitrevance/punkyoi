#include "eventbus.h"


namespace punkyoi_api::events {

    void EventBus::subscribeEventListener(const std::shared_ptr<EventListenerBase>& eventListener) {
        std::unordered_map<EventType, void*>& callbacks = eventListener->getEventType();
        std::unordered_map<EventType, void*>::iterator it = callbacks.begin();
        for (it = callbacks.begin(); it != callbacks.end(); it++) {
            m_subscribedEventListeners[it->first].insert(it->second);
        }
    }

    void EventBus::unsubscribeEventListener(const std::shared_ptr<EventListenerBase>& eventListener) {
        std::unordered_map<EventType, void*>& callbacks = eventListener->getEventType();
        std::unordered_map<EventType, void*>::iterator it = callbacks.begin();
        for (it = callbacks.begin(); it != callbacks.end(); it++) {
            m_subscribedEventListeners[it->first].erase(it->second);
        }
    }

    void EventBus::attachEventBus(const std::shared_ptr<EventBus>& subEventBus) {
        m_subEventBuses.insert(subEventBus);
    }

    void EventBus::detachEventBus(const std::shared_ptr<EventBus>& subEventBus) {
        m_subEventBuses.erase(subEventBus);
    }
}