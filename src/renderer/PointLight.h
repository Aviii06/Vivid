#pragma once

#include "Mesh.h"
#include "shapes/Shape.h"

namespace Vivid
{
	class PointLight
	{
	private:
		Vec3 m_Position;
		Vec3 m_Color;
		Mesh* m_LightMesh;

	public:
		PointLight(Vec3& position, Vec3 color, Mesh* lightMesh);
		PointLight(Vec3 position, Vec3 color, Shape& shape);

		void UpdateLightPosition(Vec3 pos);

		void Draw(Ref<Shader> shader);
	};
}
