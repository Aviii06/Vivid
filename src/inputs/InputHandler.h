#pragma once

#include "common/maths/Vec.h"
#include "GLFW/glfw3.h"
#include <map>
#include "editor/camera/movable/EditorCamera.h"
#include "common/maths/Vec.h"

// Create a class on top of GLFW input handling
namespace InputHandler
{
	bool IsKeyPressed(int key);

	Vivid::Maths::Vec2 GetMousePosition();
	Vivid::Maths::Vec2 GetMousePositionOnViewport();

	bool IsMouseButtonPressed(int button);
};
