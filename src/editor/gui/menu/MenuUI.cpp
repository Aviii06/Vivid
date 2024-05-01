#include "MenuUI.h"

namespace VividGUI
{
	void MenuUI::DrawMenuUI()
	{
		ImGui::BeginMainMenuBar();
		drawFileMenu();
		drawEditMenu();
		drawViewMenu();
		drawHelpMenu();
		ImGui::EndMainMenuBar();
	}

	void MenuUI::drawFileMenu()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene"))
			{
			}
			if (ImGui::MenuItem("Open Scene"))
			{
			}
			if (ImGui::MenuItem("Save Scene"))
			{
			}
			if (ImGui::MenuItem("Exit"))
			{
			}
			ImGui::EndMenu();
		}
	}
	void MenuUI::drawEditMenu()
	{
	}
	void MenuUI::drawViewMenu()
	{
	}
	void MenuUI::drawHelpMenu()
	{
	}
}
