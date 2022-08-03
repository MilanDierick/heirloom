// Copyright

#include "hlpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Heirloom
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = Heirloom::CreateScope<OpenGLRendererAPI>();

	void RenderCommand::Init()
	{
		s_RendererAPI->Init();
	}

	void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray, const uint32_t count)
	{
		s_RendererAPI->DrawIndexed(vertexArray, count);
	}

	void RenderCommand::SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
	{
		s_RendererAPI->SetViewport(x, y, width, height);
	}
}
