#pragma once

#include "global.hpp"

namespace HYT
{

    struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Sandbox",
			        uint32_t width = 1280,
			        uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

    class Window
    {
    public:
        Window();
		virtual ~Window();
        virtual void onUpdate() = 0;
        virtual void getSize(int & w, int & h);
        virtual void* GetNativeWindow() const = 0;
    protected:
		std::string m_title;
		uint32_t m_width, m_height;
    };
} // namespace HYT
