#pragma once
#include "core/ecs/Component.h"
#include "common/types/Types.h"
#include "core/ecs/components/model/Mesh.h"

namespace Vivid
{
	class ModelComponent : public Component
	{
	private:
		Vector<Vivid::Mesh*> m_Meshes;

	public:
		ModelComponent();
		virtual ~ModelComponent() = default;
		void ImGuiRender() override;
		void Draw() override;

		void AddMesh(Vivid::Mesh* mesh);
		void RemoveMesh(Vivid::Mesh* mesh);
	};

}
