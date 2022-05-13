//
// Created by ebona on 10.05.2022.
//

#include "Event.hpp"

#include <utility>

namespace ft {
    void EventHandler::init(std::function<void(std::shared_ptr<Event>)> windowEventFn, std::function<void(std::shared_ptr<Event>)> keyEventFn)
    {
        m_eventCallbacks["WindowEventCallback"] = std::move(windowEventFn);
        m_eventCallbacks["KeyEventCallback"] = std::move(keyEventFn);
    }

    void EventHandler::update(const std::shared_ptr<Event>& event) {
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