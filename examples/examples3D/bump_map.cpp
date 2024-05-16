#include "Vivid.h"

class ExampleInterface : public RenderingInterface
{
private:
	Vivid::Mesh lightMesh;
	Ref<Vivid::Shader> lightShader;
	Vivid::Entity* plane = Vivid::ECS::CreateEntity("plane");
	Vivid::Entity* light = Vivid::ECS::CreateEntity("DirectionalLight");
	Ref<Vivid::ModelComponent> planeModelComponent;
	Ref<Vivid::TransformComponent> planeTransformComponent = MakeRef<Vivid::TransformComponent>();
	Vivid::Mesh* planeMesh;

	Ref<Vivid::DirectionalLightComponent> directionalLightComponent;
	Ref<Vivid::Shader> shader;

public:
	void Setup() override
	{
		// Can write custom opengl confs here
		OPENGL_CONFS

		shader = MakeRef<Vivid::Shader>("./../assets/shaders/phong.vertexShader.glsl",
		    "./../assets/shaders/phong.pixelShader.glsl");

		planeMesh = new Vivid::Mesh("./../assets/obj/plane.obj");
		planeMesh->BindShader(shader);

		planeModelComponent = MakeRef<Vivid::ModelComponent>();
		planeModelComponent->AddMesh(planeMesh);

		directionalLightComponent = MakeRef<Vivid::DirectionalLightComponent>();
		directionalLightComponent->SetDirection(Vivid::Maths::Vec3(0.0f, -1.0f, 0.0f));

		planeTransformComponent->SetScale(Vivid::Maths::Vec3(50.0f, 50.0f, 50.0f));
		planeTransformComponent->SetRotation(Vivid::Maths::Vec3(90, 0, 0));

		Vivid::ECS::AddComponent(planeModelComponent, plane);
		Vivid::ECS::AddComponent(planeTransformComponent, plane);

		Vivid::ECS::AddComponent(directionalLightComponent, light);

		MovableCamera* cam = static_cast<MovableCamera*>(Application::GetInstance()->GetCamera());
		cam->SetPosition({ 0.0f, 0.0f, 100.0f });
		cam->MoveBackward();

		planeMesh->AddTexture("./../assets/textures/HighResBrickWall/brickwall.jpg");
		planeMesh->AddTexture("./../assets/textures/HighResBrickWall/normal_mapping_normal_map.png");
		planeMesh->GetTexture(0)->SetName("DiffuseTexture");
		planeMesh->GetTexture(1)->SetName("NormalMap");
	}

	void Draw() override
	{
		Vector<Vivid::DirectionalLightComponent*> directionalLights;
		Vivid::ECS::GetAllComponents(Vivid::ComponentType::DirectionalLightComponent, directionalLights);
		Vivid::Maths::Vec3 lightColor = directionalLights[0]->GetLightColor();
		float intensity = directionalLights[0]->GetIntensity();
		Vivid::Maths::Vec3 lightDir = directionalLights[0]->GetDirection();

		planeMesh->BindShader(shader);
		shader->Bind();
		shader->SetUniform3f("LightDir", lightDir);
		shader->SetUniform1f("LightIntensity", intensity);
		shader->SetUniform3f("LightColor", lightColor);
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
	Application* app = Application::GetInstance(1920, 1080, "Vivid: Bump Map Example");

	app->SetRenderingInterface(new ExampleInterface);

	return app;
}

int main()
{
	return Vivid::main(0, nullptr);
}
