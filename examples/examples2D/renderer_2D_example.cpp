#include "Vivid.h"

class ExampleInterface : public RenderingInterface
{
public:
	void Setup() override
	{
		OPENGL_2D_CONFS

		Vivid::Renderer2D::Init();
	}

	void Draw() override
	{
		Vivid::Renderer2D::BeginScene();

		// Draw using API
		Vivid::Renderer2D::DrawCircle(Vivid::Maths::Vec2(0, 0), 150, Vivid::Maths::Vec3(0.0f, 1.0f, 0.0f));

		Vivid::Renderer2D::DrawLine(Vivid::Maths::Vec2(-150, 0), Vivid::Maths::Vec2(150, 0), 2,
		    Vivid::Maths::Vec3(1.0f, 0.5f, 0.0f));

		Vivid::Renderer2D::DrawQuad(-200, -200, 100, 100, Vivid::Maths::Vec3(1.0f, 1.0f, 0.0f));

		Vivid::Renderer2D::EndScene();
	}

	void ImGuiRender() override
	{
		ImGui::Begin("Debug");
		//	ImGui::SliderFloat3("Translation Model 1", &suzannePosition.x, -500.0f, 500.0f);
		//	// ImGui::SliderFloat3("Translation Model 2", &lightPosition.x, -300.0f, 300.0f);
		//	ImGui::SliderFloat3("Light Position", &lightPos.x, -500.0f, 500.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		    1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
	}
};

Application* Vivid::CreateApplication()
{
	Application* app = Application::GetInstance(1920, 1080, "Rendering2D");

	// Important for 2D rendering, set the camera to OrthoCamera
	Maths::Vec3 pos = Maths::Vec3(0, 0, 0);
	float rot = 0.0f;
	float zoom = 0.10f;
	Camera* camera = new OrthoCamera(pos, rot, zoom, -1000.0f, 1000.0f);
	app->SetCamera(camera);

	app->SetRenderingInterface(new ExampleInterface);
	return app;
}

int main()
{
	return Vivid::main(0, nullptr);
}