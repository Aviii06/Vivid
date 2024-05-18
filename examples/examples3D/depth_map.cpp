#include "Vivid.h"

class ExampleInterface : public RenderingInterface
{
private:
	Vivid::Mesh lightMesh;
	Ref<Vivid::Shader> lightShader;
	Ref<Vivid::Entity> plane;
	Ref<Vivid::Entity> light;
	Ref<Vivid::ModelComponent> planeModelComponent;
	Ref<Vivid::TransformComponent> planeTransformComponent;
	Vivid::Mesh* planeMesh;

	Ref<Vivid::DirectionalLightComponent> directionalLightComponent;
	Ref<Vivid::Shader> shader;

public:
	void Setup() override
	{

		Ref<Vivid::Entity> plane = Vivid::ECS::CreateEntity("Plane");
		Ref<Vivid::Entity> light = Vivid::ECS::CreateEntity("DirectionalLight");
		planeModelComponent = Vivid::ECS::CreateComponent<Vivid::ModelComponent>();
		planeTransformComponent = Vivid::ECS::CreateComponent<Vivid::TransformComponent>();
		// Can write custom opengl confs here
		OPENGL_CONFS

		shader = MakeRef<Vivid::Shader>("./../assets/shaders/phong.vertexShader.glsl",
		    "./../assets/shaders/phong.pixelShader.glsl");

		planeMesh = new Vivid::Mesh("./../assets/obj/plane.obj");
		planeMesh->BindShader(shader);

		planeModelComponent->AddMesh(planeMesh);

		directionalLightComponent = Vivid::ECS::CreateComponent<Vivid::DirectionalLightComponent>();
		directionalLightComponent->SetDirection(Vivid::Maths::Vec3(0.0f, -1.0f, 0.0f));

		planeTransformComponent->SetScale(Vivid::Maths::Vec3(50.0f, 50.0f, 50.0f));
		planeTransformComponent->SetRotation(Vivid::Maths::Vec3(90, 0, 0));

		Vivid::ECS::AddComponent(planeModelComponent->GetComponentID(), plane->GetEntityID());
		Vivid::ECS::AddComponent(planeTransformComponent->GetComponentID(), plane->GetEntityID());

		Vivid::ECS::AddComponent(directionalLightComponent->GetComponentID(), light->GetEntityID());

		MovableCamera* cam = static_cast<MovableCamera*>(Application::GetInstance()->GetCamera());
		cam->SetPosition({ 0.0f, 0.0f, 100.0f });
		cam->MoveBackward();

		planeMesh->AddTexture("./../assets/textures/brick_wall/diffuse.jpg");
		planeMesh->AddTexture("./../assets/textures/brick_wall/displacement.jpg");
		planeMesh->AddTexture("./../assets/textures/brick_wall/normal.jpg");
		planeMesh->GetTexture(0)->SetName("DiffuseTexture");
		planeMesh->GetTexture(1)->SetName("DepthMap");
		planeMesh->GetTexture(2)->SetName("NormalMap");
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
