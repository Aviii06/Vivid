#include "PointLightComponent.h"
#include "imgui/imgui/imgui.h"
#include "core/renderer/shapes/Quad3d.h"
#include "core/ecs/components/TransformComponent.h"
#include "core/ecs/components/model/ModelComponent.h"

namespace Vivid
{
	PointLightComponent::PointLightComponent(Vec3 color)
	    : m_Color(color)
	{
	}

	void PointLightComponent::Draw(Camera* camera)
	{
		Vivid::Quad3d* quad = new Vivid::Quad3d(10, m_Color);
		Vivid::ModelComponent* modelComponent = new Vivid::ModelComponent();

		if (m_Shader == nullptr)
		{
			m_Shader = Vivid::Shader::Create("./../assets/shaders/basic.vertexShader.glsl",
			    "./../assets/shaders/basic.pixelShader.glsl");
		}

		m_Mesh = new Vivid::Mesh(*quad);
		m_Mesh->BindShader(m_Shader);

		modelComponent->AddMesh(m_Mesh);
		modelComponent->SetEntity(m_Entity);
		modelComponent->Draw(camera);
	}

	void PointLightComponent::ImGuiRender()
	{
		ImGui::ColorPicker3("Color", &m_Color.x);
		ImGui::SliderFloat("Intensity", &m_Intensity, 0.0f, 10.0f);
	}
}
