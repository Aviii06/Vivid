#include "editor/gui/UIFlags.h"

namespace VividGUI
{
	class MenuUI
	{
	public:
		static void DrawMenuUI();

	private:
		static void drawFileMenu();
		static void drawEditMenu();
		static void drawViewMenu();
		static void drawHelpMenu();
	};
}