#pragma once

#include "editor/camera/Camera.h"
#include "common/maths/Vec.h"

class OrthoCamera : public Camera
{
private:
	float m_AspectRatio = 1.7778f;
	float m_ZoomLevel = 1.0f;
	float m_Rotation = 0.0f;
	Vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;

public:
	OrthoCamera(float left, float right, float bottom, float top);

	~OrthoCamera() = default;

	void SetPosition(const Vec3& position);

	void SetRotation(float rotation);

	Vec3 GetPosition() const { return m_Position; }

	float GetRotation() const { return m_Rotation; }

	void SetPerspective(float left, float right, float bottom, float top);

	glm::mat4 GetViewMatrix() override { return m_ProjectionMatrix; };

	glm::mat4 GetProjectionMatrix() override { return m_ViewMatrix; };

	void SetPerspective(glm::mat4 perspective) override;

	void SetViewMatrix(glm::mat4 view) override;

	void SetViewportSize(int width, int height) override;
};
