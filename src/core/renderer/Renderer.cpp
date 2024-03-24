#include "Renderer.h"

namespace Vivid
{
	void Renderer::Draw(Ref<VertexArray> va, unsigned int indexCount, unsigned int instanceCount)
	{
		va->Bind();

		GLCall(glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr, instanceCount));
	}

	void Renderer::Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
}
