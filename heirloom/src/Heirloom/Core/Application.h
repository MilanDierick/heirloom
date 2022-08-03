// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_APPLICATION_H
#define HEIRLOOM_APPLICATION_H

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"
#include "Heirloom/ImGui/ImGuiLayer.h"

namespace Heirloom
{
	class Application
	{
	public:
		Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Close();

		[[maybe_unused]] [[nodiscard]] ImGuiLayer* GetImGuiLayer() const;
		static Application& Get();

		[[nodiscard]] Window& GetWindow() const;

	private:
		// Private application methods
		bool OnWindowClosedEvent([[maybe_unused]] WindowClosedEventArgs eventArgs);
		bool OnWindowResizedEvent(WindowResizedEventArgs eventArgs);

		// Application variables
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_IsRunning = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		static Application* m_pInstance;
	};

	Application* CreateApplication();
}

#endif //HEIRLOOM_APPLICATION_H
