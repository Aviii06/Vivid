#pragma once

#include "editor/camera/Camera.h"
#include "ComponentType.h"

namespace Vivid
{
	/*!
	 * @class Component
	 * @brief Contains a Component.
	 * @details Component is a class that contains a component. It is a base class for all the components.
	 * It contains a unique ID for every component. It also contains the ID of the entity to which it belongs.
	 */
	class Component
	{
	private:
		const int m_ID;

	protected:
		int m_OwnerEntityID = 0;

	public:
		Component();
		virtual ~Component() = default;

		virtual void Draw(Camera* camera) = 0;
		virtual void ImGuiRender() = 0;

		[[nodiscard]]
		int GetOwnerEntityID() const { return m_OwnerEntityID; }
		void SetEntity(const int& entityID) { m_OwnerEntityID = entityID; }

		virtual ComponentType GetComponentType() = 0;
		int GetComponentID() const { return m_ID; }
	};
}
