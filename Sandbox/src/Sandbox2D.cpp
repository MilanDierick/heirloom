#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"),
	  m_CameraController(1280.0f / 960.0f, false)
{
}

void Sandbox2D::OnAttach()
{
	HL_PROFILE_FUNCTION()

	m_BackgroundTexture = Heirloom::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Logo              = Heirloom::Texture2D::Create("assets/textures/logo.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(const Heirloom::Timestep)
{
	HL_PROFILE_FUNCTION()

	m_CameraController.Update(Heirloom::Timestep{0.016f});

	if (Heirloom::Input::IsKeyPressed(Heirloom::KeyCode::Escape))
	{
		Heirloom::Application::Get().Close();
	}
}

void Sandbox2D::OnRender()
{
	Heirloom::Renderer2D::ResetStats();

	Heirloom::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Heirloom::RenderCommand::Clear();

	Heirloom::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Heirloom::Renderer2D::DrawRotatedQuad({1.0f, 0.0f}, {0.8f, 0.8f}, -45.0f, {0.8f, 0.2f, 0.3f, 1.0f});
	Heirloom::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
	Heirloom::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
	Heirloom::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, m_BackgroundTexture, 10.0f);
	Heirloom::Renderer2D::DrawRotatedQuad({-2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, 45.0f, m_BackgroundTexture, 20.0f);

	Heirloom::Renderer2D::EndScene();

	Heirloom::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (float y = -5.0f; y < 5.0f; y += 0.5f)
	{
		for (float x = -5.0f; x < 5.0f; x += 0.5f)
		{
			glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
			Heirloom::Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
		}
	}
	Heirloom::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	HL_PROFILE_FUNCTION()

	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::Begin("main",
				 nullptr,
				 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowFontScale(2.0);
	ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::Begin("Settings");

	const Heirloom::Renderer2D::Statistics stats = Heirloom::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
