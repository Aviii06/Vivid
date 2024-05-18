#include "Entity.h"
#include "editor/Application.h"
#include "imgui/imgui/imgui.h"

#include "Component.h"
#include "core/ecs/ECS.h"
#include "core/ecs/ComponentFactory.h"

#define MAX_COMPONENTS 10

Vivid::Entity::Entity(int id, String name)
    : m_ID(id)
    , m_Name(name)
{
	ECS::s_EntityID++;
	m_Components.reserve(MAX_COMPONENTS);
}

void Vivid::Entity::ImguiRender()
{
	String name = "Entity: " + m_Name;
	ImGui::Text(name.c_str());

	for (auto& componentID : m_Components)
	{
		ComponentType ct = ECS::g_Components[componentID]->GetComponentType();
		if (ImGui::TreeNode(g_AllComponentStrings.at(ct).c_str()))
		{
			ECS::g_Components[componentID]->ImGuiRender();

			ImGui::TreePop();
		}
	}
}

void Vivid::Entity::Draw(Camera* camera)
{
	for (auto& component : m_Components)
	{
		ECS::g_Components[component]->Draw(camera);
	}
}

void Vivid::Entity::DrawGizmo(Camera* camera)
{
	int transformID = HasComponent(ComponentType::TransformComponent);
	auto transform = static_cast<TransformComponent*>(ECS::g_Components[transformID].get());
	if (transform)
	{
		transform->DrawGizmo(camera);
	}
}

int Vivid::Entity::HasComponent(ComponentType ct)
{
	for (int i : m_Components)
	{
		if (ct == ECS::g_Components[i]->GetComponentType())
		{
			return i;
		}
	}

	return -1;
}

void Vivid::Entity::RemoveComponent(const int& componentID)
{
	for (int i = 0; i < m_Components.size(); i++)
	{
		int id = m_Components[i];
		if (ECS::g_Components[id]->GetComponentType() == ECS::g_Components[componentID]->GetComponentType())
		{
			m_Components.erase(m_Components.begin() + i);
			std::cout << "Component Removed\n";
		}
	}
	std::cout << "Component Not found\n";
}

void Vivid::Entity::AddComponent(const int& componentID)
{
	m_Components.push_back(componentID);
}
