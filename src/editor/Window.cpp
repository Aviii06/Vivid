#include "Window.h"
#include "editor/camera/movable/EditorCamera.h"
#include "editor/camera/movable/OrthoCamera.h"
#include <iostream>
#include "confs/Config.h"
#include "inputs/InputHandler.h"

#include "imgui/imgui/backends/imgui_impl_glfw.h"
#include "imgui/imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui/imgui.h"
#include "core/renderer/Renderer.h"
#include "editor/gui/DockUI.h"
#include "editor/Application.h"
#include "core/ecs/ECS.h"
#include "gui/SceneUI.h"

#include "imguizmo/ImGuizmo.h"
#include "common/maths/Vec.h"

Window::Window(int width, int height, const char* title)
{
	m_Width = width;
	m_Height = height;
	m_Title = title;
	m_PrevMousePosition = new Vivid::Maths::Vec2(0.0f, 0.0f);

	if (!glfwInit())
	{
		std::cout << "GLFW failed to initialize!" << std::endl;
	}

	// FOR MACOS
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, 1);
	if (!m_Window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_Window);

	IMGUI_CONFS

	IMGUI_CHECKVERSION();
	std::cout << glsl_version << "\n";
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	VividGUI::ImGuiThemeSetup();
}

Window* Window::Init(int width, int height, const char* title)
{
	if (s_Instance == NULL)
		s_Instance = new Window(width, height, title);

	return s_Instance;
}

void Window::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SetRenderingInterface(RenderingInterface* renderingInterface)
{
	m_RenderingInterface = renderingInterface;
	m_RenderingInterface->Setup();

	glfwGetWindowSize(m_Window, &m_Width, &m_Height);
	m_FrameBuffer = new FrameBuffer(m_Width, m_Height);
}

void Window::Update()
{
	glfwGetWindowSize(m_Window, &m_Width, &m_Height);
	m_FrameBuffer->RescaleFrameBuffer(m_Width, m_Height);



	// Handle keyboard input
	glfwPollEvents();

	glfwMakeContextCurrent(m_Window);
	glfwSwapBuffers(m_Window);

	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Vivid::Renderer::Clear();

	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();


	VividGUI::InitUI();

	ImGuizmo::BeginFrame();

	if (ImGui::Begin("Viewport"))
	{
		// Handle Custom Inputs
		Camera* camera = Application::GetInstance()->GetCamera();
		if (ImGui::IsWindowFocused())
		{

			if (m_RenderingInterface != nullptr)
			{
				// If editor camera allow to move.
				if (typeid(*camera) == typeid(EditorCamera) || typeid(*camera) == typeid(OrthoCamera))
				{
					// TODO: Put this in a function
					MovableCamera* movableCamera = static_cast<MovableCamera*>(camera);
					if (InputHandler::IsKeyPressed(GLFW_KEY_W))
					{
						movableCamera->MoveForward();
					}
					if (InputHandler::IsKeyPressed(GLFW_KEY_S))
					{
						movableCamera->MoveBackward();
					}
					if (InputHandler::IsKeyPressed(GLFW_KEY_A))
					{
						movableCamera->MoveLeft();
					}
					if (InputHandler::IsKeyPressed(GLFW_KEY_D))
					{
						movableCamera->MoveRight();
					}

					Vivid::Maths::Vec2 mousePosition = InputHandler::GetMousePosition();
					if (InputHandler::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
					{
						movableCamera->ProcessMouseMovement(mousePosition.x - m_PrevMousePosition->x,
						    mousePosition.y - m_PrevMousePosition->y);
						m_PrevMousePosition->x = mousePosition.x;
						m_PrevMousePosition->y = mousePosition.y;
					}
					else
					{
						m_PrevMousePosition->x = mousePosition.x;
						m_PrevMousePosition->y = mousePosition.y;
					}
				}
			}
		}


		// Draw to a temporary framebuffer
		// Some components might be drawing within imgui context
		m_FrameBuffer->Bind();
		if (m_RenderingInterface != nullptr)
		{
			m_RenderingInterface->Draw();
		}

		Vivid::ECS::Draw(camera);
		m_FrameBuffer->Unbind();

		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;
		// Get the starting position of the viewport
		m_ViewportPosition = Vivid::Maths::Vec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y);

		Application::GetInstance()->GetCamera()->SetViewportSize(m_ViewportWidth, m_ViewportHeight);

		ImGui::Image(
		    (ImTextureID)m_FrameBuffer->getFrameTexture(),
		    ImVec2(m_ViewportWidth, m_ViewportHeight),
		    ImVec2(0, 1),
		    ImVec2(1, 0));

		if (typeid(*camera) == typeid(EditorCamera))
		{
			VividGUI::SceneUI::DrawGizmo(camera);
		}
		ImGui::End();
	}

	// Custom ImGui Rendering
	if (m_RenderingInterface != nullptr)
	{
		m_RenderingInterface->ImGuiRender();
	}

	// Scene "Tree"
	VividGUI::SceneUI::DrawSceneUI();

	// End Docking
	VividGUI::EndUI();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	m_FrameBuffer->Bind();
	Vivid::Renderer::Clear();

	GLCall(glClear(GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
	m_FrameBuffer->Unbind();
}