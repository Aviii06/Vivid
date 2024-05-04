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
	Vivid::Entity* light = new Vivid::Entity(2, "DirectionalLight");
	Vivid::ModelComponent* modelComponent1;
	Vivid::TransformComponent* sphereTransformComponent = new Vivid::TransformComponent();
	Vivid::TransformComponent* lightTransformComponent = new Vivid::TransformComponent();
	Vivid::Mesh* mesh;

	Vivid::PointLightComponent* pointLightComponent;
	Vivid::DirectionalLightComponent* directionalLightComponent;
	Ref<Vivid::Shader> shader;

	float shininess = 32.0f;

public:
	void Setup() override
	{
		// Can write custom opengl confs here
		OPENGL_CONFS

		shader = MakeRef<Vivid::Shader>("./../assets/shaders/phong.vertexShader.glsl",
		    "./../assets/shaders/phong.pixelShader.glsl");

		mesh = new Vivid::Mesh("./../assets/obj/suzanne.obj", 1);
		mesh->BindShader(shader);

		modelComponent1 = new Vivid::ModelComponent();
		modelComponent1->AddMesh(mesh);

		pointLightComponent = new Vivid::PointLightComponent();
		pointLightComponent->SetColor(Vivid::Maths::Vec3(1.0f, 0.5f, 1.0f));

		directionalLightComponent = new Vivid::DirectionalLightComponent();
		directionalLightComponent->SetDirection(Vivid::Maths::Vec3(0.0f, -1.0f, 0.0f));
		//

		sphereTransformComponent->SetScale(Vivid::Maths::Vec3(50.0f, 50.0f, 50.0f));
		Vivid::ECS::AddComponent(modelComponent1, suzanne);
		Vivid::ECS::AddComponent(sphereTransformComponent, suzanne);

		Vivid::ECS::AddComponent(directionalLightComponent, light);
	}

	void Draw() override
	{
		Vector<Vivid::DirectionalLightComponent*> directionalLights = Vivid::ECS::GetAllComponents<Vivid::DirectionalLightComponent>();
		Vivid::Maths::Vec3 lightDiffuseColor = directionalLights[0]->GetDiffuseColor();
		Vivid::Maths::Vec3 lightSpecularColor = directionalLights[0]->GetSpecularColor();
		float intensity = directionalLights[0]->GetIntensity();
		Vivid::Maths::Vec3 lightDir = directionalLights[0]->GetDirection();

		//		mesh->BindShader(shader);
		//		shader->Bind();
		//		shader->SetUniform3f("LightDiffuseColor", lightDiffuseColor);
		//		shader->SetUniform3f("LightDir", lightDir);
		//		shader->SetUniform1f("LightIntensity", intensity);
		//		shader->SetUniform3f("LightSpecularColor", lightSpecularColor);
		//		shader->SetUniform3f("LightColor", lightColor);
		//		shader->SetUniform1f("shininess", shininess);
	}

	void ImGuiRender() override
	{
		ImGui::Begin("Debug");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		    1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::SliderFloat("shininess", &shininess, 0.0f, 32.0f);

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
