#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "utils/Error.h"
#include "glew-cmake/include/GL/glew.h"
#include <memory>

namespace Vivid
{
	/*!
	 * @class Renderer
	 * @brief Handles all the rendering of the vertices.
	 * @details Renderer is a class that contains the functions to draw the vertices of a mesh.
	 */
	class Renderer
	{
	private:
		Renderer() = default;

	public:
		/*!
		 * @brief Initializes the Renderer.
		 * @details Initializes the Renderer by enabling the depth test and the blending.
		 * @param va The VertexArray to draw.
		 * @param indexCount The number of indices to draw.
		 * @param instanceCount The number of instances to draw. Default is 1.
		 */
		static void Draw(Ref<VertexArray> va, unsigned int indexCount, unsigned int instanceCount = 1);
		static void DrawLine(Ref<VertexArray> va, unsigned int vertexCount);
		static void Clear();
	};

}