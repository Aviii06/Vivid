#pragma once

#include "editor/camera/Camera.h"
#include "common/types/Types.h"
#include "core/ecs/Entity.h"
#include "core/ecs/Component.h"

namespace Vivid
{
	namespace ECS
	{
		extern Vector<Ref<Vivid::Component>> g_Components;
		extern Vector<Vivid::Entity*> g_Entities;
		extern Vector<Ref<Vivid::Component>> g_AllComponents;
		extern int s_EntityID;

		bool AddComponent(Ref<Vivid::Component> component, Vivid::Entity* entity);

		bool RemoveComponent(Ref<Vivid::Component> component, Vivid::Entity* entity);

		void Draw(Camera* camera);

		void ImGuiRender();

		template<typename T>
		void GetAllComponents(ComponentType type, Vector<T*>& components)
		{
			components.reserve(g_Components.size());
			for (auto& component : g_Components)
			{
				if (component->GetComponentType() == type)
				{
					components.emplace_back(static_cast<T*>(component.get()));
				}
			}
		}

		Entity* CreateEntity(String name);

		Entity* CreateEntity(Entity* entity);
	};
}
