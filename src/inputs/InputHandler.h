#pragma once

#include "common/maths/Vec.h"
#include "GLFW/glfw3.h"
#include <map>
#include "editor/camera/EditorCamera.h"

// Create a class on top of GLFW input handling
namespace InputHandler
{
	bool IsKeyPressed(int key);
	Vec2 GetMousePosition();
	bool IsMouseButtonPressed(int button);
};
