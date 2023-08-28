#include "SceneUI.h"
#include "UIFlags.h"
#include "ImGuizmo.h"
#include "core/ecs/components/TransformComponent.h"

namespace VividGUI {
    Vivid::Entity *VividGUI::SceneUI::m_SelectedEntity;

    void SceneUI::DrawSceneUI() {
        ImGui::Begin("Scene");
        for (auto entity: Vivid::ECS::g_Entities) {
            if (ImGui::Selectable(entity->GetName().c_str(), m_SelectedEntity == entity)) {
                m_SelectedEntity = entity;
            }
        }

        if (m_SelectedEntity) {
            ImGui::Begin("Inspector");
            m_SelectedEntity->DrawGUI();
            ImGui::End();
        }

        ImGui::SetWindowPos(ImVec2(200, 50));
        ImGui::End();
    }

    void SceneUI::DrawGizmo(Camera* camera)
    {
        if (m_SelectedEntity) {
            m_SelectedEntity->DrawGizmo(camera);
        }


    }
}
