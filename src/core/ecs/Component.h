#pragma once
#include "editor/camera/Camera.h"
#include "core/ecs/Entity.h"

namespace Vivid
{
	class Entity;

	class Component
	{
	protected:
		Vivid::Entity* m_Entity;

	public:
		Component() = default;
		virtual ~Component() = default;
		virtual void Draw(Camera* camera) = 0;
		virtual void ImGuiRender() = 0;

		void SetEntity(Vivid::Entity* entity) { m_Entity = entity; }
	};
}
