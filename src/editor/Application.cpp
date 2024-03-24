#include "Application.h"
#include "editor/camera/movable/EditorCamera.h"

Window* Window::s_Instance = nullptr;

Application::Application()
{
	m_Window = Window::Init(m_Width, m_Height, m_Title);
}

Application::Application(int width, int height, const char* title, Camera* camera)
    : m_Width(width)
    , m_Height(height)
    , m_Title(std::move(title))
{
	if (title == nullptr)
		m_Title = "Vivid";
	m_Window = Window::Init(m_Width, m_Height, m_Title);
	if (camera != nullptr)
		m_Camera = camera;
	else
		m_Camera = new EditorCamera(60.0f, 1.7778f, 0.1f, 10000.0f);
}

bool Application::IsRunning()
{
	return !glfwWindowShouldClose(m_Window->GetGLFWWindow());
}

void Application::Terminate()
{
	glfwTerminate();
}

void Application::Run()
{
	while (IsRunning())
	{
		m_Window->Update();
	}
}
