#include "ModelComponent.h"
#include "imgui/imgui/imgui.h"

#define MAX_MESHES 10

Vivid::ModelComponent::ModelComponent()
{
	m_Meshes.reserve(MAX_MESHES);
}

void Vivid::ModelComponent::ImGuiRender()
{
	ImGui::Text("Model");
	if (ImGui::Button("Add Mesh"))
	{
	}
}

void Vivid::ModelComponent::Draw(Camera* camera)
{
	for (auto& mesh : m_Meshes)
		mesh->Draw(camera);
}

void Vivid::ModelComponent::AddMesh(Vivid::Mesh* mesh)
{
	m_Meshes.push_back(mesh);
}

void Vivid::ModelComponent::RemoveMesh(Vivid::Mesh* mesh)
{
	m_Meshes.erase(std::remove(m_Meshes.begin(), m_Meshes.end(), mesh), m_Meshes.end());
}
