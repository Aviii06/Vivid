#include "ECS.h"

Vector<Vivid::Component*> Vivid::ECS::g_Components;
Vector<Vivid::Entity*> Vivid::ECS::g_Entities;
int Vivid::ECS::s_EntityID = 0;

void Vivid::ECS::AddComponent(Vivid::Component* component, Vivid::Entity* entity)
{
	component->SetEntity(entity);
	g_Components.push_back(component);
	entity->AddComponent(component);
}

bool Vivid::ECS::RemoveComponent(Vivid::Component* component, Vivid::Entity* entity)
{
	component->SetEntity(entity);

	for (auto it = g_Components.begin(); it != g_Components.end(); ++it)
	{
		if (*it == component)
		{
			g_Components.erase(it);
			entity->RemoveComponent(component);
			return true;
		}
	}

	return false;
}

void Vivid::ECS::Draw(Camera* camera)
{
	for (auto& entity : g_Entities)
	{
		entity->Draw(camera);
	}
}

void Vivid::ECS::ImGuiRender()
{
	for (auto& entity : g_Entities)
	{
		entity->DrawGUI();
	}
}

Vivid::Entity* Vivid::ECS::CreateEntity(String name)
{
	Entity* entity = new Entity(s_EntityID++, name);
	g_Entities.push_back(entity);
	return entity;
}

Vivid::Entity* Vivid::ECS::CreateEntity(Vivid::Entity* entity)
{
	g_Entities.push_back(entity);
	return entity;
}
