#include "Vivid.h"

class ExampleInterface : public RenderingInterface
{
private:
	Vivid::Mesh lightMesh;
	Ref<Vivid::Shader> lightShader;
	Ref<Vivid::Entity> plane;
	Ref<Vivid::Entity> light;
	Vivid::ModelComponent planeModelComponent;
	Vivid::TransformComponent planeTransformComponent;
	Vivid::Mesh* planeMesh;

	Vivid::DirectionalLightComponent directionalLightComponent;
	Ref<Vivid::Shader> shader;

public:
	void Setup() override
	{

		Vivid::Entity plane = Vivid::ECS::CreateEntity();
		Vivid::Entity light = Vivid::ECS::CreateEntity();
		planeModelComponent = Vivid::ModelComponent();
		planeTransformComponent = Vivid::TransformComponent();
		// Can write custom opengl confs here
		OPENGL_CONFS

		shader = MakeRef<Vivid::Shader>("./../assets/shaders/phong.vertexShader.glsl",
		    "./../assets/shaders/phong.pixelShader.glsl");

		planeMesh = new Vivid::Mesh("./../assets/obj/plane.obj");
		planeMesh->BindShader(shader);

		planeModelComponent.m_meshes.push_back(*planeMesh);

		directionalLightComponent = Vivid::DirectionalLightComponent();
		directionalLightComponent.m_lightDirection = Vivid::Maths::Vec3(0.0f, -1.0f, 0.0f);

		planeTransformComponent.m_scale = Vivid::Maths::Vec3(50.0f, 50.0f, 50.0f);
		planeTransformComponent.m_rotation = Vivid::Maths::Vec3(90, 0, 0);

		Vivid::ECS::AddComponent(plane, planeModelComponent);
		Vivid::ECS::AddComponent(plane, planeTransformComponent);

		Vivid::ECS::AddComponent(light, directionalLightComponent);

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
		Vector<Vivid::DirectionalLightComponent> directionalLights = Vivid::ECS::GetComponents<Vivid::DirectionalLightComponent>();
		Vivid::Maths::Vec3 lightColor = directionalLights[0].m_lightColor;
		float intensity = directionalLights[0].m_intensity;
		Vivid::Maths::Vec3 lightDir = directionalLights[0].m_lightDirection;

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
