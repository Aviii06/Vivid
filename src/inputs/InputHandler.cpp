#include "../editor/Application.h"
#include "InputHandler.h"
#include "common/maths/Vec.h"

bool InputHandler::IsKeyPressed(int key)
{
	GLFWwindow* window = Application::GetInstance()->GetWindow().GetGLFWWindow();
	int state = glfwGetKey(window, key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

Vivid::Maths::Vec2 InputHandler::GetMousePosition()
{
	GLFWwindow* window = Application::GetInstance()->GetWindow().GetGLFWWindow();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return Vivid::Maths::Vec2((float)xpos, (float)ypos);
}

bool InputHandler::IsMouseButtonPressed(int button)
{
	GLFWwindow* window = Application::GetInstance()->GetWindow().GetGLFWWindow();
	int state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;
}