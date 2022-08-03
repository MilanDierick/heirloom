//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_RENDERERAPI_H
#define HEIRLOOM_RENDERERAPI_H

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Heirloom
{
	class RendererAPI
	{
	public:
		RendererAPI()          = default;
		virtual ~RendererAPI() = default;

		RendererAPI(const RendererAPI& other)                = delete;
		RendererAPI(RendererAPI&& other) noexcept            = delete;
		RendererAPI& operator=(const RendererAPI& other)     = delete;
		RendererAPI& operator=(RendererAPI&& other) noexcept = delete;

		enum class API
		{
			None = 0,
			OpenGL = 1
		};

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		static API GetAPI();

	private:
		static API s_API;
	};
}

#endif //HEIRLOOM_RENDERERAPI_H
