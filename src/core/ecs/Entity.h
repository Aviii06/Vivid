#pragma once

#include "common/types/Types.h"
#include "common/types/SmartPointers.h"

#include "editor/camera/Camera.h"
#include "editor/camera/movable/EditorCamera.h"

namespace Vivid
{
	class Component;

	class Entity
	{
	private:
		int m_ID;
		String m_Name = "";
		Vector<Ref<Vivid::Component>> m_Components;

	public:
		Entity() = default;

		Entity(int id, String name);

		~Entity();

		void AddComponent(Ref<Vivid::Component> component);

		void RemoveComponent(int index);
		void RemoveComponent(Ref<Vivid::Component> component);

		void Draw(Camera* camera);

		void DrawGUI();

		inline int GetID() const { return m_ID; }

		inline String GetName() const { return m_Name; }
		void SetName(String name) { m_Name = name; }

		inline Vector<Ref<Vivid::Component>> GetAllComponents() const { return m_Components; }

		template <typename T>
		T* GetComponent()
		{
			for (auto component : m_Components)
			{
				if (GetType(component.get()) == typeid(T).name())
				{
					return static_cast<T*>(component.get());
				}
			}
			return nullptr;
		}

		const char* GetType(Component* component);

		void DrawGizmo(Camera* camera);

		int HasComponent(const String& componentName);
	};

}
