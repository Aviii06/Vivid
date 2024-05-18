#include "ECS.h"
#include "ComponentFactory.h"

Map<int, Ref<Vivid::Component>> g_Components;
Map<int, Ref<Vivid::Entity>> g_Entities;

int Vivid::ECS::s_EntityID = 0;
int Vivid::ECS::s_ComponentID = 0;

bool Vivid::ECS::AddComponent(int componentID, int entityID)
{
	// Check if the component already exists
	// If So then just update the component
	Ref<Component> component = g_Components[componentID];
	const ComponentType ct = component->GetComponentType();

	const int index = g_Entities[entityID]->HasComponent(ct);
	Ref<Entity> entity = g_Entities[entityID];
	if (index != -1)
	{
		const String& componentName = g_AllComponentStrings.at(ct);
		std::cerr << componentName << " already exists\n"
		          << std::endl;
		std::cout << "Updating component: " << componentName << std::endl;

		entity->RemoveComponent(componentID);
	}

	component->SetEntity(entity->GetEntityID());

	g_Components[componentID] = component;
	entity->AddComponent(componentID);
	return true;
}

bool Vivid::ECS::RemoveComponent(int componentID, int entityID)
{
	Ref<Component> component = g_Components[componentID];
	const ComponentType ct = component->GetComponentType();

	const int index = g_Entities[entityID]->HasComponent(ct);
	Ref<Entity> entity = g_Entities[index];
	component->SetEntity(entity->GetEntityID());

	for (auto&& comp : g_Components)
	{
		if (comp.second->GetComponentType() == component->GetComponentType())
		{
			entity->RemoveComponent(componentID);
			auto it = g_Components.find(comp.first);
			g_Components.erase(it);
			return true;
		}
	}

	const String& componentName = g_AllComponentStrings.at(ct);
	std::cerr << "Failed to remove component: " << componentName << std::endl;
	return false;
}

void Vivid::ECS::Draw(Camera* camera)
{
	for (auto& entity : g_Entities)
	{
		entity.second->Draw(camera);
	}
}

void Vivid::ECS::ImGuiRender()
{
	for (auto& entity : g_Entities)
	{
		entity.second->ImguiRender();
	}
}

Ref<Vivid::Entity> Vivid::ECS::CreateEntity(const String& name)
{
	Ref<Entity> entity = MakeRef<Entity>(s_EntityID, name);
	g_Entities[entity->GetEntityID()] = entity;

	// std::cout << g_Entities[entity->GetID()] << "\n";
	// std::cout << entity << "\n";

	auto tc = ECS::CreateComponent<TransformComponent>();
	AddComponent(tc->GetComponentID(), entity->GetEntityID());
	return entity;
}

Ref<Vivid::Component> Vivid::ECS::GetComponent(ComponentType ct, int entityID)
{
	int componentID = g_Entities[entityID]->HasComponent(ct);

	if (componentID == -1)
	{
		return nullptr;
	}
	return g_Components[componentID];
}
