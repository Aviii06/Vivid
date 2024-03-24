#pragma once

#include "Shape.h"
#include "common/maths/Vec.h"

namespace Vivid
{
	class Quad3d : public Shape
	{
	private:
		float m_Size;

	public:
		Quad3d(int size, Maths::Vec3 col = Maths::Vec3(1.0f, 1.0f, 1.0f));
	};
}
