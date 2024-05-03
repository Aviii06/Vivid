#pragma once

#include "core/renderer/Texture.h"

namespace VividGui
{
	class Assets
	{
	private:
		Vivid::Texture* texEdit;
		Vivid::Texture* texMinus;
		Vivid::Texture* texPlus;
		Vivid::Texture* texOpen;
		unsigned int buttonWidth = 10;
		unsigned int buttonHeight = 10;
		static Assets* s_Instance;

		Assets();

	public:
		const Vivid::Texture* GetTexEdit() { return texEdit; }
		const Vivid::Texture* GetTexMinus() { return texMinus; }
		const Vivid::Texture* GetTexPlus() { return texPlus; }
		const Vivid::Texture* GetTexOpen() { return texOpen; }
		unsigned int GetButtonWidth() { return buttonWidth; }
		unsigned int GetButtonHeight() { return buttonHeight; }

		static Assets* GetInstance()
		{
			if (!s_Instance)
				s_Instance = new Assets();
			return s_Instance;
		}
	};
}
