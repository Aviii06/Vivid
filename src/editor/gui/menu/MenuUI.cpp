#include "MenuUI.h"
#include "FileMenu.h"

namespace VividGUI
{
	void MenuUI::DrawMenuUI()
	{
		ImGui::BeginMainMenuBar();
		FileMenu::draw();
		ImGui::EndMainMenuBar();
	}
}
