#include "Entity.h"

Vivid::Entity::Entity(int id, String name)
: m_ID(id), m_Name(std::move(name))
{
}

Vivid::Entity::~Entity()
{
}

void Vivid::Entity::AddComponent(Ref<Vivid::Component> component)
{
	m_Components.push_back(component.get());
}

void Vivid::Entity::RemoveComponent(Ref<Vivid::Component> component)
{
	for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		if (*it == component.get())
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
		component->Draw();
	}
}

void Vivid::Entity::Draw()
{
	drawComponents();
	drawGUI();
}
