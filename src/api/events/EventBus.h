#pragma once

#include "Event.h"
#include <set>
#include <unordered_set>
#include <vector>

namespace punkyoi_api {

	class EventBus {
	public:
		EventBus();
		~EventBus();

		void subscribeEventListener(EventListenerBase* eventListener);
		void unsubscribeEventListener(EventListenerBase* eventListener);

		void attachEventBus(EventBus* subEventBus);
		void detachEventBus(EventBus* subEventBus);

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
		std::unordered_set<EventBus*> m_subEventBuses;
	};
}
