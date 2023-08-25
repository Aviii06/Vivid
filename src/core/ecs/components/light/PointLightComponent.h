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
		float m_Intensity = 1.0f;
		Vivid::Mesh* m_Mesh;
		Ref<Vivid::Shader> m_Shader;

	public:
		PointLightComponent() = default;
		PointLightComponent(Vec3 color);
		void Draw(Camera* camera) override;
		void ImGuiRender() override;

		inline Vec3 GetColor() const { return m_Color; }
		inline float GetIntensity() const { return m_Intensity; }

		String GetComponentName() override { return "PointLight Component"; }
	};
}
