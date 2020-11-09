#pragma once

#include "global.hpp"
#include "Layer.hpp"
#include "Window.hpp"
#include "Log.hpp"

namespace HYT
{
    /**
     * @brief Application is a singleton class that contains a single instance of this application
     * 
     */
    class Application
    {
    public:
        virtual ~Application(){};

        /**
         * @brief Push a layer pointer to the layer stack.
         * 
         * @param layer pointer to the layer to push.
         */
        void pushLayer(Layer *layer);

        /**
         * @brief Find and pop a layer pointer from the stack.
         * 
         * @param layer layer pointer to pop.
         */
        void popLayer(Layer *layer);

        /**
         * @brief Pop the top layer from the stack
         * 
         */
        void popLayer();

        /**
         * @brief Push an overlay onto the layer stack.
         * 
         * @param layer pointer to the overlay layer.
         */
        void pushOverlay(Layer *layer);

        /**
         * @brief Find and pop an overlay from the stack.
         * 
         * @param layer overlay layer pointer to pop.
         */
        void popOverlay(Layer *layer);

        /**
         * @brief Pop the top layer from the overlay stack;
         * 
         */
        void popOverlay();

        /**
         * @brief Subscribe to a type of event with a provided callback.
         * 
         * @param type the type of event to subscribe to.
         * @param callback the function to be called when the event is handled.
         */
        void subscribe(EventType type, std::function<bool(Event &)> callback);

        /**
         * @brief Set whether the application should keep running.
         * 
         * @param should whether the application should run.
         */
        void setShouldRun(bool should);

        inline static bool isRunning() {return s_instance != nullptr;};

        /**
         * @brief start the application main cycle
         * 
         */
        void run();

        /**
         * @brief Get the Event Queue reference
         * 
         * @returns the reference to the application event queue 
         */
        EventQueue &getEventQueue();

        /**
         * @brief Get the Window object
         * 
         * @return Window* 
         */
        Window * getWindow();

        /**
         * @brief Get the application instance
         * 
         * @param name name of the application
         * @param width width of application window
         * @param height height of application window
         * @return Application* pointer to the application instance
         */
        static Application *getInstance(const std::string &name = "OpenGL Sandbox", uint32_t width = 1280, uint32_t height = 720, int verMajor = 4, int verMinor = 1);

    protected:
        /**
         * @brief handle events in the event queue
         * 
         */
        void handleEvents();
        Application() = default;

        bool m_initialized = false;
        bool m_running = true;
        std::vector<Layer *> m_layers;
        std::vector<Layer *> m_overlays;
        std::chrono::time_point<std::chrono::steady_clock> m_LastFrameTime;
        Scoped<Window> m_window;
        EventQueue m_eventQueue;
        EventDispatcher m_dispatcher;
        static Application *s_instance;
    };
} // namespace HYT

#define APP_EVENT_QUEUE ::HYT::Application::getInstance()->getEventQueue()
#define APP_INSTANCE ::HYT::Application::getInstance()
#define APP_WINDOW ::HYT::Application::getInstance()->getWindow()
#define APP_NATIVE_WINDOW ::HYT::Application::getInstance()->getWindow()->GetNativeWindow()
