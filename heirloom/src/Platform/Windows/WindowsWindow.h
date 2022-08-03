//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_WINDOWSWINDOW_H
#define HEIRLOOM_WINDOWSWINDOW_H

#include "GLFW/glfw3.h"

#include "Heirloom/Core/Window.h"
#include "Heirloom/Renderer/GraphicsContext.h"

namespace Heirloom
{
	class WindowsWindow final : public Window
	{
	public:
		explicit WindowsWindow(const WindowProps& props);
		~WindowsWindow() override;

		WindowsWindow(const WindowsWindow& other)                = delete;
		WindowsWindow(WindowsWindow&& other) noexcept            = delete;
		WindowsWindow& operator=(const WindowsWindow& other)     = delete;
		WindowsWindow& operator=(WindowsWindow&& other) noexcept = delete;

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetNativeWindow() const override { return m_Window; }

	private:
		void Init(const WindowProps& props);
		void Shutdown() const;

		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			Event<WindowResizedEventArgs>* WindowResizedEvent;
			Event<WindowClosedEventArgs>* WindowClosedEvent;
		};

		WindowData m_Data;
	};
}

#endif //HEIRLOOM_WINDOWSWINDOW_H
