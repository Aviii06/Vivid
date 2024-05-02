#include "ModelComponent.h"
#include "imgui/imgui/imgui.h"
#include "core/ecs/components/TransformComponent.h"
#include "core/os/FileDialogue.h"
#include "core/renderer/Texture.h"

#define MAX_MESHES 10

Vivid::ModelComponent::ModelComponent()
{
	m_Meshes.reserve(MAX_MESHES);
}

void Vivid::ModelComponent::ImGuiRender()
{
	ImGui::Text("Model");

	ImGui::Text("Meshes");
	for (int i = 0; i < m_Meshes.size(); i++)
	{
		ImGui::Text("Mesh %d", i);
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)texMinus->getRendererID(), ImVec2(50, 50)))
		{
			RemoveMesh(m_Meshes[i]);
		}
	}
}

void Vivid::ModelComponent::Draw(Camera* camera)
{
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
