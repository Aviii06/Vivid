#pragma once

#define MAX_VERTICES_ALLOWED 10000000
#include "common/Types.h"
#include "glm/glm/glm.hpp"

namespace Vivid
{

	struct Vertex
	{
		Vec3 position;
		Vec2 texcoord;
		Vec3 color;
		Vec3 normal;
	};

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