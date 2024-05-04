#include "SceneUI.h"
#include "UIFlags.h"
#include "editor/assets/Assets.h"
#include "core/ecs/ECS.h"

namespace VividGUI
{
	Vivid::Entity* VividGUI::SceneUI::m_SelectedEntity;

	void SceneUI::DrawSceneUI()
	{
		ImGui::Begin("Scene");
		for (auto entity : Vivid::ECS::g_Entities)
		{
			if (ImGui::Selectable(entity->GetName().c_str(), m_SelectedEntity == entity))
			{
				m_SelectedEntity = entity;
			}
		}

		unsigned int texId = VividGui::Assets::GetInstance()->GetTexPlus()->GetRendererID();
		if (ImGui::ImageButton((ImTextureID)texId,
							   ImVec2(VividGui::Assets::GetInstance()->GetButtonWidth(), VividGui::Assets::GetInstance()->GetButtonWidth()),
							   {
								   0,
								   0,
							   },
							   { 1, 1 }, 2))
		{
			Vivid::ECS::CreateEntity("Entity" + std::to_string(Vivid::ECS::s_EntityID));
		}

		if (m_SelectedEntity)
		{
			ImGui::Begin("Inspector");
			m_SelectedEntity->DrawGUI();

			char* name = m_SelectedEntity->GetName().data();
			static const ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;
			if (ImGui::InputText(m_SelectedEntity->GetName().c_str(), name, 255, flags))
			{
				if (name == "")
				{
					m_SelectedEntity->SetName("Entity" + std::to_string(Vivid::ECS::s_EntityID));
				}

				String temp = name;
				// temp must not contain space
				for (int i = 0; i < temp.size(); i++)
				{
					if (name[i] == ' ')
					{
						name[i] = '_';
					}
				}
				m_SelectedEntity->SetName(String(name));
			}

			for (int i = 0; i < Vivid::ECS::g_Entities.size(); i++)
			{
				if (i == m_SelectedEntity->GetID())
				{
					continue;
				}

				if (m_SelectedEntity->GetName() == Vivid::ECS::g_Entities[i]->GetName())
				{
					ImGui::Text("Name Already Exist");
				}
			}
			ImGui::End();
		}

		ImGui::SetWindowPos(ImVec2(200, 50));
		ImGui::End();
	}

	void SceneUI::DrawGizmo(Camera* camera)
	{
		if (m_SelectedEntity)
		{
			m_SelectedEntity->DrawGizmo(camera);
		}
	}
}
