#pragma once

#include "common/types/SmartPointers.h"
#include "common/types/Types.h"

namespace Vivid
{
	class IndexBuffer
	{
	public:
		unsigned int m_RendererID;
		unsigned int m_Count;

	public:
		IndexBuffer() = default;

		IndexBuffer(Vector<unsigned int>& indices);

		static Ref<IndexBuffer> Create(Vector<unsigned int>& indices);

		~IndexBuffer();

		void Bind() const;

		void Unbind() const;

		inline unsigned int GetCount() const { return m_Count; }
	};
}
