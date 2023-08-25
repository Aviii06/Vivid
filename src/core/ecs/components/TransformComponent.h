#pragma once
#include "core/ecs/Component.h"
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
		TransformComponent(Vec3 position, Vec3 rotation, Vec3 scale)
		    : m_Position(position)
		    , m_Rotation(rotation)
		    , m_Scale(scale)
		{
		}
		virtual ~TransformComponent() = default;
		void Draw(Camera* camera) override;
		void ImGuiRender() override;

		inline Vec3 GetPosition() const { return m_Position; }
		inline Vec3 GetRotation() const { return m_Rotation; }
		inline Vec3 GetScale() const { return m_Scale; }

		inline void SetPosition(Vec3 position) { m_Position = position; }
	};
}
