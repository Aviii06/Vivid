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
	class PointLightComponent : public Component
	{
	private:
		Maths::Vec3 m_Color;
		float m_Intensity = 1.0f;
		Vivid::Mesh* m_Mesh;
		Ref<Vivid::Shader> m_Shader;

	public:
		PointLightComponent() = default;
		PointLightComponent(Maths::Vec3 color);

		void Draw(Camera* camera) override;
		void ImGuiRender() override;

		void SetColor(Maths::Vec3 color) { m_Color = color; }

		inline Maths::Vec3 GetColor() const { return m_Color; }
		inline float GetIntensity() const { return m_Intensity; }
		ComponentType GetComponentType() override { return ComponentType::PointLightComponent; }
	};
}
