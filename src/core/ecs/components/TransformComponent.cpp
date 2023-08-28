#include "TransformComponent.h"

#include "imgui/imgui/imgui.h"

namespace Vivid
{
    void TransformComponent::updateTransformImGUI()
    {
        if (ImGui::IsKeyPressed((ImGuiKey)90))
            m_CurrentGizmoOperation = ImGuizmo::TRANSLATE;
        if (ImGui::IsKeyPressed((ImGuiKey)69))
            m_CurrentGizmoOperation = ImGuizmo::ROTATE;
        if (ImGui::IsKeyPressed((ImGuiKey)82)) // r Key
            m_CurrentGizmoOperation = ImGuizmo::SCALE;
        if (ImGui::RadioButton("Translate", m_CurrentGizmoOperation == ImGuizmo::TRANSLATE))
            m_CurrentGizmoOperation = ImGuizmo::TRANSLATE;
        ImGui::SameLine();
        if (ImGui::RadioButton("Rotate", m_CurrentGizmoOperation == ImGuizmo::ROTATE))
            m_CurrentGizmoOperation = ImGuizmo::ROTATE;
        ImGui::SameLine();
        if (ImGui::RadioButton("Scale", m_CurrentGizmoOperation == ImGuizmo::SCALE))
            m_CurrentGizmoOperation = ImGuizmo::SCALE;

        ImGuizmo::DecomposeMatrixToComponents(&m_Transform[0][0], &m_Position.x, &m_Rotation.x, &m_Scale.x);
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
        ImGuizmo::RecomposeMatrixFromComponents(&m_Position.x, &m_Rotation.x, &m_Scale.x, &m_Transform[0][0]);

        if (m_CurrentGizmoOperation != ImGuizmo::SCALE)
        {
            if (ImGui::RadioButton("Local", m_CurrentGizmoMode == ImGuizmo::LOCAL))
                m_CurrentGizmoMode = ImGuizmo::LOCAL;
            ImGui::SameLine();
            if (ImGui::RadioButton("World", m_CurrentGizmoMode == ImGuizmo::WORLD))
                m_CurrentGizmoMode = ImGuizmo::WORLD;
        }
        if (ImGui::IsKeyPressed((ImGuiKey)83))
            m_UsingSnap = !m_UsingSnap;
        ImGui::Checkbox("", &m_UsingSnap);
        ImGui::SameLine();

        switch (m_CurrentGizmoOperation)
        {
            case ImGuizmo::TRANSLATE:
                ImGui::InputFloat3("Snap", &m_Snap[0]);
                break;
            case ImGuizmo::ROTATE:
                ImGui::InputFloat("Angle Snap", &m_Snap[0]);
                break;
            case ImGuizmo::SCALE:
                ImGui::InputFloat("Scale Snap", &m_Snap[0]);
                break;
        }
//        ImGui::Checkbox("Bound Sizing", &boundSizing);
//        if (boundSizing)
//        {
//            ImGui::PushID(3);
//            ImGui::Checkbox("", &boundSizingSnap);
//            ImGui::SameLine();
//            ImGui::InputFloat3("Snap", boundsSnap);
//            ImGui::PopID();
//        }

    }


	void TransformComponent::ImGuiRender()
	{
		Vec3 prevScale = m_Scale;

        updateTransformImGUI();

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

        // Todo: Use quaternions
		m_Transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x, m_Position.y, m_Position.z));
		m_Transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_Transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_Transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		m_Transform *= glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale.x, m_Scale.y, m_Scale.z));
	}

	void TransformComponent::Draw(Camera* camera)
	{
	}

    void TransformComponent::DrawGizmo(Camera* camera)
    {
        ImGuiIO& io = ImGui::GetIO();
        float viewManipulateRight = io.DisplaySize.x;
        float viewManipulateTop = 0;

        glm::mat4 cameraProjection = camera->GetProjectionMatrix();
        glm::mat4 cameraView = camera->GetViewMatrix();

        ImGui::SetNextWindowSize(ImVec2(800, 400));
        ImGui::SetNextWindowPos(ImVec2(400,20));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)ImColor(0.35f, 0.3f, 0.3f));
        ImGui::Begin("Gizmo", 0, ImGuiWindowFlags_NoMove);
        ImGuizmo::SetDrawlist();
        float windowWidth = (float)ImGui::GetWindowWidth();
        float windowHeight = (float)ImGui::GetWindowHeight();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
        viewManipulateRight = ImGui::GetWindowPos().x + windowWidth;
        viewManipulateTop = ImGui::GetWindowPos().y;


        glm::mat4 identityMatrix = glm::mat4(1.0f);

        ImGuizmo::Manipulate(&cameraView[0][0], &cameraProjection[0][0], m_CurrentGizmoOperation, m_CurrentGizmoMode, &m_Transform[0][0], NULL, m_UsingSnap ? &m_Snap[0] : NULL);
        float camDistance = 100;
        ImGuizmo::ViewManipulate(&cameraView[0][0], camDistance, ImVec2(viewManipulateRight - 128, viewManipulateTop), ImVec2(128, 128), 0x10101010);

        ImGuizmo::DecomposeMatrixToComponents(&m_Transform[0][0], &m_Position.x, &m_Rotation.x, &m_Scale.x);

        ImGui::End();
        ImGui::PopStyleColor(1);
    }
}