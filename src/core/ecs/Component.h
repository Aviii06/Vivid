#pragma once

#include "editor/camera/Camera.h"
#include "Entity.h"

namespace Vivid
{
	enum class ComponentType
	{
		TransformComponent,
		ModelComponent,
		PointLightComponent,
		DirectionalLightComponent,
	};

	class Component
	{
	protected:
		friend class Entity;

		Vivid::Entity* m_Entity;

	public:
		Component() = default;

		virtual ~Component() = default;

		virtual void Draw(Camera* camera) = 0;

		virtual void ImGuiRender() = 0;

		void SetEntity(Vivid::Entity* entity) { m_Entity = entity; }

		Vivid::Entity* GetEntity() const { return m_Entity; }

		virtual String GetComponentName() = 0;
		virtual ComponentType GetComponentType() = 0;
	};
}
