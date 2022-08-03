#include "hlpch.h"
#include "RendererAPI.h"

namespace Heirloom
{
	RendererAPI::API RendererAPI::s_API = API::OpenGL;

	RendererAPI::API RendererAPI::GetAPI()
	{
		return s_API;
	}
}
