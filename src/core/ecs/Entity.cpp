#include "Entity.h"
#include "editor/Application.h"
#include "imgui/imgui/imgui.h"

#include "Component.h"
#include "core/ecs/ECS.h"
#include "core/ecs/components/TransformComponent.h"

#define MAX_COMPONENTS 10

Vivid::Entity::Entity(int id, String name)
    : m_ID(id)
    , m_Name(std::move(name))
{
	ECS::s_EntityID++;
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
	ImGui::Text(name.c_str());

	for (auto& component : m_Components)
	{
		if (ImGui::TreeNode(component->GetComponentName().c_str()))
		{
			component->ImGuiRender();

			ImGui::TreePop();
		}
	}
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

void Vivid::Entity::DrawGizmo(Camera* camera)
{
	auto transform = GetComponent<TransformComponent>();
	if (transform)
	{
		transform->DrawGizmo(camera);
	}
}