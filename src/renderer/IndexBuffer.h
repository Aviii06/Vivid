#pragma once

#include "common/Types.h"

#include "common/Types.h"

namespace NewtonRenderer
{
	class IndexBuffer
	{
	public:
		unsigned int m_RendererID;
		unsigned int m_Count;

	public:
		IndexBuffer() = default;

		IndexBuffer(Vector<unsigned int>& indices);

		~IndexBuffer();

		void Bind() const;

		void Unbind() const;

		inline unsigned int GetCount() const { return m_Count; }
	};
}