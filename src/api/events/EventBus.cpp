#include "EventBus.h"

namespace punkyoi_api {

	EventBus::EventBus() {
	}


	EventBus::~EventBus() {
	}
	
	void EventBus::subscribeEventListener(EventListenerBase* eventListener) {
		std::unordered_map<EventType, void*>& callbacks = eventListener->getEventType();
		std::unordered_map<EventType, void*>::iterator it = callbacks.begin();
		for (it = callbacks.begin(); it != callbacks.end(); it++) {
			m_subscribedEventListeners[it->first].insert(it->second);
		}
	}

	void EventBus::unsubscribeEventListener(EventListenerBase* eventListener) {
		std::unordered_map<EventType, void*>& callbacks = eventListener->getEventType();
		std::unordered_map<EventType, void*>::iterator it = callbacks.begin();
		for (it = callbacks.begin(); it != callbacks.end(); it++) {
			m_subscribedEventListeners[it->first].erase(it->second);
		}
	}

	void EventBus::attachEventBus(EventBus* subEventBus) {
		m_subEventBuses.insert(subEventBus);
	}

	void EventBus::detachEventBus(EventBus* subEventBus) {
		m_subEventBuses.erase(subEventBus);
	}
}