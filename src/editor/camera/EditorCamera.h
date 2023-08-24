#pragma once

#include "Camera.h"

/// Editor EditorCamera has the ability to move around the scene using WASD keys and mouse in an intuitive way.
class EditorCamera : public Camera
{
private:
	float m_FOV = 60.0f;
	float m_NearCip = 0.1f;
	float m_FarClip = 5000.0f;
	float m_AspectRatio = 1.7778f; // 16:9 = m_ViewportWidth / m_ViewportHeight

	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);

	int m_ViewportWidth = 1280;
	int m_ViewportHeight = 720;

	glm::mat4 m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV),
	    m_AspectRatio, m_NearCip, m_FarClip);
	glm::mat4 m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front,
	    glm::vec3(0.0f, 1.0f, 0.0f));

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

	void ProcessKeyboard(CameraMovement direction);

	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

	void ProcessMouseScroll(float scrollOffset);

	glm::vec3 GetPosition() { return m_Position; }
	glm::mat4 GetViewMatrix() { return m_ViewMatrix; };
	glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; };
	float GetYaw() { return m_Yaw; }
	float GetPitch() { return m_Pitch; }
	float GetMovementSpeed() { return m_MovementSpeed; }
	float GetMouseSensitivity() { return m_MouseSensitivity; }
	float GetZoom() { return m_ZoomSensitivity; }

	void SetPerspective(glm::mat4 perspective);
	void SetPerspective(float fov, float aspect, float near, float far);
	void SetViewMatrix(glm::mat4 view);

	void SetViewportSize(int width, int height);
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();

	CameraType GetCameraType() override { return CameraType::EDITOR; }
};
