#pragma once

#include "editor/camera/Camera.h"
#include "ComponentType.h"

namespace Vivid
{
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

		[[nodiscard]] int GetOwnerEntityID() const { return m_OwnerEntityID; }
		void SetEntity(const int& entityID) { m_OwnerEntityID = entityID; }

		virtual ComponentType GetComponentType() = 0;
		int GetComponentID() const { return m_ID; }
	};
}
