#pragma once

#include "editor/camera/Camera.h"
#include "common/types/Types.h"
#include "core/ecs/Entity.h"
#include "core/ecs/Component.h"

namespace Vivid
{
	namespace ECS
	{
		extern Vector<Vivid::Component*> g_Components;
		extern Vector<Vivid::Entity*> g_Entities;
		extern int s_EntityID;

		void AddComponent(Vivid::Component* component, Vivid::Entity* entity);

		bool RemoveComponent(Vivid::Component* component, Vivid::Entity* entity);

		void Draw(Camera* camera);

		void ImGuiRender();

		template <typename T>
		Vector<T*> GetAllComponents()
		{
			Vector<T*> components;
			components.reserve(g_Components.size());
			for (auto& component : g_Components)
			{
				if (typeid(*component) == typeid(T))
				{
					components.push_back(static_cast<T*>(component));
				}
			}
			return components;
		}

		Entity* CreateEntity(String name);

		Entity* CreateEntity(Entity* entity);

	};
}
