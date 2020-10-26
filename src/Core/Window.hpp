#pragma once

#include "global.hpp"

namespace HYT
{

	/**
	 * @brief properties used to create a window
	 * 
	 */
    struct WindowProps
	{
		/**
		 * @brief Title of the window
		 * 
		 */
		std::string Title;

		/**
		 * @brief Width of the window
		 * 
		 */
		uint32_t Width;

		/**
		 * @brief Height of the window
		 * 
		 */
		uint32_t Height;

		WindowProps(const std::string& title = "Sandbox",
			        uint32_t width = 1280,
			        uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

    /**
     * @brief An abstract class that represents the application window. Implementation is dependent on platform.
     * 
     */
	class Window
    {
    public:
        Window(){};
		virtual ~Window(){};
        virtual void onUpdate() = 0;
        virtual void getSize(int & w, int & h) = 0;

		/**
		 * @brief Get the platform native window pointer
		 * 
		 * @return void* 
		 */
        virtual void* GetNativeWindow() const = 0;

		/**
		 * @brief Static function to create an application Window; should be implemented by platform specific code.
		 * 
		 * @param props properties of the window to be created
		 * @return Window* 
		 */
		static Window* Create(const WindowProps& props = WindowProps());
    protected:
		std::string m_title;
        EventDispatcher m_eventDispatcher;
    };
} // namespace HYT
