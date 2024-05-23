#pragma once

#include "imgui.h"
#include "imgui/imgui/backends/imgui_impl_glfw.h"
#include "imgui/imgui/backends/imgui_impl_opengl3.h"

/*!
 * @namespace VividGUI
 * @brief VividGUI namespace
 * @details A namespace that contains GUI related helper tools.
*/
namespace VividGUI
{
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

	void ImGuiThemeSetup();
};
