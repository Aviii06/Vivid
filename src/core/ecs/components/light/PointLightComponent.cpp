#include "PointLightComponent.h"
#include "imgui/imgui/imgui.h"
#include "core/renderer/shapes/Quad3d.h"
#include "core/ecs/components/TransformComponent.h"
#include "core/ecs/components/model/ModelComponent.h"
#include "core/ecs/ECS.h"
#include "common/maths/Vec.h"

namespace Vivid
{
	PointLightComponent::PointLightComponent(Maths::Vec3 color)
	    : m_Color(color)
	{
	}

	void PointLightComponent::Draw(Camera* camera)
	{
		auto component = ECS::GetComponent(ComponentType::TransformComponent, m_OwnerEntityID);

		float scale = dynamic_cast<TransformComponent*>(component.get())->GetScale().x;
		Quad3d* quad = new Vivid::Quad3d(10.0f / scale, m_Color);
		ModelComponent* modelComponent = new Vivid::ModelComponent();

		if (m_Shader == nullptr)
		{
			m_Shader = Vivid::Shader::Create("./../assets/shaders/basic.vertexShader.glsl",
			    "./../assets/shaders/basic.pixelShader.glsl");
		}

		m_Mesh = new Vivid::Mesh(*quad);
		m_Mesh->BindShader(m_Shader);

		modelComponent->AddMesh(m_Mesh);
		modelComponent->SetEntity(m_OwnerEntityID);
		modelComponent->Draw(camera);
	}

	void PointLightComponent::ImGuiRender()
	{
		ImGui::ColorPicker3("Color", &m_Color.x);
		ImGui::SliderFloat("Intensity", &m_Intensity, 0.0f, 10.0f);
	}
}
