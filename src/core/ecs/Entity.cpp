#include "Entity.h"
#include "editor/Application.h"
#define MAX_COMPONENTS 10

Vivid::Entity::Entity(int id, String name)
    : m_ID(id)
    , m_Name(std::move(name))
{
	m_Components.reserve(MAX_COMPONENTS);
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

void Vivid::Entity::drawGUI()
{
	for (auto& component : m_Components)
	{
		component->ImGuiRender();
	}
}

void Vivid::Entity::drawComponents()
{
	for (auto& component : m_Components)
	{
		component->Draw(Application::GetInstance()->GetCamera());
	}
}

void Vivid::Entity::Draw()
{
	drawComponents();
	drawGUI();
}