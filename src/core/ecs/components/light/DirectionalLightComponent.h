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
		Maths::Vec3 m_DiffuseColor, m_SpecularColor, m_LightColor;
		float m_Intensity = 1.0f;
		Maths::Vec3 m_Direction = Maths::Vec3(0.0f, -1.0f, 0.0f);

	public:
		DirectionalLightComponent() = default;

		DirectionalLightComponent(Maths::Vec3 diffuseColor, Maths::Vec3 specularColor, Maths::Vec3 lightColor = Maths::Vec3(1.0f, 1.0f, 1.0f));

		void Draw(Camera* camera) override;

		void ImGuiRender() override;

		void SetDirection(Maths::Vec3 direction) { m_Direction = direction; }

		inline Maths::Vec3 GetDiffuseColor() const { return m_DiffuseColor; }
		inline Maths::Vec3 GetSpecularColor() const { return m_SpecularColor; }
		inline Maths::Vec3 GetLightColor() const { return m_LightColor; }

		inline void SetDiffuseColor(Maths::Vec3 diffuseColor) { m_DiffuseColor = diffuseColor; }
		inline void SetSpecularColor(Maths::Vec3 specularColor) { m_SpecularColor = specularColor; }

		inline float GetIntensity() const { return m_Intensity; }

		inline Maths::Vec3 GetDirection() const { return m_Direction; }

		String GetComponentName() override { return "DirectionalLight Component"; }
	};
}
