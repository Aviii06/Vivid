#pragma once

#include <iostream>
#include <sstream>

#include "core/renderer/IndexBuffer.h"
#include "core/renderer/Mesh.h"
#include "core/renderer/Renderer.h"
#include "core/renderer/Shader.h"
#include "core/renderer/shapes/Shape.h"
#include "core/renderer/Texture.h"
#include "core/renderer/VertexArray.h"
#include "core/renderer/VertexBuffer.h"
#include "core/renderer/PointLight.h"
#include "core/renderer/shapes/Quad3d.h"
#include "core/renderer/Renderer2D.h"
#include "core/renderer/Renderer3D.h"

#include "editor/Camera.h"
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