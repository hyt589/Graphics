#include "Event.hpp"

namespace HYT
{
    Event::Event(EventType type) : m_eventType(type){}

    void EventQueue::push(Event e)
    {
        m_events.push(e);
    }

    void EventQueue::pop()
    {
        m_events.pop();
    }

    Event & EventQueue::front()
    {
        return m_events.front();
    }

    bool EventQueue::isEmpty() const
    {
        return m_events.empty();
    }

    void EventDispatcher::subscribe(EventType type, EventFn callback)
    {
        m_callbacks[type] = callback;
    }

    void EventDispatcher::post(Event event, EventQueue & queue)
    {
        queue.push(event);
    }

    void EventDispatcher::handle(Event & e)
    {
        auto type = e.getEventType();
        if (m_callbacks.find(type) == m_callbacks.end())
        {
            return;
        }
        auto callback = m_callbacks.at(type);
        e.isHandled = callback(e);
    }


} // namespace HYT::Core
