#pragma once

#include "core/renderer/VertexBuffer.h"
#include "common/types/SmartPointers.h"

namespace Vivid
{
	class Shape
	{
	protected:
		Vector<Vertex> m_Pos;
		Vector<unsigned int> m_Ind;

	public:
		Shape() = default;

		Vector<Vertex>& GetPositions() { return m_Pos; };

		Vector<unsigned int>& GetIndices() { return m_Ind; };

		size_t GetPositionsSize() { return sizeof(m_Pos); };

		size_t GetIndicesSize() { return sizeof(m_Ind); };
	};
}
