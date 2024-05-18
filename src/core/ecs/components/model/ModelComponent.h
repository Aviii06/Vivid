#pragma once

#include "core/ecs/Component.h"
#include "common/types/Types.h"
#include "core/ecs/components/model/Mesh.h"
#include "editor/camera/Camera.h"

namespace Vivid
{
	/*!
	 * @class ModelComponent
	 * @brief Contains a ModelComponent.
	 * @details ModelComponent is a class that contains a model component. It is a derived class from Component.
	 * It contains a vector of meshes. These meshes are then rendered in the scene. It also contains a UI for the model component.
	 * From the UI you can add and remove meshes from the model component.
	 */
	class ModelComponent : public Component
	{
	private:
		Vector<Mesh*> m_Meshes;

	public:
		ModelComponent();
		virtual ~ModelComponent() = default;

		void ImGuiRender() override;
		void Draw(Camera* camera) override;

		void AddMesh(Vivid::Mesh* mesh);
		void RemoveMesh(Vivid::Mesh* mesh);

		inline Vector<Vivid::Mesh*> GetMeshes() { return m_Meshes; }
		ComponentType GetComponentType() override { return ComponentType::ModelComponent; }
	};
}
