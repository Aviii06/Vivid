#include "Vivid.h"

class ExampleInterface : public RenderingInterface
{
private:
	Vec3 lightColor = Vec3(1.0f, 0.5f, 1.0f);
	Vec3 lightPos = Vec3(0.0f, 0.0f, -100.0f);

	glm::vec3 translationModel1 = glm::vec3(0, 50, -200);
	glm::vec3 translationModel2 = glm::vec3(0, 50, -200);
	Vivid::Mesh lightMesh;
	Ref<Vivid::Shader> lightShader;
	Vivid::Entity* entity1 = new Vivid::Entity(1, "entity1");
	Vivid::Entity* entity2 = new Vivid::Entity(2, "entity2");
	Vivid::ModelComponent* modelComponent1;
	Vivid::ModelComponent* modelComponent2;
	Vivid::TransformComponent* transformComponent = new Vivid::TransformComponent();
	Vivid::Mesh* mesh1;
	Vivid::Mesh* mesh2;

	Vivid::PointLightComponent* pointLightComponent;

public:
	void Setup() override
	{
		// Can write custom opengl confs here
		OPENGL_CONFS

		// Creating a shader

		// Drawing other meshes

		Ref<Vivid::Shader> shader = MakeRef<Vivid::Shader>("./../assets/shaders/phong.vertexShader.glsl",
		    "./../assets/shaders/phong.pixelShader.glsl");

		mesh1 = new Vivid::Mesh("./../assets/obj/suzanne.obj");
		mesh1->BindShader(shader);

		mesh2 = new Vivid::Mesh("./../assets/obj/cube.obj");
		mesh2->BindShader(shader);

		modelComponent1 = new Vivid::ModelComponent();
		modelComponent1->AddMesh(mesh1);

		modelComponent2 = new Vivid::ModelComponent();
		modelComponent2->AddMesh(mesh2);

		//		entity1.AddComponent(modelComponent1);

		pointLightComponent = new Vivid::PointLightComponent();

		Vivid::ECS::AddComponent(modelComponent1, entity1);
		Vivid::ECS::AddComponent(modelComponent2, entity2);
		Vivid::ECS::AddComponent(pointLightComponent, entity2);

		Vivid::ECS::AddComponent(transformComponent, entity2);
	}

	void Draw() override
	{
		mesh1->Update(glm::translate(glm::mat4(1.0f), translationModel1));
		mesh2->Update(glm::translate(glm::mat4(1.0f), translationModel2));

		Ref<Vivid::Shader> shader = MakeRef<Vivid::Shader>("./../assets/shaders/phong.vertexShader.glsl",
		    "./../assets/shaders/phong.pixelShader.glsl");

		Vector<Vivid::PointLightComponent*> pointLights = Vivid::ECS::GetAllComponents<Vivid::PointLightComponent>();
		Vec3 lightColor = pointLights[0]->GetColor();
		Vivid::Entity* lightEntity = pointLights[0]->GetEntity();
		Vector<Vivid::Component*> LightComponents = lightEntity->GetAllComponents();
		Vec3 lightPosition = lightEntity->GetComponent<Vivid::TransformComponent>()->GetPosition();
		Vivid::ModelComponent* modelComponent;

		shader->SetUniform3f("lightColor", lightColor);
		shader->SetUniform3f("lightPos", lightPosition);
		shader->SetUniform1f("intensity", 2.0f);
		mesh1->BindShader(shader);
	}

	void ImGuiRender() override
	{

		translationModel2 = glm::vec3(transformComponent->GetPosition().x, transformComponent->GetPosition().y, transformComponent->GetPosition().z);
		ImGui::Begin("Debug");
		ImGui::SliderFloat3("Translation Model 1", &translationModel1.x, -500.0f, 500.0f);
		ImGui::SliderFloat3("Translation Model 2", &translationModel2.x, -500.0f, 500.0f);
		ImGui::SliderFloat3("Light Position", &lightPos.x, -500.0f, 500.0f);

		transformComponent->SetPosition(Vec3(translationModel2.x, translationModel2.y, translationModel2.z));

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
