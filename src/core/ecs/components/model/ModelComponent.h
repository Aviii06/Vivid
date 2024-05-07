#pragma once

#include "core/ecs/Component.h"
#include "common/types/Types.h"
#include "core/ecs/components/model/Mesh.h"
#include "editor/camera/Camera.h"

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

		void Draw(Camera* camera) override;

		void AddMesh(Vivid::Mesh* mesh);

		void RemoveMesh(Vivid::Mesh* mesh);

		inline Vector<Vivid::Mesh*> GetMeshes() { return m_Meshes; }

		String GetComponentName() override { return "Model Component"; }
		ComponentType GetComponentType() override { return ComponentType::ModelComponent; }
	};

}
