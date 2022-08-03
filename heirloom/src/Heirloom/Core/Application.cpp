// Author: Milan Dierick
// Solution: Heirloom

#include "hlpch.h"
#include "Application.h"
#include "Heirloom/Renderer/Renderer.h"

// TODO: No magic numbers, this should probably be in a settings object
#define MS_PER_TICK 1000.0F / 144.0F

namespace Heirloom
{
	Application* Application::m_pInstance = nullptr; //NOLINT

	Application::Application()
	{
		HL_PROFILE_FUNCTION()

		HL_CORE_ASSERT(!m_pInstance, "There can only be one application instance!")
		m_pInstance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->WindowResizedEvent += [this](auto&& args)
		{ OnWindowResizedEvent(std::forward<decltype(args)>(args)); };
		m_Window->WindowClosedEvent += [this](auto&& args)
		{ OnWindowClosedEvent(std::forward<decltype(args)>(args)); };

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer(); //NOLINT
		PushOverlay(m_ImGuiLayer); // TODO: Pass the shared pointer here
	}

// TODO: A cheap solution is to walk the list backwards when you update. That way removing an object only shifts items that were already updated.
	void Application::Run()
	{
		HL_PROFILE_FUNCTION()

		std::chrono::steady_clock::time_point previousTimePoint = std::chrono::steady_clock::now();
		double lag = 0.0;

		while (m_IsRunning)
		{
			HL_PROFILE_SCOPE("Frame")

			const std::chrono::time_point<std::chrono::steady_clock> currentTimePoint =
					std::chrono::steady_clock::now();

			const auto elapsedTime = std::chrono::time_point_cast<std::chrono::milliseconds>(currentTimePoint).
					time_since_epoch() - std::chrono::time_point_cast<std::chrono::milliseconds>(previousTimePoint).
					time_since_epoch();

			previousTimePoint = currentTimePoint;

			lag += elapsedTime.count();

			m_Window->OnUpdate();

			if (m_Minimized)
			{
				continue;
			}

			while (lag >= MS_PER_TICK)
			{
				{
					HL_PROFILE_SCOPE("LayerStack OnUpdate")

					for (Layer* layer: m_LayerStack)
					{
						layer->OnUpdate(Timestep{ 1000 / MS_PER_TICK });
					}
				}

				lag -= MS_PER_TICK;
			}

			{
				HL_PROFILE_SCOPE("LayerStack OnRender")

				for (Layer* layer: m_LayerStack)
				{
					layer->OnRender();
				}
			}

			m_ImGuiLayer->Begin();

			{
				HL_PROFILE_SCOPE("LayerStack OnImGuiRender")

				for (Layer* layer: m_LayerStack)
				{
					layer->OnImGuiRender();
				}
			}

			m_ImGuiLayer->End();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		HL_PROFILE_FUNCTION()

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		HL_PROFILE_FUNCTION()

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close()
	{
		m_IsRunning = false;
	}

	[[maybe_unused]] ImGuiLayer* Application::GetImGuiLayer() const
	{
		return m_ImGuiLayer;
	}

	Application& Application::Get()
	{
		return *m_pInstance;
	}

	Window& Application::GetWindow() const
	{
		return *m_Window;
	}

	bool Application::OnWindowClosedEvent([[maybe_unused]] const WindowClosedEventArgs eventArgs)
	{
		HL_PROFILE_FUNCTION()

		m_IsRunning = false;
		return true;
	}

	bool Application::OnWindowResizedEvent(const WindowResizedEventArgs eventArgs)
	{
		HL_PROFILE_FUNCTION()

		if (eventArgs.Width == 0 || eventArgs.Height == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(eventArgs.Width, eventArgs.Height);

		return false;
	}
}