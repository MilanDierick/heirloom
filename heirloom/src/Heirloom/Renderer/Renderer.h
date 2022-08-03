//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_RENDERER_H
#define HEIRLOOM_RENDERER_H

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"

namespace Heirloom
{
	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader,
				const Ref<VertexArray>& vertexArray,
				const glm::mat4& transform = glm::mat4(1.0f));

		static RendererAPI::API GetAPI()
		{
			return RendererAPI::GetAPI();
		}

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};
}

#endif //HEIRLOOM_RENDERER_H
