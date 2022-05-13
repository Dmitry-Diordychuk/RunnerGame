//
// Created by ebona on 10.05.2022.
//

#ifndef EVENT_HPP
#define EVENT_HPP

#include <functional>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

namespace ft {
    enum EventType {
        None,
        WindowResize,
        WindowClose,
        KeyPress,
        KeyRelease
    };

    enum EventCategory {
        CustomEvent,
        WindowEvent,
        KeyEvent
    };

    class Event
    {
    public:
        EventType getEventType() const { return m_eventType; }
        EventCategory getEventCategory() const { return m_eventCategory; }
        bool isHandled() const { return m_isHandled; }
        void setHandled() { m_isHandled = true; }
        virtual ~Event() = default;

    protected:
        Event(EventType type, EventCategory category) : m_eventType(type), m_eventCategory(category) {}
        bool m_isHandled = false;
        EventType m_eventType = EventType::None;
        EventCategory m_eventCategory = EventCategory::CustomEvent;

    };

    class EventHandler
    {
    public:
        void init(std::function<void(std::shared_ptr<Event>)> windowEventFn, std::function<void(std::shared_ptr<Event>)> keyEventFn);

        void update(const std::shared_ptr<Event>& event);

    private:
        std::map<std::string, std::function<void(std::shared_ptr<Event>)>> m_eventCallbacks;
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(int width, int height) : Event(EventType::WindowResize, EventCategory::WindowEvent), m_width(width), m_height(height) {}

        int width() const { return m_width; }
        int height() const { return m_height; }
    private:
        int m_width;
        int m_height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() : Event(EventType::WindowClose, EventCategory::WindowEvent) {}

    private:
    };

    class KeyPressEvent : public Event
    {
    public:
        explicit KeyPressEvent(int key) : Event(EventType::KeyPress, EventCategory::KeyEvent), m_key(key) {}

        int key() const { return m_key; }
    private:
        int m_key;
    };

    class KeyReleaseEvent : public Event
    {
    public:
        explicit KeyReleaseEvent(int key) : Event(EventType::KeyRelease, EventCategory::KeyEvent), m_key(key) {}

        int key() const { return m_key; }
    private:
        int m_key;
    };
}


#endif //EVENT_HPP
