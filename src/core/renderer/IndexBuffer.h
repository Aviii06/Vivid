#pragma once

#include "common/types/SmartPointers.h"
#include "common/types/Types.h"

namespace Vivid
{
	/*!
	 * @class IndexBuffer
	 * @brief Manages the IndexBuffer. For more information on IndexBuffers, visit https://learnopengl.com/Getting-started/Hello-Triangle Element Buffer Objects.
	 * @details To create an IndexBuffer use the Create function. It takes in a Vector of unsigned integers that contains the indices and allocates the buffer to the GPU.
	 */
	class IndexBuffer
	{
	public:
		unsigned int m_RendererID;
		unsigned int m_Count;

	public:
		IndexBuffer() = default;
		IndexBuffer(Vector<unsigned int>& indices);
		~IndexBuffer();

		static Ref<IndexBuffer> Create(Vector<unsigned int>& indices);

		void Bind() const;

		void Unbind() const;

		inline unsigned int GetCount() const { return m_Count; }
	};
}
