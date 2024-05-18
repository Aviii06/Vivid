#pragma once

#include "common/maths/Vec.h"
#include "common/types/Types.h"
#include "common/types/SmartPointers.h"
#include "glm/glm/glm.hpp"
#include "common/maths/Vec.h"

namespace Vivid
{

	/*!
	 * @struct Vertex
	 * @brief A struct for the Vertex.
	 * @details Vertex is a struct that contains the position, texture coordinates, normal, and tangent of a vertex.
	 */
	struct Vertex
	{
		Maths::Vec3 position;
		Maths::Vec2 texcoord;
		Maths::Vec3 normal;
		Maths::Vec3 tangent;
	};

	/*!
	 * @class VertexBuffer
	 * @brief A class for the VertexBuffer.
	 * @details VertexBuffer is a class that contains the vertices of a mesh. For more information read the OpenGL documentation.
	 */
	class VertexBuffer
	{
	private:
		unsigned int m_RendererID;

	public:
		VertexBuffer(std::vector<Vertex>& vertices);

		static Ref<VertexBuffer> Create(std::vector<Vertex>& vertices);

		~VertexBuffer();

		void Bind(const std::vector<Vertex>& vertices) const;

		void Unbind() const;
	};
}