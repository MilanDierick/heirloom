// Author: Milan Dierick
// Solution: Heirloom

#include "hlpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Heirloom/Core/Application.h"

// Temporary
#include <GLFW/glfw3.h>

namespace Heirloom
{
	ImGuiLayer::ImGuiLayer()
			: Layer("ImGuiLayer")
	{
	}

	// ReSharper disable once CppMemberFunctionMayBeStatic
	void ImGuiLayer::OnAttach()
	{
		HL_PROFILE_FUNCTION()

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding              = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// io.Fonts->AddFontFromFileTTF("assets/fonts/Lingua.otf", 12);
		// io.Fonts->Build();

		Application& app   = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		HL_PROFILE_FUNCTION()

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate(Timestep)
	{
	}

	void ImGuiLayer::OnRender()
	{
	}

	void ImGuiLayer::OnImGuiRender()
	{
	}

	// ReSharper disable once CppMemberFunctionMayBeStatic
	void ImGuiLayer::Begin()
	{
		HL_PROFILE_FUNCTION()

		{
			HL_PROFILE_SCOPE("ImGui_ImplOpenGL3_NewFrame")
			ImGui_ImplOpenGL3_NewFrame();
		}

		{
			HL_PROFILE_SCOPE("ImGui_ImplGlfw_NewFrame")
			ImGui_ImplGlfw_NewFrame();
		}

		{
			HL_PROFILE_SCOPE("ImGui::NewFrame")
			ImGui::NewFrame();
		}
	}

	// ReSharper disable once CppMemberFunctionMayBeStatic
	void ImGuiLayer::End()
	{
		HL_PROFILE_FUNCTION()

		ImGuiIO& io      = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize   = ImVec2(static_cast<float>(app.GetWindow().GetWidth()),
				static_cast<float>(app.GetWindow().GetHeight()));

		{
			HL_PROFILE_SCOPE("ImGui::End Rendering")

			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		{
			HL_PROFILE_SCOPE("ImGui::End ViewportsConfig")

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
				{
					HL_PROFILE_SCOPE("ImGui::UpdatePlatformWindows()")
					ImGui::UpdatePlatformWindows();
				}
				{
					HL_PROFILE_SCOPE("ImGui::RenderPlatformWindowsDefault()")
					ImGui::RenderPlatformWindowsDefault();
				}
				{
					HL_PROFILE_SCOPE("ImGui::glfwMakeContextCurrent()")
					glfwMakeContextCurrent(backupCurrentContext);
				}
			}
		}
	}
}
