#pragma once

#include "global.hpp"
#include <magic_enum.hpp>

namespace HYT
{
    enum class EventType
    {
        None = 0,
        WindowCloseEvent, WindowResizeEvent,
        KeyPressEvent, KeyReleaseEvent, KeyRepeatEvent,
        MouseButtonPressEvent, MouseButtonReleaseEvent, MouseButtonRepeatEvent,
        CursorPosEvent,
        ScrollEvent
    };

    class Event
    {
    public:
        //@brief Create an event instance
        //@param type: the type of the event
        //@param data: any type of event data
        Event(EventType type, std::any data = NULL);

        //@brief whether or not this event is properly handled
        bool isHandled = false;

        //@returns the type enum of this event
        inline EventType getEventType() const
        {
            return m_eventType;
        };

        //@returns the string representation of this event
        std::string to_string();

        //@returns data relevant to this event
        std::any getData();

    private:
        const EventType m_eventType;
        std::any m_eventData;
    };

    ///@brief a FIFO queue of events. 
    //Events are pushed into a queue before they are handled in chronological order
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

    /**
     * @brief Event Dispatcher is the object that manages events
     * 
     */
    class EventDispatcher
    {
    public:
        using EventFn = std::function<bool(Event &)>;

        //@brief Attach a handle callback to an event type
        //@param type: the type enum
        //@param callback: a function that gets called when the event is handled.
        //  A boolean value should be returned indicating weather this event is consumed by this function.
        //  You should not post new events in this callback.
        void subscribe(EventType type, EventFn callback);

        //@brief Post an event to an event queue
        //@param event: the event instance to post
        //@param queue: the reference to the event queue where the event will be posted
        void post(Event event, EventQueue & queue);

        //@brief handle an event according to subscribed callbacks
        //@param event: the reference to the event being handled
        void handle(Event & Event);

    protected:
        std::unordered_map<EventType, EventFn> m_callbacks;
    };

} // namespace HYT::Core