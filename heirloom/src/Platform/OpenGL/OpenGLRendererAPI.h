// Author: Milan Dierick
// Solution: Heirloom

//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_OPENGLRENDERERAPI_H
#define HEIRLOOM_OPENGLRENDERERAPI_H

#include "Heirloom/Renderer/RendererAPI.h"

namespace Heirloom
{
	class OpenGLRendererAPI final : public RendererAPI
	{
	public:
		void Init() override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
	};
}

#endif //HEIRLOOM_OPENGLRENDERERAPI_H
