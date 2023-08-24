#pragma once
#include "core/components/Component.h"
#include "common/maths/Vec.h"

namespace Vivid
{

	class TransformComponent : public Component
	{
	private:
		Vec3 m_Position;
		Vec3 m_Rotation;
		Vec3 m_Scale;

	public:
		TransformComponent() = default;
		virtual ~TransformComponent() = default;
		void OnUpdate() override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}
