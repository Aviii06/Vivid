#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Vivid
{
	class VertexArray
	{
	private:
		unsigned int m_RendererID;

	public:
		VertexArray();

		~VertexArray();

		static Ref<VertexArray> Create();

		void AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, const Vector<Vertex>& vertices);

		void AddIndexBuffer(const IndexBuffer& ib);

		void Bind() const;

		void Unbind() const;
	};
}