#include "FileMenu.h"

namespace VividGUI
{
	void FileMenu::draw()
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
}
