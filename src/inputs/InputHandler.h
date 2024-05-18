#pragma once

#include "common/maths/Vec.h"
#include "GLFW/glfw3.h"
#include <map>
#include "editor/camera/movable/EditorCamera.h"
#include "common/maths/Vec.h"

/*!
 @namespace InputHandler
 @brief A namespace that contains functions to handle input.
 @details This namespace contains functions to check if a key is pressed or not, get the mouse position, get the mouse position on the viewport, and check if a mouse button is pressed or not.
*/
namespace InputHandler
{
	/*!
	 @brief Checks if a key is pressed or not.
	 @details Gets an Application singelton and then gets the GLFW window from it and checks if the key is pressed or not.
	 @param key The key to check if it is pressed or not. key is a GLFW key code.
	 @return bool True if key is pressed, false otherwise.
	*/
	bool IsKeyPressed(int key);

	/*!
	 @brief Gets the mouse position.
	 @details Gets an Application singelton and then gets the GLFW window from it and gets the mouse position.
	 @return Vivid::Maths::Vec2 The mouse position.
	*/
	Vivid::Maths::Vec2 GetMousePosition();

	/*!
	 @brief Gets the mouse position on the viewport.
	 @details Gets the mouse position and then subtracts the viewport position from it and then returns the mouse position.
	 @return Vivid::Maths::Vec2 The mouse position on the viewport. Right is positive x, up is positive y.
	*/
	Vivid::Maths::Vec2 GetMousePositionOnViewport();

	/*!
	 @brief Checks if a mouse button is pressed or not.
	 @details Gets an Application singelton and then gets the GLFW window from it and checks if the mouse button is pressed or not.
	 @param button The mouse button to check if it is pressed or not. button is a GLFW mouse button code.
	 @return bool True if mouse button is pressed, false otherwise.
	*/
	bool IsMouseButtonPressed(int button);
};
