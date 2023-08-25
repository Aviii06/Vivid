#include "Entity.h"
#include "editor/Application.h"
#include "imgui/imgui/imgui.h"

#include "Component.h"
#include "core/ecs/ECS.h"
#define MAX_COMPONENTS 10

Vivid::Entity::Entity(int id, String name)
    : m_ID(id)
    , m_Name(std::move(name))
{
	m_Components.reserve(MAX_COMPONENTS);
	ECS::CreateEntity(this);
}

Vivid::Entity::~Entity()
{
}

void Vivid::Entity::AddComponent(Vivid::Component* component)
{
	m_Components.push_back(component);
}

void Vivid::Entity::RemoveComponent(Vivid::Component* component)
{
	for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		if (*it == component)
		{
			m_Components.erase(it);
			break;
		}
	}
}

void Vivid::Entity::DrawGUI()
{
	String name = "Entity: " + m_Name;
	ImGui::Begin(name.c_str());
	for (auto& component : m_Components)
	{

		ImGui::SeparatorText(component->GetComponentName().c_str());
		component->ImGuiRender();
	}
	ImGui::End();
}

void Vivid::Entity::Draw(Camera* camera)
{
	for (auto& component : m_Components)
	{
		component->Draw(Application::GetInstance()->GetCamera());
	}
}

const char* Vivid::Entity::GetType(Vivid::Component* component)
{
	return typeid(*component).name();
}