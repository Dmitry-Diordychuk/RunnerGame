//
// Created by ebona on 10.05.2022.
//

#include "Event.hpp"

namespace ft {
    void EventHandler::init(function<void(Ref<Event>)> windowEventFn, function<void(Ref<Event>)> keyEventFn)
    {
        m_eventCallbacks["WindowEventCallback"] = move(windowEventFn);
        m_eventCallbacks["KeyEventCallback"] = move(keyEventFn);
    }

    void EventHandler::update(const Ref<Event>& event) {
        if (event != nullptr && !event->isHandled()) {
            if (event->getEventCategory() == EventCategory::WindowEvent) {
                m_eventCallbacks["WindowEventCallback"](event);
                event->setHandled();
            }
            else if (event->getEventCategory() == EventCategory::KeyEvent) {
                m_eventCallbacks["KeyEventCallback"](event);
                event->setHandled();
            }
        }
    }
}