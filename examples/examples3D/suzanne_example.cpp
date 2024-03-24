#include "Vivid.h"

class ExampleInterface : public RenderingInterface
{
private:
	Vivid::Maths::Vec3 lightColor = Vivid::Maths::Vec3(1.0f, 0.5f, 1.0f);
	Vivid::Maths::Vec3 lightPos = Vivid::Maths::Vec3(0.0f, 0.0f, -100.0f);
	Vivid::Maths::Vec2* m_PrevMousePosition = new Vivid::Maths::Vec2(0.0f, 0.0f);

	glm::vec3 suzannePosition = glm::vec3(0, 50, -200);
	Vivid::Mesh lightMesh;
	Ref<Vivid::Shader> lightShader;

public:
	void Setup() override
	{
		// Can write custom opengl confs here
		OPENGL_CONFS

		Vivid::Renderer2D::Init();

		// Light Info
		Vivid::Quad3d cube(10.0f, lightColor);
		//		lightMesh = Vivid::Mesh(cube);
		//		light = Vivid::PointLight(lightPos, lightColor, &lightMesh);
		//		lightShader = MakeRef<Vivid::Shader>("./../assets/shaders/basic.vertexShader.glsl",
		//		    "./../assets/shaders/basic.pixelShader.glsl");
		//		light.Draw(lightShader);

		// Creating a shader
		Ref<Vivid::Shader> shader = MakeRef<Vivid::Shader>("./../assets/shaders/phong.vertexShader.glsl",
		    "./../assets/shaders/phong.pixelShader.glsl");

		// Drawing other meshes
		Vivid::Mesh mesh1("./../assets/obj/suzanne.obj");
		mesh1.BindShader(shader);

		mesh1.Update(glm::translate(glm::mat4(1.0f), suzannePosition));
		shader->SetUniform3f("lightColor", lightColor);
		shader->SetUniform3f("lightPos", lightPos);
		shader->SetUniform1f("intensity", 2.0f);

		shader->Bind();
		mesh1.Update(glm::translate(glm::mat4(1.0f), suzannePosition));
		mesh1.Draw(Application::GetInstance()->GetCamera());

		//		light.UpdateLightPosition(lightPos);
		//		light.Draw(lightShader);
	}

	void Draw() override
	{
		Ref<Vivid::Shader> shader = MakeRef<Vivid::Shader>("./../assets/shaders/phong.vertexShader.glsl",
		    "./../assets/shaders/phong.pixelShader.glsl");

		// Drawing other meshes
		Vivid::Mesh mesh1("./../assets/obj/suzanne.obj");
		mesh1.BindShader(shader);

		shader->SetUniform3f("lightColor", lightColor);
		shader->SetUniform3f("lightPos", lightPos);
		shader->SetUniform1f("intensity", 2.0f);

		shader->Bind();
		mesh1.Update(glm::translate(glm::mat4(1.0f), suzannePosition));
		mesh1.Draw(Application::GetInstance()->GetCamera());

		//		light.UpdateLightPosition(lightPos);
		//		light.Draw(lightShader);
	}

	void ImGuiRender() override
	{
		ImGui::Begin("Debug");
		ImGui::SliderFloat3("Translation Model 1", &suzannePosition.x, -500.0f, 500.0f);
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
	return app;
}

int main()
{
	return Vivid::main(0, nullptr);
}
