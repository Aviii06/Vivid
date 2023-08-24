#pragma once

#include "core/ecs/components/model/Mesh.h"
#include "core/renderer/shapes/Shape.h"

namespace Vivid
{
	class PointLight
	{
	private:
		Vec3 m_Position;
		Vec3 m_Color;
		Mesh* m_LightMesh;

	public:
		PointLight() = default;
		PointLight(Vec3& position, Vec3 color, Mesh* lightMesh);
		PointLight(Vec3 position, Vec3 color, Shape& shape);

		void UpdateLightPosition(Vec3 pos);

		void Draw(Ref<Shader> shader);
	};
}
