#include "OrthoCamera.h"
#include "common/maths/Vec.h"
#include "editor/Application.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

OrthoCamera::OrthoCamera(Vivid::Maths::Vec3 position, float rotation, float zoomLevel, float near, float far)
    : m_Rotation(rotation)
    , m_ZoomLevel(zoomLevel)
    , m_Near(near)
    , m_Far(far)
{
	m_Position = position;
	m_Left = 0;
	m_Right = m_ViewportWidth;
	m_Bottom = 0;
	m_Top = m_ViewportHeight;

	updateProjectionMatrix();
	updateViewMatrix();
}

void OrthoCamera::updateProjectionMatrix()
{
//	m_ProjectionMatrix = glm::ortho(m_Left * m_ZoomLevel, m_Right * m_ZoomLevel, m_Bottom * m_ZoomLevel, m_Top * m_ZoomLevel, m_Near, m_Far);
	// For now ignore zoom level
	m_ProjectionMatrix = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, m_Near, m_Far);
}

void OrthoCamera::updateViewMatrix()
{
	// TODO: Add rotations and movement
//	m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position.ToGLM());
	m_ViewMatrix = glm::mat4(1.0f);
}

void OrthoCamera::SetRotation(float rotation)
{
	m_Rotation = rotation;
}

void OrthoCamera::SetPerspective(float left, float right, float bottom, float top)
{
	m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}

void OrthoCamera::SetViewportSize(int width, int height)
{
	m_Left = 0;
	m_Right = (float)width;
	m_Bottom = 0;
	m_Top = (float)height;
	m_ViewportWidth = width;
	m_ViewportHeight = height;
	updateProjectionMatrix();
	updateViewMatrix();
}

void OrthoCamera::MoveForward()
{
//	m_ZoomLevel -= m_Speed;
	m_ZoomLevel = std::fmax(m_ZoomLevel, 0.01f);
	updateViewMatrix();
}

void OrthoCamera::MoveBackward()
{
//	m_ZoomLevel += m_Speed;
	m_ZoomLevel = std::fmax(m_ZoomLevel, 0.01f);
	updateViewMatrix();
}

void OrthoCamera::MoveLeft()
{
	m_Position.x += m_Speed;
	updateViewMatrix();
}

void OrthoCamera::MoveRight()
{
	m_Position.x -= m_Speed;
	updateViewMatrix();
}

void OrthoCamera::ProcessMouseScroll(float scrollOffset)
{
	m_ZoomLevel -= scrollOffset;
	m_ZoomLevel = std::fmax(m_ZoomLevel, 0.25f);
	updateProjectionMatrix();
}

void OrthoCamera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
	m_Position.x += xOffset * m_Speed * m_ScrollSpeed;
	m_Position.y -= yOffset * m_Speed * m_ScrollSpeed;
	updateViewMatrix();
}
