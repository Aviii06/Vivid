#pragma once

#include "glm/glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

/*!
 * @enum CameraMovement
 * @brief CameraMovement enum
 * @details An enum that represents the camera movement.
 */
enum class CameraMovement
{
	FORWARD = 1,
	BACKWARD = 2,
	LEFT = 3,
	RIGHT = 4
};

/*!
 * @class Camera
 * @brief A class that represents the camera.
 * @details It contains functions to get the view matrix, get the projection matrix, set the perspective, set the view matrix, set the viewport size, get the viewport width, and get the viewport height. This is an abstract class.
 */
class Camera
{
protected:
	int m_ViewportWidth = 1920;
	int m_ViewportHeight = 1080;

public:
	virtual glm::mat4 GetViewMatrix() = 0;
	virtual glm::mat4 GetProjectionMatrix() = 0;

	virtual void SetPerspective(glm::mat4 perspective) = 0;
	virtual void SetViewMatrix(glm::mat4 view) = 0;

	virtual void SetViewportSize(int width, int height) = 0;
	int GetViewportWidth() { return m_ViewportWidth; }
	int GetViewportHeight() { return m_ViewportHeight; }
};