#pragma once
#include "common/types/Types.h"
#include "common/types/SmartPointers.h"
#include "core/ecs/Component.h"

#include "editor/camera/Camera.h"
#include "editor/camera/EditorCamera.h"

namespace Vivid
{
	class Entity
	{
	private:
		int m_ID;
		String m_Name;
		Vector<Component*> m_Components;

		void drawGUI();
		void drawComponents();

	public:
		Entity() = default;
		Entity(int id, String name);
		~Entity();

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);

		void Draw();

		template <typename T>
		T* GetComponent()
		{
			for (auto& component : m_Components)
			{
				if (typeid(*component) == typeid(T))
				{
					return static_cast<T*>(component);
				}
			}
			return nullptr;
		}

		inline int GetID() const { return m_ID; }
		inline String GetName() const { return m_Name; }
		inline Vector<Component*> GetComponents() const { return m_Components; }
	};

}
