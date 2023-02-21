#include "Renderer.h"

namespace Vivid
{
	void Renderer::Draw(Ref<VertexArray> va, unsigned int indexCount)
	{
		va->Bind();

		GLCall(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
}