#include "Assets.h"

namespace VividGui
{
	Assets* Assets::s_Instance = nullptr;

	Assets::Assets()
	{
		texEdit = new Vivid::Texture("./src/editor/assets/edit.png");
		texMinus = new Vivid::Texture("./src/editor/assets/minus.png");
		texPlus = new Vivid::Texture("./src/editor/assets/plus.png");
		texOpen = new Vivid::Texture("./src/editor/assets/open.png");
	}
}