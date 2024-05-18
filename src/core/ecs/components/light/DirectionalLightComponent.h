#pragma once

#include "core/ecs/components/model/Mesh.h"
#include "core/renderer/shapes/Shape.h"

#include "core/ecs/Component.h"
#include "common/maths/Vec.h"

namespace Vivid
{
	/*!
	 * @class PointLightComponent
	 * @brief Contains a PointLightComponent.
	 * @details PointLightComponent is a class that contains a point light component. It is a derived class from Component.
	 * It contains a color and intensity of the light. It also contains a mesh and shader for the light. It also contains a UI for the point light component.
	 * From the UI you can change the color and intensity of the light.
	 */
	class DirectionalLightComponent : public Component
	{
	private:
		Maths::Vec3 m_LightColor = Maths::Vec3(1.0f, 1.0f, 1.0f);
		float m_Intensity = 1.0f;
		Maths::Vec3 m_Direction = Maths::Vec3(0.0f, -1.0f, 0.0f);

	public:
		DirectionalLightComponent() = default;
		DirectionalLightComponent(Maths::Vec3 lightColor);

		void Draw(Camera* camera) override;
		void ImGuiRender() override;

		void SetDirection(Maths::Vec3 direction) { m_Direction = direction; }

		inline Maths::Vec3 GetLightColor() const { return m_LightColor; }
		inline float GetIntensity() const { return m_Intensity; }
		inline Maths::Vec3 GetDirection() const { return m_Direction; }
		ComponentType GetComponentType() override { return ComponentType::DirectionalLightComponent; }
	};
}
