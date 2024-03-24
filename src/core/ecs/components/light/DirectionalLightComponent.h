#pragma once

#include "core/ecs/components/model/Mesh.h"
#include "core/renderer/shapes/Shape.h"

#include "core/ecs/Component.h"
#include "common/maths/Vec.h"

namespace Vivid
{

	class DirectionalLightComponent : public Vivid::Component
	{
	private:
		Maths::Vec3 m_Color;
		float m_Intensity = 1.0f;
		Maths::Vec3 m_Direction = Maths::Vec3(0.0f, -1.0f, 0.0f);

	public:
		DirectionalLightComponent() = default;

		DirectionalLightComponent(Maths::Vec3 color);

		void Draw(Camera* camera) override;

		void ImGuiRender() override;

		void SetColor(Maths::Vec3 color) { m_Color = color; }

		void SetDirection(Maths::Vec3 direction) { m_Direction = direction; }

		inline Maths::Vec3 GetColor() const { return m_Color; }

		inline float GetIntensity() const { return m_Intensity; }

		inline Maths::Vec3 GetDirection() const { return m_Direction; }

		String GetComponentName() override { return "DirectionalLight Component"; }
	};
}
