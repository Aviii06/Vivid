#pragma once

#include "common/types/OpenGLTypes.h"
#include "common/types/SmartPointers.h"
#include "Window.h"
#include <iostream>
#include "confs/DynamicExportingMacros.h"
#include "editor/RenderingInterface.h"
#include "editor/camera/Camera.h"

#include "inputs/InputHandler.h"

/*!
 * @class Application
 * @brief Application class
 * @details A class that contains functions to create an application, run the application, get the window, get the camera, get the title, set the camera, terminate the application, and set the rendering interface.
*/
class VIVAPI Application
{
private:
	static Application* s_Instance;
	int m_Width, m_Height;
	const char* m_Title;

	Application();

	Application(int width, int height, const char* title, Camera* camera = nullptr);

	Window* m_Window;
	Camera* m_Camera;

public:
	bool IsRunning();

	void Run();

	// TODO: Fix this semantically
	static Application*
	GetInstance(int width = 1920, int height = 1080, const char* title = "Vivid", Camera* camera = nullptr)
	{
		if (s_Instance == NULL)
			s_Instance = new Application(width, height, title, camera);
		return s_Instance;
	}

	Window& GetWindow() { return *m_Window; }

	Camera* GetCamera() { return m_Camera; }

	char* GetTitle() { return (char*)m_Title; }

	void SetCamera(Camera* camera) { m_Camera = camera; }

	void Terminate();

	void SetRenderingInterface(RenderingInterface* renderingInterface)
	{
		m_Window->SetRenderingInterface(renderingInterface);
	}
};

namespace Vivid
{
	Application* CreateApplication();
}
