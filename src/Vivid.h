#pragma once

#include <iostream>
#include <sstream>

#include "core/ecs/components/model/Mesh.h"
#include "core/ecs/components/model/ModelComponent.h"
#include "core/ecs/components/TransformComponent.h"
#include "core/ecs/components/light/DirectionalLightComponent.h"
#include "core/ecs/components/light/PointLightComponent.h"
#include "core/ecs/Entity.h"
#include "core/ecs/Component.h"
#include "core/ecs/ECS.h"

#include "core/renderer/IndexBuffer.h"
#include "core/renderer/Renderer.h"
#include "core/renderer/Shader.h"
#include "core/renderer/shapes/Shape.h"
#include "core/renderer/Texture.h"
#include "core/renderer/VertexArray.h"
#include "core/renderer/VertexBuffer.h"
#include "core/renderer/shapes/Quad3d.h"
#include "core/renderer/Renderer2D.h"
#include "core/renderer/Renderer3D.h"

#include "editor/camera/Camera.h"
#include "editor/camera/movable/EditorCamera.h"
#include "editor/camera/movable/OrthoCamera.h"
#include "editor/Window.h"
#include "editor/Application.h"
#include "editor/RenderingInterface.h"
#include "editor/EntryPoint.h"

#include "inputs/InputHandler.h"

#include "confs/Config.h"

#include "utils/Timer.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm/glm.hpp"

#include "imgui.h"
#include "imgui/imgui/backends/imgui_impl_glfw.h"
#include "imgui/imgui/backends/imgui_impl_opengl3.h"

Application* Application::s_Instance = nullptr;
