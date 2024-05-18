#pragma once

#include "editor/camera/movable/MovableCamera.h"
#include "common/maths/Vec.h"

/*!
 * @class EditorCamera
 * @brief A class for the EditorCamera.
 * @details EditorCamera is a camera that can be moved around in the scene.
 * It can be moved forward, backward, left, right, and can be rotated using the mouse.
 * It also has a perspective. EditorCamera works on perspective projection and is the default camera for rendering.
 */
class EditorCamera : public MovableCamera
{
private:
	float m_FOV = 60.0f;
	float m_NearCip = 0.1f;
	float m_FarClip = 5000.0f;
	float m_AspectRatio = 1.7778f; // 16:9 = m_ViewportWidth / m_ViewportHeight

	Vivid::Maths::Vec3 m_Front = Vivid::Maths::Vec3(0.0f, 0.0f, -1.0f);
	Vivid::Maths::Vec3 m_Up = Vivid::Maths::Vec3(0.0f, 1.0f, 0.0f);
	Vivid::Maths::Vec3 m_Right = Vivid::Maths::Vec3(1.0f, 0.0f, 0.0f);

	// We'll never roll the camera. https://sidvind.com/wiki/Yaw,_pitch,_roll_camera
	float m_Yaw = 0.0f;
	float m_Pitch = 0.0f;

	float m_MovementSpeed = 15.0f;
	float m_MouseSensitivity = 0.08f;
	float m_ZoomSensitivity = 0.08f;

	glm::vec2 m_MousePosition = glm::vec2(0.0f, 0.0f);

	void updateCameraVectors();
	void updateProjectionMatrix();
	void updateViewMatrix();

public:
	EditorCamera() = default;
	EditorCamera(float fov, float aspect, float near, float far);

	float GetYaw() { return m_Yaw; }
	float GetPitch() { return m_Pitch; }
	float GetMovementSpeed() { return m_MovementSpeed; }
	float GetMouseSensitivity() { return m_MouseSensitivity; }
	float GetZoom() { return m_ZoomSensitivity; }

	void SetPerspective(float fov, float aspect, float near, float far);
	void SetViewportSize(int width, int height) override;

	void MoveForward() override;
	void MoveBackward() override;
	void MoveLeft() override;
	void MoveRight() override;
	void ProcessMouseScroll(float scrollOffset) override;
	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) override;
};
