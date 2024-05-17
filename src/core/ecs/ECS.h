#pragma once

#include "editor/camera/Camera.h"
#include "common/types/Types.h"
#include "common/types/SmartPointers.h"
#include "core/ecs/Entity.h"
#include "core/ecs/Component.h"

namespace Vivid
{
	namespace ECS
	{
		extern Map<int, Ref<Component>> g_Components;
		extern Map<int, Ref<Entity>> g_Entities;
		extern int s_EntityID;
		extern int s_ComponentID;

		bool AddComponent(int componentID, int entityID);

		bool RemoveComponent(int componentID, int entityID);

		void Draw(Camera* camera);

		void ImGuiRender();

		template<typename T>
		void GetAllComponents(const ComponentType type, Vector<T*>& components)
		{
			components.reserve(g_Components.size());
			for (auto& component : g_Components)
			{
				if (component.second->GetComponentType() == type)
				{
					components.emplace_back(static_cast<T*>(component.second.get()));
				}
			}
		}

		Ref<Entity> CreateEntity(const String& name);

		Ref<Vivid::Component> GetComponent(ComponentType ct, int entityID);

		template <typename T>
		typename std::enable_if<std::is_base_of<Component,T>::value,Ref<T>>::type CreateComponent()
		{
			Ref<T> component = MakeRef<T>();
			g_Components[component->GetComponentID()] = component;
			return component;
		}
	};
}
