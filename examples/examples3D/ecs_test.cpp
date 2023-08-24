#include "Vivid.h"

class ExampleInterface : public RenderingInterface
{
private:
	Vec3 lightColor = Vec3(1.0f, 0.5f, 1.0f);
	Vec3 lightPos = Vec3(0.0f, 0.0f, -100.0f);

	glm::vec3 translationModel1 = glm::vec3(0, 50, -200);
	Vivid::Mesh lightMesh;
	Ref<Vivid::Shader> lightShader;
	Vivid::Entity entity1;
	Vivid::ModelComponent* modelComponent1;
	Vivid::Mesh* mesh1;

public:
	void Setup() override
	{
		// Can write custom opengl confs here
		OPENGL_CONFS

		// Creating a shader
		Ref<Vivid::Shader> shader = MakeRef<Vivid::Shader>("./../assets/shaders/basic.vertexShader.glsl",
		    "./../assets/shaders/basic.pixelShader.glsl");

		// Drawing other meshes
		mesh1 = new Vivid::Mesh("./../assets/obj/suzanne.obj");
		mesh1->BindShader(shader);

		modelComponent1 = new Vivid::ModelComponent();
		modelComponent1->AddMesh(mesh1);
		entity1.AddComponent(modelComponent1);
	}

	void Draw() override
	{
		Ref<Vivid::Shader> shader = MakeRef<Vivid::Shader>("./../assets/shaders/basic.vertexShader.glsl",
		    "./../assets/shaders/basic.pixelShader.glsl");

		// Drawing other meshes
		mesh1->BindShader(shader);

		shader->Bind();
		mesh1->Update(glm::translate(glm::mat4(1.0f), translationModel1));
		entity1.Draw();
	}

	void ImGuiRender() override
	{
		ImGui::Begin("Debug");
		ImGui::SliderFloat3("Translation Model 1", &translationModel1.x, -500.0f, 500.0f);
		ImGui::SliderFloat3("Light Position", &lightPos.x, -500.0f, 500.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		    1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
	}
};

Application* Vivid::CreateApplication()
{
	Application* app = Application::GetInstance(1920, 1080, "Vivid: Suzanne Example");

	app->SetRenderingInterface(new ExampleInterface);

	//	OrthoCamera* orthoCamera = new OrthoCamera(0 ,1920, 0, 1080);
	//	app->SetCamera(orthoCamera);
	return app;
}

int main()
{
	return Vivid::main(0, nullptr);
}
