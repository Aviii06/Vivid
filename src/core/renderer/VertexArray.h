#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Vivid
{
	/*!
	 * @class VertexArray
	 * @brief A class for the VertexArray.
	 * @details VertexArray is a class that contains the vertex buffer and the index buffer. For more information read the OpenGL documentation.
	 */
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