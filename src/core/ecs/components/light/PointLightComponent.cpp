#include "PointLightComponent.h"
#include "imgui/imgui/imgui.h"

namespace Vivid
{
	PointLightComponent::PointLightComponent(Vec3 color)
	    : m_Color(color)
	{
	}

	void PointLightComponent::Draw(Camera* camera)
	{
	}

	void PointLightComponent::ImGuiRender()
	{
		ImGui::Text("Point Light");
		ImGui::ColorPicker3("Color", &m_Color.x);
	}
}
