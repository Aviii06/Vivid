#include "SceneUI.h"
#include "UIFlags.h"


namespace VividGUI
{
	Vivid::Entity* VividGUI::SceneUI::m_SelectedEntity;

	void SceneUI::DrawSceneUI()
	{
		ImGui::Begin("Scene", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x - 200, ImGui::GetIO().DisplaySize.y - 100));
		for (auto& entity : Vivid::ECS::g_Entities)
		{
			if (ImGui::Selectable(entity->GetName().c_str(), m_SelectedEntity == entity))
			{
				m_SelectedEntity = entity;
			}
		}
		ImGui::SetWindowPos(ImVec2(200, 50));
		ImGui::End();
	}
}
