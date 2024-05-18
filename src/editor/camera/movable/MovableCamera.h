#pragma once

#pragma once

#include "editor/camera/Camera.h"
#include "common/maths/Vec.h"

/*!
 * @class MovableCamera
 * @brief A class for the MovableCamera's.
 * @details MovableCamera is a camera that can be moved around in the scene. It can be moved forward, backward, left, right, and can be rotated using the mouse.
 */
class MovableCamera : public Camera
{
protected:
	Vivid::Maths::Vec3 m_Position;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;

public:
	glm::vec3 GetPosition() { return m_Position.ToGLM(); }
	glm::mat4 GetViewMatrix() { return m_ViewMatrix; };
	glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; };

	void SetPosition(const Vivid::Maths::Vec3& position) { m_Position = position; };
	void SetViewMatrix(const glm::mat4& view) { m_ViewMatrix = view; };
	void SetPerspective(const glm::mat4& perspective) { m_ProjectionMatrix = perspective; };

	virtual void SetViewportSize(int width, int height) = 0;

	virtual void MoveForward() = 0;
	virtual void MoveBackward() = 0;
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;
	virtual void ProcessMouseScroll(float scrollOffset) = 0;
	virtual void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true) = 0;
};
