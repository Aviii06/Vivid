#include "OrthoCamera.h"

OrthoCamera::OrthoCamera(float left, float right, float bottom, float top)
{
	m_Width = right - left;
	m_Height = top - bottom;

	m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	m_ViewMatrix = glm::mat4(1.0f);
}

void OrthoCamera::SetPosition(const Vec3& position)
{
	m_Position = position;
}

void OrthoCamera::SetRotation(float rotation)
{
	m_Rotation = rotation;
}

void OrthoCamera::SetPerspective(float left, float right, float bottom, float top)
{
	m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}

void OrthoCamera::SetPerspective(glm::mat4 perspective)
{
	m_ProjectionMatrix = perspective;
}

void OrthoCamera::SetViewMatrix(glm::mat4 view)
{
	m_ViewMatrix = view;
}

void OrthoCamera::SetViewportSize(int width, int height)
{
	m_Width = width;
	m_Height = height;
	m_AspectRatio = (float)width / (float)height;
}
