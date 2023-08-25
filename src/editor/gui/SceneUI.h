#pragma once
#include "core/ecs/ECS.h"

namespace VividGUI
{
	class SceneUI
	{
	private:
		static Vivid::Entity* m_SelectedEntity;
	public:
		static void DrawSceneUI();
	};
};
