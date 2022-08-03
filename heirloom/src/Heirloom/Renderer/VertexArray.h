//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_VERTEXARRAY_H
#define HEIRLOOM_VERTEXARRAY_H

#include <memory>
#include "Buffer.h"

namespace Heirloom
{
	class VertexArray
	{
	public:
		VertexArray()          = default;
		virtual ~VertexArray() = default;

		VertexArray(const VertexArray& other)                = delete;
		VertexArray(VertexArray&& other) noexcept            = delete;
		VertexArray& operator=(const VertexArray& other)     = delete;
		VertexArray& operator=(VertexArray&& other) noexcept = delete;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer> GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};
}

#endif //HEIRLOOM_VERTEXARRAY_H
