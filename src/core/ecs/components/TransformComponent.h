#pragma once
#include "core/ecs/Component.h"
#include "common/maths/Vec.h"
#include "imguizmo/ImGuizmo.h"

namespace Vivid
{

	class TransformComponent : public Component
	{
	private:
		Vec3 m_Position;
		Vec3 m_Rotation;
		Vec3 m_Scale = Vec3(1.0f, 1.0f, 1.0f);
		bool m_FixScale = false;
		glm::mat4 m_Transform = glm::mat4(1.0f);
        ImGuizmo::OPERATION m_CurrentGizmoOperation = ImGuizmo::TRANSLATE;
        ImGuizmo::MODE m_CurrentGizmoMode = ImGuizmo::WORLD;
        bool m_UsingSnap = false;
        float m_Snap[3] = { 1.f, 1.f, 1.f };


        void updateTransformImGUI();
        void drawGizmo(Camera* camera);

	public:
		TransformComponent() = default;
		TransformComponent(Vec3 position, Vec3 rotation, Vec3 scale)
		    : m_Position(position)
		    , m_Rotation(rotation)
		    , m_Scale(scale)
		{
			m_Transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x, m_Position.y, m_Position.z));
		}
		virtual ~TransformComponent() = default;
		void Draw(Camera* camera) override;
		void ImGuiRender() override;

		inline Vec3 GetPosition() const { return m_Position; }
		inline Vec3 GetRotation() const { return m_Rotation; }
		inline Vec3 GetScale() const { return m_Scale; }
		inline glm::mat4 GetTransform() const { return m_Transform; }

		inline void SetPosition(Vec3 position) { m_Position = position; }
        inline void SetRotation(Vec3 rotation) { m_Rotation = rotation; }
        inline void SetScale(Vec3 scale) { m_Scale = scale; }

		String GetComponentName() override { return "Transform Component"; }

        inline ImGuizmo::OPERATION GetCurrentGizmoOperation() const { return m_CurrentGizmoOperation; }
        inline ImGuizmo::MODE GetCurrentGizmoMode() const { return m_CurrentGizmoMode; }
        inline bool IsUsingSnap() const { return m_UsingSnap; }
        inline float* GetSnap() { return m_Snap; }

        void DrawGizmo(Camera* camera);
	};
}
