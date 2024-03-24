#include "Vivid.h"
#include "common/maths/Vec.h"

const int number_of_sphere = 36;

class ExampleInterface : public RenderingInterface
{
private:
	glm::vec3 suzannePosition = glm::vec3(0, 50, -200);
	glm::vec3 lightPosition = glm::vec3(0, 0, 0);

	Vivid::Mesh lightMesh;
	Ref<Vivid::Shader> lightShader;
	Vivid::Entity* suzanne = new Vivid::Entity(1, "Suzanne");
	Vivid::Entity* light = new Vivid::Entity(2, "DirectionalLight");
	Vivid::ModelComponent* modelComponent1;
	Vivid::TransformComponent* suzanneTransformComponent = new Vivid::TransformComponent();
	Vivid::TransformComponent* lightTransformComponent = new Vivid::TransformComponent();
	Vivid::Mesh* sphere;

	Vivid::PointLightComponent* pointLightComponent;
	Vivid::DirectionalLightComponent* directionalLightComponent;
	Ref<Vivid::Shader> shader;

	std::vector<Vivid::Maths::Vec3> translations;

public:
	void Setup() override
	{
		// Can write custom opengl confs here
		OPENGL_CONFS

		shader = MakeRef<Vivid::Shader>("./../assets/shaders/phong.vertexShader.glsl",
		    "./../assets/shaders/phong.pixelShader.glsl");

		//		sphere = new Vivid::Mesh("./../assets/obj/icoSphereHighpoly.obj");
		//		sphere = new Vivid::Mesh("./../assets/obj/suzanne.obj");
		sphere = new Vivid::Mesh("./../assets/obj/newIcoSphere.obj", number_of_sphere);
		sphere->BindShader(shader);

		modelComponent1 = new Vivid::ModelComponent();
		modelComponent1->AddMesh(sphere);

		pointLightComponent = new Vivid::PointLightComponent();
		pointLightComponent->SetColor(Vivid::Maths::Vec3(1.0f, 0.5f, 1.0f));

		directionalLightComponent = new Vivid::DirectionalLightComponent();
		directionalLightComponent->SetColor(Vivid::Maths::Vec3(1.0f, 0.5f, 1.0f));
		directionalLightComponent->SetDirection(Vivid::Maths::Vec3(0.0f, -1.0f, 0.0f));

		//
		Vivid::ECS::AddComponent(modelComponent1, suzanne);
		Vivid::ECS::AddComponent(lightTransformComponent, suzanne);

		Vivid::ECS::AddComponent(directionalLightComponent, light);

		for (unsigned int i = 0; i < number_of_sphere; i++)
		{
			Vivid::Maths::Vec3 translation;

			// Make a grid of spheres
			translation.x = (float)(i % 6) * 1000.0f;
			translation.y = (float)(i / 6) * 1000.0f;
			translation.z = 0.0f;

			translations.push_back(translation);
		}
		//
		//		for(unsigned int i = 0; i < number_of_sphere; i++)
		//		{
		//			shader->SetUniform3f(("offsets[" + std::to_string(i) + "]"), translations[i]);
		//		}
	}

	void Draw() override
	{
		Vector<Vivid::DirectionalLightComponent*> directionalLights = Vivid::ECS::GetAllComponents<Vivid::DirectionalLightComponent>();
		Vivid::Maths::Vec3 lightColor = directionalLights[0]->GetColor();
		float intensity = directionalLights[0]->GetIntensity();
		Vivid::Maths::Vec3 lightDir = directionalLights[0]->GetDirection();

		sphere->BindShader(shader);
		shader->SetUniform3f("directionalLightColor", lightColor);
		shader->SetUniform1f("directionalLightIntensity", intensity);
		shader->SetUniform3f("directionalLightDir", lightDir);
		for (unsigned int i = 0; i < number_of_sphere; i++)
		{
			shader->SetUniform3f(("offsets[" + std::to_string(i) + "]"), translations[i]);
		}

		// Draw using API
		//		Vivid::Renderer2D::DrawQuad(2013, -200, 100, 100, Vec3(1.0f, 1.0f, 0.0f));
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
	Maths::Vec3 pos = Maths::Vec3(0, 0, 0);
	float rot = 0.0f;
	float zoom = 0.10f;

	Camera* camera = new OrthoCamera(pos, rot, zoom, -1000.0f, 1000.0f);
	Application* app = Application::GetInstance(1920, 1080, "Vivid: ECS TEST Example", camera);

	app->SetRenderingInterface(new ExampleInterface);

	return app;
}

int main()
{
	return Vivid::main(0, nullptr);
}
