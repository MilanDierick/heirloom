#include "hlpch.h"
#include "Renderer2D.h"
#include "RenderCommand.h"

namespace Heirloom
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads    = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices  = MaxQuads * 6;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
		static const uint32_t MaxTextureSlots = 32;

		uint32_t QuadIndexCount           = 0;
		QuadVertex* pQuadVertexBufferBase = nullptr;
		QuadVertex* pQuadVertexBuffer     = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		glm::vec4 QuadVertexPositions[4];

		Renderer2D::Statistics Stats;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		HL_PROFILE_FUNCTION()

		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
				{ShaderDataType::Float2, "a_TexCoord"},
				{ShaderDataType::Float, "a_TexIndex"},
				{ShaderDataType::Float, "a_TilingFactor"}
		});

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.pQuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		const Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_Data.WhiteTexture       = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

		// Set all texture slots to 0
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		s_Data.QuadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
		s_Data.QuadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
		s_Data.QuadVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
		s_Data.QuadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
	}

	void Renderer2D::Shutdown()
	{
		HL_PROFILE_FUNCTION()

		delete[] s_Data.pQuadVertexBufferBase;
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		HL_PROFILE_FUNCTION()

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.QuadIndexCount    = 0;
		s_Data.pQuadVertexBuffer = s_Data.pQuadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		HL_PROFILE_FUNCTION()

		const uint32_t dataSize = static_cast<uint32_t>(reinterpret_cast<uint8_t*>(s_Data.pQuadVertexBuffer) -
														reinterpret_cast<uint8_t*>(s_Data.pQuadVertexBufferBase));
		s_Data.QuadVertexBuffer->SetData(s_Data.pQuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		// Nothing to draw
		if (s_Data.QuadIndexCount == 0)
		{
			return;
		}

		// Bind textures
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			s_Data.TextureSlots[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		++s_Data.Stats.DrawCalls;
	}

	void Renderer2D::FlushAndReset()
	{
		EndScene();

		s_Data.QuadIndexCount    = 0;
		s_Data.pQuadVertexBuffer = s_Data.pQuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		HL_PROFILE_FUNCTION()

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		{
			FlushAndReset();
		}

		const float textureIndex = 0.0f; // White Texture
		const float tilingFactor = 1.0f;

		const glm::mat4 transform = translate(glm::mat4(1.0f), position) * scale(
				glm::mat4(1.0f),
				{size.x, size.y, 1.0f});

		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[0],
				color,
				{0.0f, 0.0f},
				textureIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[1],
				color,
				{1.0f, 0.0f},
				textureIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[2],
				color,
				{1.0f, 1.0f},
				textureIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[3],
				color,
				{0.0f, 1.0f},
				textureIndex,
				tilingFactor);

		s_Data.QuadIndexCount += 6;

		++s_Data.Stats.QuadCount;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position,
			const glm::vec2& size,
			const Ref<Texture2D>& texture,
			const float tilingFactor,
			const glm::vec4& tintColor)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position,
			const glm::vec2& size,
			const Ref<Texture2D>& texture,
			const float tilingFactor,
			const glm::vec4& tintColor)
	{
		HL_PROFILE_FUNCTION()

		float texIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get())
			{
				texIndex = static_cast<float>(i);
				break;
			}
		}

		if (texIndex == 0.0f)
		{
			if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			{
				FlushAndReset();
			}

			texIndex                                     = static_cast<float>(s_Data.TextureSlotIndex);
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		const glm::mat4 transform = translate(glm::mat4(1.0f), position) * scale(
				glm::mat4(1.0f),
				{size.x, size.y, 1.0f});

		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[0],
				tintColor,
				{0.0f, 0.0f},
				texIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[1],
				tintColor,
				{1.0f, 0.0f},
				texIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[2],
				tintColor,
				{1.0f, 1.0f},
				texIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[3],
				tintColor,
				{0.0f, 1.0f},
				texIndex,
				tilingFactor);

		s_Data.QuadIndexCount += 6;

		++s_Data.Stats.QuadCount;
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		HL_PROFILE_FUNCTION()

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		{
			FlushAndReset();
		}

		const float textureIndex = 0.0f; // White Texture
		const float tilingFactor = 1.0f;

		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[0],
				color,
				{0.0f, 0.0f},
				textureIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[1],
				color,
				{1.0f, 0.0f},
				textureIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[2],
				color,
				{1.0f, 1.0f},
				textureIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[3],
				color,
				{0.0f, 1.0f},
				textureIndex,
				tilingFactor);

		s_Data.QuadIndexCount += 6;

		++s_Data.Stats.QuadCount;
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor,
			const glm::vec4& tintColor)
	{
		HL_PROFILE_FUNCTION()

		float texIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get())
			{
				texIndex = static_cast<float>(i);
				break;
			}
		}

		if (texIndex == 0.0f)
		{
			if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			{
				FlushAndReset();
			}

			texIndex                                     = static_cast<float>(s_Data.TextureSlotIndex);
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[0],
				tintColor,
				{0.0f, 0.0f},
				texIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[1],
				tintColor,
				{1.0f, 0.0f},
				texIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[2],
				tintColor,
				{1.0f, 1.0f},
				texIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[3],
				tintColor,
				{0.0f, 1.0f},
				texIndex,
				tilingFactor);

		s_Data.QuadIndexCount += 6;

		++s_Data.Stats.QuadCount;
	}

	void Renderer2D::DrawQuad(Sprite& sprite)
	{
		DrawQuad(sprite.Position, sprite.Size, sprite.Texture, sprite.TilingFactor, sprite.TintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position,
			const glm::vec2& size,
			const float rotation,
			const glm::vec4& color)
	{
		DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position,
			const glm::vec2& size,
			const float rotation,
			const glm::vec4& color)
	{
		HL_PROFILE_FUNCTION()

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		{
			FlushAndReset();
		}

		const float textureIndex = 0.0f; // White Texture
		const float tilingFactor = 1.0f;

		const glm::mat4 transform = translate(glm::mat4(1.0f), position) * rotate(
				glm::mat4(1.0f),
				glm::radians(rotation),
				{0.0f, 0.0f, 1.0f}) * scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[0],
				color,
				{0.0f, 0.0f},
				textureIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[1],
				color,
				{1.0f, 0.0f},
				textureIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[2],
				color,
				{1.0f, 1.0f},
				textureIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[3],
				color,
				{0.0f, 1.0f},
				textureIndex,
				tilingFactor);

		s_Data.QuadIndexCount += 6;

		++s_Data.Stats.QuadCount;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position,
			const glm::vec2& size,
			const float rotation,
			const Ref<Texture2D>& texture,
			const float tilingFactor,
			const glm::vec4& tintColor)
	{
		DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position,
			const glm::vec2& size,
			const float rotation,
			const Ref<Texture2D>& texture,
			const float tilingFactor,
			const glm::vec4& tintColor)
	{
		HL_PROFILE_FUNCTION()

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = static_cast<float>(i);
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			{
				FlushAndReset();
			}

			textureIndex                                 = static_cast<float>(s_Data.TextureSlotIndex);
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		const glm::mat4 transform = translate(glm::mat4(1.0f), position) * rotate(
				glm::mat4(1.0f),
				glm::radians(rotation),
				{0.0f, 0.0f, 1.0f}) * scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[0],
				tintColor,
				{0.0f, 0.0f},
				textureIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[1],
				tintColor,
				{1.0f, 0.0f},
				textureIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[2],
				tintColor,
				{1.0f, 1.0f},
				textureIndex,
				tilingFactor);
		ConfigureAndIncrementQuadVertexBufferPtr(transform * s_Data.QuadVertexPositions[3],
				tintColor,
				{0.0f, 1.0f},
				textureIndex,
				tilingFactor);

		s_Data.QuadIndexCount += 6;

		++s_Data.Stats.QuadCount;
	}

	void Renderer2D::DrawRotatedQuad(Sprite& sprite)
	{
		DrawRotatedQuad(sprite.Position,
				sprite.Size,
				sprite.Rotation,
				sprite.Texture,
				sprite.TilingFactor,
				sprite.TintColor);
	}

	void Renderer2D::ConfigureAndIncrementQuadVertexBufferPtr(const glm::vec3& position,
			const glm::vec4& color,
			const glm::vec2& texCoord,
			const float texIndex,
			const float tilingFactor)
	{
		s_Data.pQuadVertexBuffer->Position     = position;
		s_Data.pQuadVertexBuffer->Color        = color;
		s_Data.pQuadVertexBuffer->TexCoord     = texCoord;
		s_Data.pQuadVertexBuffer->TexIndex     = texIndex;
		s_Data.pQuadVertexBuffer->TilingFactor = tilingFactor;
		s_Data.pQuadVertexBuffer++;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}
}
