#include "Window.h"
#include "Camera.h"
#include <iostream>
#include "confs/Config.h"
#include "inputs/InputHandler.h"

#include "imgui/imgui/backends/imgui_impl_glfw.h"
#include "imgui/imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui/imgui.h"
#include "core/renderer/Renderer.h"
#include "editor/gui/DockUI.h"

InputHandler* InputHandler::s_Instance;
Camera* Camera::s_Instance;

Window::Window(int width, int height, const char* title)
{
	m_Width = width;
	m_Height = height;
	m_Title = title;
	m_PrevMousePosition = new Vec2(0.0f, 0.0f);

	if (!glfwInit())
	{
		std::cout << "GLFW failed to initialize!" << std::endl;
	}

	// FOR MACOS
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
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

	m_FrameBuffer = new FrameBuffer(m_Width, m_Height);
	m_PickerFrameBuffer = new FrameBuffer(m_Width, m_Height);
}

void Window::Update()
{
	// Handle left click to identify object
	Vec2 mousePosition = InputHandler::GetInstance()->GetMousePosition();
	if (InputHandler::GetInstance()->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
	}

	// Handle Custom Inputs
	if (m_RenderingInterface != nullptr)
	{
		m_RenderingInterface->Input();
	}

	// Handle keyboard input
	glfwPollEvents();

	glfwMakeContextCurrent(m_Window);
	glfwSwapBuffers(m_Window);

	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Vivid::Renderer::Clear();

	// Draw to a temporary framebuffer
	m_FrameBuffer->Bind();
	if (m_RenderingInterface != nullptr)
	{
		m_RenderingInterface->Draw();
	}
	m_FrameBuffer->Unbind();

	// IMGUI
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	VividGUI::InitUI();
	ImGui::Begin("Viewport");
	{
		ImGui::BeginChild("GameRender");

		float width = ImGui::GetContentRegionAvail().x;
		float height = ImGui::GetContentRegionAvail().y;

		Camera::GetInstance()->SetViewportSize(width, height);

		ImGui::Image(
		    (ImTextureID)m_FrameBuffer->getFrameTexture(),
		    ImGui::GetContentRegionAvail(),
		    ImVec2(0, 1),
		    ImVec2(1, 0));
	}
	ImGui::EndChild();
	ImGui::End();

	// Custom ImGui Rendering
	if (m_RenderingInterface != nullptr)
	{
		m_RenderingInterface->ImGuiRender();
	}

	VividGUI::EndUI();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	m_FrameBuffer->Bind();
	Vivid::Renderer::Clear();

	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_FrameBuffer->Unbind();
}
