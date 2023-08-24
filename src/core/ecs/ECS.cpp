#include "ECS.h"

Vector<Vivid::Component*> Vivid::ECS::g_Components;

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
	for (auto& component : g_Components)
	{
		component->Draw(camera);
	}
}

void Vivid::ECS::ImGuiRender()
{
	for (auto& component : g_Components)
	{
		component->ImGuiRender();
	}
}
