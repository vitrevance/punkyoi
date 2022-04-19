#include "event.h"

namespace punkyoi_api::events {

    bool Event::isEventInCategory(EventCategory category) { return getEventCategories() & category; }
    bool Event::isHandled() { return m_isHandled; }
    bool Event::isCanceled() { return m_isCanceled; }
    bool Event::isCancelable() { return m_isCancelable; }

    bool Event::setCanceled(bool state) {m_isCanceled = m_isCancelable && state; return m_isCancelable; }
    void Event::setHandled() { m_isHandled = true; }
}