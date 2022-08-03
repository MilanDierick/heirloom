//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_RENDERER2D_H
#define HEIRLOOM_RENDERER2D_H

#include "OrthographicCamera.h"
#include "Shader.h"
#include "Sprite.h"
#include "Texture.h"
#include "VertexArray.h"

namespace Heirloom
{
	class Renderer2D
	{
	public:
		static void Init();

		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera);

		static void EndScene();

		static void Flush();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref <Texture2D>& texture,
				float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref <Texture2D>& texture,
				float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);

		static void DrawQuad(const glm::mat4& transform, const Ref <Texture2D>& texture,
				float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawQuad(Sprite& sprite);

		static void
		DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);

		static void
		DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
				const Ref <Texture2D>& texture, float tilingFactor = 1.0f,
				const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
				const Ref <Texture2D>& texture, float tilingFactor = 1.0f,
				const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawRotatedQuad(Sprite& sprite);

		// Stats
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() const
			{
				return QuadCount * 4;
			}

			uint32_t GetTotalIndexCount() const
			{
				return QuadCount * 6;
			}
		};

		static void ResetStats();

		static Statistics GetStats();

	private:
		static void FlushAndReset();

		static void ConfigureAndIncrementQuadVertexBufferPtr(const glm::vec3& position,
				const glm::vec4& color,
				const glm::vec2& texCoord,
				float texIndex,
				float tilingFactor);
	};
}

#endif //HEIRLOOM_RENDERER2D_H
