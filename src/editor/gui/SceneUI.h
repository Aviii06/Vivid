#pragma once

#include "core/ecs/ECS.h"

namespace VividGUI
{
	/*!
	 * @brief SceneUI class
	 * @details A class that contains the SceneUI. Scene contains all the entities and have a spacial entity called m_SelectedEntity. The selectedEntity Generates a gizmo that can be used to move the entity, and an Inspector that can be used to change the properties of the entity and showcase it's components.
	 */
	class SceneUI
	{
	private:
		static Vivid::Entity* m_SelectedEntity;

	public:
		static void DrawSceneUI();

		static void DrawGizmo(Camera* camera);
	};
};
