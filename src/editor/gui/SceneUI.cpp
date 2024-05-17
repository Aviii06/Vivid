#include "SceneUI.h"
#include "UIFlags.h"
#include "editor/assets/Assets.h"
#include "core/ecs/ECS.h"
#include "core/ecs/ComponentFactory.h"

namespace VividGUI
{
	Vivid::Entity* VividGUI::SceneUI::m_SelectedEntity;

	void SceneUI::DrawSceneUI()
	{
		ImGui::Begin("Scene");
		for (auto entity : Vivid::ECS::g_Entities)
		{
			if (ImGui::Selectable(entity.second->GetName().c_str(), m_SelectedEntity == entity.second.get()))
			{
				m_SelectedEntity = entity.second.get();
			}
		}

		unsigned int texId = VividGui::Assets::GetInstance()->GetTexPlus()->GetRendererID();
		if (ImGui::ImageButton((ImTextureID)texId,
		        ImVec2(VividGui::Assets::GetInstance()->GetButtonWidth(), VividGui::Assets::GetInstance()->GetButtonWidth()),
		        { 0, 0 }, { 1, 1 }, 2))
		{
			Vivid::ECS::CreateEntity("Entity" + std::to_string(Vivid::ECS::s_EntityID));
		}

		if (m_SelectedEntity)
		{
			ImGui::Begin("Inspector");
			m_SelectedEntity->ImguiRender();

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

			for (auto& entity: Vivid::ECS::g_Entities)
			{
				if (entity.first == m_SelectedEntity->GetID())
				{
					continue;
				}

				if (m_SelectedEntity->GetName() == entity.second->GetName())
				{
					ImGui::Text("Name Already Exist");
				}
			}
			ImGui::End();

			// A Popup which is triggered when you right click a entity and you can add components through a list of checklist
			if (ImGui::BeginPopupContextWindow())
			{
				if (ImGui::BeginMenu("Add Component"))
				{
					for (auto ct: Vivid::g_AllComponentStrings)
					{
						bool doesComponentExist = false;
						auto component = m_SelectedEntity->HasComponent(ct.first);
						if (component)
						{
							doesComponentExist = true;
						}

						if (ImGui::MenuItem(Vivid::g_AllComponentStrings.at(ct.first).c_str(), NULL, doesComponentExist))
						{
							if (doesComponentExist)
							{
								if (ct.first == Vivid::ComponentType::TransformComponent)
								{
									doesComponentExist = true;
									continue;
								}
								Vivid::ECS::RemoveComponent(component, m_SelectedEntity->GetID());
							}
							else
							{
								Vivid::ECS::AddComponent(component, m_SelectedEntity->GetID());
							}
						}
					}
					ImGui::EndMenu();
				}
				ImGui::EndPopup();
			}
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
