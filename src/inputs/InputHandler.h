#pragma once

#include "common/maths/Vec.h"
#include "GLFW/glfw3.h"
#include <map>
#include "editor/Camera.h"

// Create a class on top of GLFW input handling
class InputHandler
{
private:
	static InputHandler* s_Instance;
	InputHandler() = default;

public:
	static InputHandler* GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new InputHandler();
		}
		return s_Instance;
	}

	bool IsKeyPressed(int key);
	Vec2 GetMousePosition();
	bool IsMouseButtonPressed(int button);
	Camera* GetCamera();
};
