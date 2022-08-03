// Author: Milan Dierick
// Solution: Heirloom

//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_RENDERCOMMAND_H
#define HEIRLOOM_RENDERCOMMAND_H

#include <glm/vec4.hpp>
#include "VertexArray.h"
#include "RendererAPI.h"

namespace Heirloom
{
	class RenderCommand
	{
	public:
		static void Init();
		static void SetClearColor(const glm::vec4& color);
		static void Clear();
		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0);
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}

#endif //HEIRLOOM_RENDERCOMMAND_H
