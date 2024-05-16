#include "ModelComponent.h"
#include "imgui/imgui/imgui.h"
#include "core/ecs/components/TransformComponent.h"
#include "core/os/FileDialogue.h"
#include "core/renderer/Texture.h"
#include "editor/assets/Assets.h"

#define MAX_MESHES 10

Vivid::ModelComponent::ModelComponent()
{
	m_Meshes.reserve(MAX_MESHES);
}

void Vivid::ModelComponent::Draw(Camera* camera)
{
	TransformComponent transformComponent;
	if (m_Entity->HasComponent(transformComponent.GetComponentName()) == -1)
	{
		std::cerr << "Entity does not have a TransformComponent\n";
		return;
	}
	glm::mat4 transform = m_Entity->GetComponent<Vivid::TransformComponent>()->GetTransform();

	for (auto& mesh : m_Meshes)
	{
		mesh->Update(transform);
		mesh->Draw(camera);
	}
}

void Vivid::ModelComponent::AddMesh(Vivid::Mesh* mesh)
{
	m_Meshes.push_back(mesh);
}

void Vivid::ModelComponent::RemoveMesh(Vivid::Mesh* mesh)
{
	m_Meshes.erase(std::remove(m_Meshes.begin(), m_Meshes.end(), mesh), m_Meshes.end());
}

void Vivid::ModelComponent::ImGuiRender()
{
	static ImGuiTableColumnFlags columns_base_flags = ImGuiTableColumnFlags_None;

	if (ImGui::BeginTable("table_advanced", 4, 0, ImVec2(0, 0), 0))
	{
		ImGui::TableSetupColumn("ID", columns_base_flags, 0.0f, 0);
		ImGui::TableSetupColumn("Action-Remove", columns_base_flags | ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, 1);
		ImGui::TableSetupColumn("Action-Edit", columns_base_flags | ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, 2);

		ImGui::PushButtonRepeat(true);
		ImGuiListClipper clipper;
		clipper.Begin(m_Meshes.size());
		int row_minimum_height = (int)10;
		while (clipper.Step())
		{
			for (int row_n = clipper.DisplayStart; row_n < clipper.DisplayEnd; row_n++)
			{
				if (row_n >= m_Meshes.size())
					break;
				Mesh* item = m_Meshes[row_n];
				// if (!filter.PassFilter(item->Name))
				//     continue;

				ImGui::PushID(item->GetID());
				ImGui::TableNextRow(ImGuiTableRowFlags_None, row_minimum_height);

				ImGui::TableSetColumnIndex(0);
				ImGui::Text("Mesh %d", item->GetID());

				if (ImGui::TableSetColumnIndex(1))
				{
					if (ImGui::ImageButton((ImTextureID)VividGui::Assets::GetInstance()->GetTexMinus()->GetRendererID(), ImVec2(10, 10),
					        ImVec2(0.25, 0.25), ImVec2(0.75, 0.75), 2))
					{
						RemoveMesh(m_Meshes[row_n]);
					}
				}

				if (ImGui::TableSetColumnIndex(2))
				{
					if (ImGui::ImageButton((ImTextureID)VividGui::Assets::GetInstance()->GetTexEdit()->GetRendererID(), ImVec2(10, 10),
					        ImVec2(0.25, 0.25), ImVec2(0.75, 0.75), 2))
					{
						m_Meshes[row_n]->EditMesh();
					}
				}
				ImGui::PopID();
			}
		}
		ImGui::PopButtonRepeat();
		ImGui::EndTable();

		if (ImGui::ImageButton((ImTextureID)VividGui::Assets::GetInstance()->GetTexPlus()->GetRendererID(), ImVec2(10, 10),
		        ImVec2(0.25, 0.25), ImVec2(0.75, 0.75), 2))
		{
			std::string file = FileDialogue::OpenFile({}, {});
			if (!file.empty())
			{
				Mesh* mesh = new Mesh(file);
				AddMesh(mesh);
			}
		}

		for (auto&& mesh : m_Meshes)
		{
			mesh->ImGuiRender();
		}
	}
}