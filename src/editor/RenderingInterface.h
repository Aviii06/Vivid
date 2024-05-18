#pragma once

#include "confs/DynamicExportingMacros.h"

/*!
 * @class RenderingInterface
 * @brief RenderingInterface class
 * @details A class that contains functions to setup, draw, and render ImGui. This can be used by a user to render their own things. User needs to crete a class that inherits from this class and implement the functions. All the different functions can share variables having member variables in the class, or gloabl variables.
*/
class VIVAPI RenderingInterface
{
public:
	/*!
	 * @brief Setup function
	 * @details A pure virtual function that needs to be implemented by the user. This function is called once before the first frame. You need to do all the OpenGl setup here.
	*/
	virtual void Setup() = 0;

	/*!
	 * @brief Draw function
	 * @details A pure virtual function that needs to be implemented by the user. This function is called every frame.
	*/
	virtual void Draw() = 0;

	/*!
	 * @brief ImGuiRender function
	 * @details A pure virtual function that needs to be implemented by the user. This function is called every frame.
	*/
	virtual void ImGuiRender() = 0;
};
