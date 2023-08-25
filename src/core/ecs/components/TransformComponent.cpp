#include "TransformComponent.h"

#include "imgui/imgui/imgui.h"

namespace Vivid
{
	void TransformComponent::ImGuiRender()
	{
		Vec3 prevScale = m_Scale;
		ImGui::Text("Position");
		ImGui::SliderFloat3("##Position", &m_Position.x, -500.0f, 500.0f);
		ImGui::Text("Rotation");
		ImGui::SliderFloat3("##Rotation", &m_Rotation.x, -180.0f, 180.0f);
		ImGui::Text("Scale");
		ImGui::SliderFloat3("##Scale", &m_Scale.x, 0.0f, 5.0f, "%.2f");
		ImGui::SameLine();
		ImGui::Text("Fix Scale");
		ImGui::SameLine();
		ImGui::Checkbox("##FixScale", &m_FixScale);

		// TODO: This is a hack, fix it
		if (m_FixScale)
		{
			if (m_Scale.x != prevScale.x)
			{
				m_Scale.y = m_Scale.x;
				m_Scale.z = m_Scale.x;
			}

			if (m_Scale.y != prevScale.y)
			{
				m_Scale.x = m_Scale.y;
				m_Scale.z = m_Scale.y;
			}

			if (m_Scale.z != prevScale.z)
			{
				m_Scale.x = m_Scale.z;
				m_Scale.y = m_Scale.z;
			}
		}

		m_Transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x, m_Position.y, m_Position.z));
		m_Transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_Transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_Transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		m_Transform *= glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale.x, m_Scale.y, m_Scale.z));
	}

	void TransformComponent::Draw(Camera* camera)
	{
	}
}