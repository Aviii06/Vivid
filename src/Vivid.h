#pragma once

#include <iostream>
#include <sstream>

#include "renderer/IndexBuffer.h"
#include "renderer/Mesh.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/shapes/Shape.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "editor/Camera.h"
#include "renderer/PointLight.h"
#include "renderer/shapes/Quad3d.h"
#include "renderer/Renderer2D.h"
#include "renderer/Renderer3D.h"

#include "editor/Window.h"
#include "editor/Application.h"
#include "editor/RenderingInterface.h"
#include "editor/EntryPoint.h"

#include "inputs/InputHandler.h"

#include "confs/Config.h"

#include "inputs/InputHandler.h"

#include "confs/Config.h"

#include "utils/Timer.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm/glm.hpp"

#include "imgui.h"
#include "imgui/imgui/backends/imgui_impl_glfw.h"
#include "imgui/imgui/backends/imgui_impl_opengl3.h"

Application* Application::s_Instance = nullptr;