#pragma once

#include "core/ecs/components/model/Mesh.h"
#include "core/renderer/shapes/Shape.h"

#include "core/ecs/Component.h"

namespace Vivid
{

	class PointLightComponent : public Vivid::Component
	{
	private:
		Vec3 m_Color;

	public:
		PointLightComponent() = default;
		PointLightComponent(Vec3 color);
		void Draw(Camera* camera) override;
		void ImGuiRender() override;
	};
}
