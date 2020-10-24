#include "Event.hpp"

namespace HYT
{
    Event::Event(EventType type, std::any data)
        : m_eventType(type), eventData(data)
    {
    }

    std::string Event::to_string()
    {
        return std::string(magic_enum::enum_name(m_eventType));
    }

    void EventQueue::push(Event e)
    {
        m_events.push(e);
    }

    void EventQueue::pop()
    {
        m_events.pop();
    }

    Event &EventQueue::front()
    {
        return m_events.front();
    }

    bool EventQueue::isEmpty() const
    {
        return m_events.empty();
    }

    int EventQueue::size() const
    {
        return m_events.size();
    }

    void EventDispatcher::subscribe(EventType type, EventFn callback)
    {
        m_callbacks[type] = callback;
    }

    void EventDispatcher::post(Event event, EventQueue &queue)
    {
        queue.push(event);
    }

    void EventDispatcher::handle(Event &e)
    {
        auto type = e.getEventType();
        if (m_callbacks.find(type) == m_callbacks.end())
        {
            return;
        }
        auto callback = m_callbacks.at(type);
        e.isHandled = callback(e);
    }

} // namespace HYT
