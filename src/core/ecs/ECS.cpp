#include "ECS.h"
#include "core/ecs/components/TransformComponent.h"
#include "core/ecs/components/model/ModelComponent.h"
#include "core/ecs/components/light/PointLightComponent.h"
#include "core/ecs/components/light/DirectionalLightComponent.h"

Vector<Ref<Vivid::Component>> Vivid::ECS::g_Components;
Vector<Vivid::Entity*> Vivid::ECS::g_Entities;
Vector<Ref<Vivid::Component>> Vivid::ECS::g_AllComponents = {
	MakeRef<Vivid::TransformComponent>(),
	MakeRef<Vivid::ModelComponent>(),
	MakeRef<Vivid::PointLightComponent>(),
	MakeRef<Vivid::DirectionalLightComponent>()
};

int Vivid::ECS::s_EntityID = 0;

bool Vivid::ECS::AddComponent(Ref<Vivid::Component> component, Vivid::Entity* entity)
{
	// Check if the component already exists
	// If So then just update the component
	int index = entity->HasComponent(component->GetComponentName());
	if (index != -1)
	{

		std::cerr << component->GetComponentName() << "already exists\n" << std::endl;
		std::cout << "Updating component: " << component->GetComponentName() << std::endl;
		entity->RemoveComponent(index);
	}

	component->SetEntity(entity);

	g_Components.push_back(component);
	entity->AddComponent(component);
	return true;
}

bool Vivid::ECS::RemoveComponent(Ref<Vivid::Component> component, Vivid::Entity* entity)
{
	component->SetEntity(entity);

	for (int  i = 0; i < g_Components.size(); i++)
	{
		if (g_Components[i]->GetComponentName() == component->GetComponentName())
		{
			g_Components.erase(g_Components.begin() + i);
			entity->RemoveComponent(component);
			return true;
		}
	}

	std::cerr << "Failed to remove component: " << component->GetComponentName() << std::endl;
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
	Entity* entity = new Entity(s_EntityID, name);
	return entity;
}

Vivid::Entity* Vivid::ECS::CreateEntity(Vivid::Entity* entity)
{
	g_Entities.emplace_back(entity);
	return entity;
}
