#pragma once

#include "common/types/OpenGLTypes.h"
#include "utils/Error.h"
#include "core/renderer/FrameBuffer.h"
#include "editor/RenderingInterface.h"
#include "common/maths/Vec.h"

class Window
{
private:
	GLFWwindow* m_Window;
	Vivid::Maths::Vec2 m_ViewportPosition;
	int m_Width, m_Height;
	float m_ViewportWidth, m_ViewportHeight;
	const char* m_Title;
	Vivid::Maths::Vec2* m_PrevMousePosition;
	RenderingInterface* m_RenderingInterface;
	FrameBuffer* m_FrameBuffer;

	Window(int width, int height, const char* title);

	static Window* s_Instance;

public:
	~Window() = default;

	static Window* Init(int width, int height, const char* title);

	void Clear() const;

	void Update();

	int GetWidth() const { return m_Width; }

	int GetHeight() const { return m_Height; }

	GLFWwindow* GetGLFWWindow() const { return m_Window; }

	float GetAspectRatio() const { return (float)m_Width / (float)m_Height; }

	void SetRenderingInterface(RenderingInterface* renderingInterface);

	Vivid::Maths::Vec2 GetViewportPosition() { return m_ViewportPosition; }
	float GetViewportWidth() { return m_ViewportWidth; }
	float GetViewportHeight() { return m_ViewportHeight; }
};