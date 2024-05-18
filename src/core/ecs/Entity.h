#pragma once

#include "common/types/Types.h"
#include "editor/camera/Camera.h"
#include "core/ecs/ComponentType.h"

namespace Vivid
{
	/// Contains an Entity
	/// Every Entity contains a vector of components which can further be Added and Removed
	/*!
	 * @class Entity
	 * @brief Contains an Entity.
	 * @details Entity is an object you see in the scene-tree. It contains a vector of componentsIDs which can be added and removed.
	 * All the Entities are stored in a gloabal map in the @namespace ECS. Every Entity has a unique ID, which is incremented every
	 * time a new Entity is created.
	 */
	class Entity
	{
	private:
		int m_ID = 0;
		String m_Name;
		Vector<int> m_Components;

	public:
		Entity() = default;
		Entity(int id, String name);
		~Entity() = default;

		void Draw(Camera* camera);
		void ImguiRender();
		void DrawGizmo(Camera* camera);

		[[nodiscard]]
		int GetEntityID() const { return m_ID; }
		[[nodiscard]]
		String GetName() const { return m_Name; }
		void SetName(String& name) { m_Name = std::move(name); }
		void SetName(String&& name) { m_Name = name; }

		/*!
		 * @brief Checks if the Entity has a component.
		 * @details Checks if the Entity has a component of the given type.
		 * @param ct The type of the component.
		 * @return The ID of the component if found, -1 if not found.
		 */
		int HasComponent(ComponentType ct);

		void RemoveComponent(const int& componentID);
		void AddComponent(const int& componentID);
	};

}
