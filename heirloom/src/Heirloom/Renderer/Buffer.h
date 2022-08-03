//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_BUFFER_H
#define HEIRLOOM_BUFFER_H

#include "Heirloom/Core/Core.h"

namespace Heirloom
{
	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(const ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::None: return 0;
		case ShaderDataType::Float: return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		case ShaderDataType::Mat3: return 4 * 3 * 3;
		case ShaderDataType::Mat4: return 4 * 4 * 4;
		case ShaderDataType::Int: return 4;
		case ShaderDataType::Int2: return 4 * 2;
		case ShaderDataType::Int3: return 4 * 3;
		case ShaderDataType::Int4: return 4 * 4;
		case ShaderDataType::Bool: return 1;
		}

		HL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		ShaderDataType Type;
		std::string Name;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		BufferElement()
				: Type(ShaderDataType::None),
				  Offset(0),
				  Size(0),
				  Normalized(false)
		{
		}

		BufferElement(const ShaderDataType type, const std::string& name, const bool normalized = false)
				: Type(type),
				  Name(name),
				  Offset(0),
				  Size(ShaderDataTypeSize(type)),
				  Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float: return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat3: return 3; // 3* float3
			case ShaderDataType::Mat4: return 4; // 4* float4
			case ShaderDataType::Int: return 1;
			case ShaderDataType::Int2: return 2;
			case ShaderDataType::Int3: return 3;
			case ShaderDataType::Int4: return 4;
			case ShaderDataType::Bool: return 1;
			default: ;
			}

			HL_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout()
		{
		}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
				: m_Elements(elements)
		{
			HL_PROFILE_FUNCTION()

			CalculateOffsetsAndStride();
		}

		const std::vector<BufferElement>& GetElements() const
		{
			return m_Elements;
		}

		uint32_t GetStride() const
		{
			return m_Stride;
		}

		// ReSharper disable CppInconsistentNaming
		std::vector<BufferElement>::iterator begin()
		{
			return m_Elements.begin();
		}

		std::vector<BufferElement>::iterator end()
		{
			return m_Elements.end();
		}

		std::vector<BufferElement>::const_iterator begin() const
		{
			return m_Elements.cbegin();
		}

		std::vector<BufferElement>::const_iterator end() const
		{
			return m_Elements.cend();
		}

		// ReSharper restore CppInconsistentNaming

	private:
		void CalculateOffsetsAndStride();

		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer()          = default;
		virtual ~VertexBuffer() = default;

		VertexBuffer(const VertexBuffer& other)                = delete;
		VertexBuffer(VertexBuffer&& other) noexcept            = delete;
		VertexBuffer& operator=(const VertexBuffer& other)     = delete;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept = delete;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};

	// Only 32-bit index buffers supported
	class IndexBuffer
	{
	public:
		IndexBuffer()          = default;
		virtual ~IndexBuffer() = default;

		IndexBuffer(const IndexBuffer& other)                = delete;
		IndexBuffer(IndexBuffer&& other) noexcept            = delete;
		IndexBuffer& operator=(const IndexBuffer& other)     = delete;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept = delete;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};
}

#endif //HEIRLOOM_BUFFER_H
