#include "hlpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Heirloom
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		HL_PROFILE_FUNCTION()

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: HL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
		}

		HL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		HL_PROFILE_FUNCTION()

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: HL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}

		HL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}