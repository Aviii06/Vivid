#pragma once

#include "editor/camera/movable/MovableCamera.h"
#include "common/maths/Vec.h"

class OrthoCamera : public MovableCamera
{
private:
	float m_Rotation = 0.0f;
	//	glm::mat4 m_ProjectionMatrix;
	//	glm::mat4 m_ViewMatrix;

	float m_Left, m_Right, m_Bottom, m_Top;
	float m_Near, m_Far;

	float m_ZoomLevel = 1.0f;

	void updateProjectionMatrix();
	void updateViewMatrix();

	float m_Speed = 0.5f;
	float m_ScrollSpeed = 1;

public:
	OrthoCamera(Vivid::Maths::Vec3 position, float rotation, float zoomLevel, float near = -1.0f, float far = 1.0f);

	~OrthoCamera() = default;

	void SetRotation(float rotation);

	float GetRotation() const { return m_Rotation; }

	void SetPerspective(float left, float right, float bottom, float top);

	//	glm::mat4 GetViewMatrix() override { return m_ProjectionMatrix; };
	//	glm::mat4 GetProjectionMatrix() override { return m_ViewMatrix; };
	Vivid::Maths::Vec4 GetBounds() { return Vivid::Maths::Vec4(m_Left, m_Right, m_Bottom, m_Top); };

	void SetViewportSize(int width, int height) override;

	void MoveForward() override;
	void MoveBackward() override;
	void MoveLeft() override;
	void MoveRight() override;
	void ProcessMouseScroll(float scrollOffset) override;
	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) override;

	Vivid::Maths::Vec2 ScreenToWorldCoords(float x, float y);
};
