#include "EditorCamera.h"

EditorCamera::EditorCamera(float fov, float aspect, float near, float far)
    : m_FOV(fov)
    , m_AspectRatio(aspect)
    , m_NearCip(near)
    , m_FarClip(far)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearCip, m_FarClip);
}

// Process keyboard input
void EditorCamera::ProcessKeyboard(CameraMovement direction)
{
	float velocity = m_MovementSpeed;

	switch (direction)
	{
	case CameraMovement::FORWARD:
		m_Position += m_Front * velocity;
		break;
	case CameraMovement::BACKWARD:
		m_Position -= m_Front * velocity;
		break;
	case CameraMovement::RIGHT:
		m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * velocity;
		break;
	case CameraMovement::LEFT:
		m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * velocity;
		break;
	}

	updateViewMatrix();
}

// Process mouse movement
void EditorCamera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
	xOffset *= m_MouseSensitivity;
	yOffset *= m_MouseSensitivity;

	m_Yaw += xOffset;
	m_Pitch += yOffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
	}

	updateCameraVectors();
	updateViewMatrix();
}

// Process mouse scroll
void EditorCamera::ProcessMouseScroll(float scrollOffset)
{
	if (m_ZoomSensitivity >= 1.0f && m_ZoomSensitivity <= 45.0f)
		m_ZoomSensitivity -= scrollOffset;
	if (m_ZoomSensitivity <= 1.0f)
		m_ZoomSensitivity = 1.0f;
	if (m_ZoomSensitivity >= 45.0f)
		m_ZoomSensitivity = 45.0f;

	updateProjectionMatrix();
}

// Update camera vectors
void EditorCamera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = -sin(glm::radians(m_Pitch));
	front.z = -cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}
void EditorCamera::updateProjectionMatrix()
{
	m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearCip, m_FarClip);
}

// Updates view matrix based on camera position and orientation
void EditorCamera::updateViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void EditorCamera::SetPerspective(float fov, float aspect, float near, float far)
{
	m_FOV = fov;
	m_AspectRatio = aspect;
	m_NearCip = near;
	m_FarClip = far;
	updateProjectionMatrix();
}

void EditorCamera::SetViewportSize(int width, int height)
{
	m_AspectRatio = (float)width / (float)height;
	updateProjectionMatrix();
}

void EditorCamera::MoveForward()
{
	m_Position += m_Front * m_MovementSpeed;
	updateViewMatrix();
}

void EditorCamera::MoveBackward()
{
	m_Position -= m_Front * m_MovementSpeed;
	updateViewMatrix();
}

void EditorCamera::MoveLeft()
{
	m_Position -= m_Right * m_MovementSpeed;
	updateViewMatrix();
}

void EditorCamera::MoveRight()
{
	m_Position += m_Right * m_MovementSpeed;
	updateViewMatrix();
}

void EditorCamera::SetViewMatrix(glm::mat4 view)
{
	m_ViewMatrix = view;
}

void EditorCamera::SetPerspective(glm::mat4 perspective)
{
	m_ProjectionMatrix = perspective;
}