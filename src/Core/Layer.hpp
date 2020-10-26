#pragma once

#include "global.hpp"
#include "Event.hpp"

namespace HYT
{
    /**
     * @brief An execution layer of the application
     * 
     */
    class Layer
    {
    public:
        /**
         * @brief a layer is initialized when it is pushed into the stack
         * 
         */
        virtual void init() {};

        /**
         * @brief actions to perform during each frame
         * 
         * @param seconds time in seconds from last frame
         */
        virtual void onUpdate(float seconds) {};

        /**
         * @brief a layer is terminated when it is poped from the stack
         * 
         */
        virtual void terminate() {};

        /**
         * @brief actions to perform when an event has occured
         * 
         * @param e 
         */
        virtual void onEvent(Event &e) {};

        /**
         * @brief subscribe to a particular type of event
         * 
         * @param type the event type to subscribe to
         * @param callback the function to call when an event of subscribed type has occured
         */
        inline void subscribe(EventType type, std::function<bool(Event&)> callback)
        {
            m_eventDispatcher.subscribe(type, callback);
        };

    protected:
        EventDispatcher m_eventDispatcher;
    };
} // namespace HYT
