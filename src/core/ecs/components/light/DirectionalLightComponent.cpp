#include "DirectionalLightComponent.h"
#include "imgui/imgui/imgui.h"
#include "core/renderer/shapes/Quad3d.h"
#include "core/ecs/components/TransformComponent.h"
#include "core/ecs/components/model/ModelComponent.h"
#include "common/maths/Vec.h"

namespace Vivid
{
	DirectionalLightComponent::DirectionalLightComponent(Maths::Vec3 diffuseColor, Maths::Vec3 specularColor, Maths::Vec3 lightColor)
	    : m_DiffuseColor(diffuseColor)
	    , m_SpecularColor(specularColor)
	    , m_LightColor(lightColor)
	{
	}

	void DirectionalLightComponent::Draw(Camera* camera)
	{
		//		Vivid::Quad3d* quad = new Vivid::Quad3d(10, m_Color);
		//		Vivid::ModelComponent* modelComponent = new Vivid::ModelComponent();
		//
		//		if (m_Shader == nullptr)
		//		{
		//			m_Shader = Vivid::Shader::Create("./../assets/shaders/basic.vertexShader.glsl",
		//			    "./../assets/shaders/basic.pixelShader.glsl");
		//		}
		//
		//		m_Mesh = new Vivid::Mesh(*quad);
		//		m_Mesh->BindShader(m_Shader);
		//
		//		modelComponent->AddMesh(m_Mesh);
		//		modelComponent->SetEntity(m_Entity);
		//		modelComponent->Draw(camera);
	}

	void DirectionalLightComponent::ImGuiRender()
	{
		ImGui::SliderFloat("Intensity", &m_Intensity, 0.0f, 10.0f);
		ImGui::SliderFloat3("Direction", &m_Direction.x, -1.0f, 1.0f);
		ImGui::ColorPicker3("Diffuse Color", &m_DiffuseColor.x);
		ImGui::ColorPicker3("Specular Color", &m_SpecularColor.x);
		ImGui::ColorPicker3("Light Color", &m_LightColor.x);
	}
}
