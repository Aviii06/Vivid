#include "VertexBuffer.h"
#include "Renderer.h"


namespace Vivid
{
	VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices)
	{
		GLCall(glGenBuffers(1, &m_RendererID)); // creating a buffer
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // binding the buffer
		GLCall(glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES_ALLOWED * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW));
	}

	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	void VertexBuffer::Bind(const std::vector<Vertex>& vertices) const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data()));

	}

	void VertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	Ref<VertexBuffer> VertexBuffer::Create(std::vector<Vertex>& vertices)
	{
		return MakeRef<VertexBuffer>(vertices);
	}
}