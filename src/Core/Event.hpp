#pragma once

#include "global.hpp"
#include <magic_enum.hpp>

namespace HYT
{
    enum class EventType
    {
        None = 0,
        WindowCloseEvent
    };

    class Event
    {
    public:
        Event(EventType et, std::any data = NULL);
        bool isHandled = false;
        inline EventType getEventType() const
        {
            return m_eventType;
        };
        std::string to_string();
        std::any eventData;

    private:
        const EventType m_eventType;
    };

    //Event is pushed into a queue before they are handled in chronological order
    class EventQueue
    {
    public:
        //Push an event to the back of the queue
        void push(Event e);

        //Pop the first event in the que
        void pop();

        //Get the reference if the first event in queue
        Event& front();

        //Check if the queue is empty
        bool isEmpty() const;

        int size() const;
    protected:
        std::queue<Event> m_events;
    };

    class EventDispatcher
    {
    public:
        using EventFn = std::function<bool(Event &)>;

        //Attach a handle callback to an event type
        void subscribe(EventType type, EventFn callback);

        //Post an event to an event queue
        void post(Event event, EventQueue & queue);

        //handle an event according to subscribed EventType
        void handle(Event & Event);

    protected:
        std::unordered_map<EventType, EventFn> m_callbacks;
    };

} // namespace HYT::Core