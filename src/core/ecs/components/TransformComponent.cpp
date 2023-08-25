#include "TransformComponent.h"

#include "imgui/imgui/imgui.h"

namespace Vivid
{
	void TransformComponent::ImGuiRender()
	{
		ImGui::Text("Transform Component");
		ImGui::Text("Position");
		ImGui::SliderFloat3("##Position", &m_Position.x, -500.0f, 500.0f);
		ImGui::Text("Rotation");
		ImGui::SliderFloat3("##Rotation", &m_Rotation.x, -500.0f, 500.0f);
		ImGui::Text("Scale");
		ImGui::SliderFloat3("##Scale", &m_Scale.x, -500.0f, 500.0f);

		m_Transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x, m_Position.y, m_Position.z));
	}
	void TransformComponent::Draw(Camera* camera)
	{
	}
}