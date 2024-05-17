#pragma once

#include "common/types/Types.h"
#include "editor/camera/Camera.h"
#include "core/ecs/ComponentType.h"

namespace Vivid
{
	/// Contains an Entity
	/// Every Entity contains a vector of components which can further be Added and Removed
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

		[[nodiscard]] int GetID() const { return m_ID; }
		[[nodiscard]] String GetName() const { return m_Name; }
		void SetName(String& name) { m_Name = std::move(name); }
		void SetName(String&& name) { m_Name = name; }

		/// Return -1 if no component found.
		int HasComponent(ComponentType ct);

		void RemoveComponent(const int& componentID);
		void AddComponent(const int& componentID);
	};

}
