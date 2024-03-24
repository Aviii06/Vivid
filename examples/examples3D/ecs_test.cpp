#include "Vivid.h"

class ExampleInterface : public RenderingInterface
{
private:
	Vivid::Maths::Vec3 lightColor = Vivid::Maths::Vec3(1.0f, 0.5f, 1.0f);
	Vivid::Maths::Vec3 lightPos = Vivid::Maths::Vec3(0.0f, 0.0f, -100.0f);

	glm::vec3 suzannePosition = glm::vec3(0, 50, -200);
	glm::vec3 lightPosition = glm::vec3(0, 0, 0);

	Vivid::Mesh lightMesh;
	Ref<Vivid::Shader> lightShader;
	Vivid::Entity* suzanne = new Vivid::Entity(1, "Suzanne");
	Vivid::Entity* light = new Vivid::Entity(2, "PointLight");
	Vivid::ModelComponent* modelComponent1;
	Vivid::TransformComponent* suzanneTransformComponent = new Vivid::TransformComponent();
	Vivid::TransformComponent* lightTransformComponent = new Vivid::TransformComponent();
	Vivid::Mesh* mesh;

	Vivid::PointLightComponent* pointLightComponent;
	Ref<Vivid::Shader> shader;

public:
	void Setup() override
	{
		// Can write custom opengl confs here
		OPENGL_CONFS

		shader = MakeRef<Vivid::Shader>("./../assets/shaders/phong.vertexShader.glsl",
		    "./../assets/shaders/phong.pixelShader.glsl");

		mesh = new Vivid::Mesh("./../assets/obj/suzanne.obj");
		mesh->BindShader(shader);

		modelComponent1 = new Vivid::ModelComponent();
		modelComponent1->AddMesh(mesh);

		pointLightComponent = new Vivid::PointLightComponent();
		pointLightComponent->SetColor(Vivid::Maths::Vec3(1.0f, 0.5f, 1.0f));
		//
		Vivid::ECS::AddComponent(modelComponent1, suzanne);
		Vivid::ECS::AddComponent(lightTransformComponent, suzanne);

		Vivid::ECS::AddComponent(pointLightComponent, light);
		Vivid::ECS::AddComponent(suzanneTransformComponent, light);
	}

	void Draw() override
	{
		Vector<Vivid::PointLightComponent*> pointLights = Vivid::ECS::GetAllComponents<Vivid::PointLightComponent>();
		Vivid::Maths::Vec3 lightColor = pointLights[0]->GetColor();
		float intensity = pointLights[0]->GetIntensity();
		Vivid::Maths::Vec3 lightPosition = pointLights[0]->GetEntity()->GetComponent<Vivid::TransformComponent>()->GetPosition();

		mesh->BindShader(shader);
		shader->SetUniform3f("lightColor", lightColor);
		shader->SetUniform3f("lightPos", lightPosition);
		shader->SetUniform1f("intensity", intensity);

		// Draw using API
		Vivid::Renderer2D::DrawQuad(2013, -200, 100, 100, Vivid::Maths::Vec3(1.0f, 1.0f, 0.0f));
	}

	void ImGuiRender() override
	{
		ImGui::Begin("Debug");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		    1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
	}
};

Application* Vivid::CreateApplication()
{
	Application* app = Application::GetInstance(1920, 1080, "Vivid: ECS TEST Example");

	app->SetRenderingInterface(new ExampleInterface);

	return app;
}

int main()
{
	return Vivid::main(0, nullptr);
}
