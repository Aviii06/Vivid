set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/inputs/InputHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/Window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/Application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Error.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Timer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/IndexBuffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/components/model/Mesh.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/Renderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/Shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/Texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/VertexArray.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/VertexBuffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/camera/movable/EditorCamera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/components/light/PointLightComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/shapes/Quad3d.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/shapes/Sphere.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/camera/movable/EditorCamera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/components/light/PointLightComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/shapes/Quad3d.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/shapes/Sphere.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/Renderer2D.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/Renderer3D.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/components/light/DirectionalLightComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/gui/DockUI.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/FrameBuffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/components/TransformComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/Entity.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/components/model/ModelComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/camera/movable/OrthoCamera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/ECS.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/gui/SceneUI.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/gui/UIFlags.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/os/FileDialogue.cpp editor/gui/menu/MenuUI.cpp editor/gui/menu/FileMenu.cpp editor/assets/Assets.cpp)

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/inputs/InputHandler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/IndexBuffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/components/model/Mesh.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/Renderer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/Shader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/shapes/Shape.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/Texture.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/VertexArray.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/VertexBuffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/VertexBufferLayout.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/camera/movable/EditorCamera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/components/light/PointLightComponent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/shapes/Quad3d.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/shapes/Sphere.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/Window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/Application.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/camera/movable/EditorCamera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/camera/movable/OrthoCamera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/components/light/PointLightComponent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/shapes/Quad3d.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/shapes/Sphere.h
        ${CMAKE_CURRENT_SOURCE_DIR}/common/types/SmartPointers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/common/maths/Vec.h
        ${CMAKE_CURRENT_SOURCE_DIR}/common/maths/VectorHelper.h
        ${CMAKE_CURRENT_SOURCE_DIR}/confs/Config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Error.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Timer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/Renderer2D.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/Renderer3D.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Vivid.h
        ${CMAKE_CURRENT_SOURCE_DIR}/confs/DynamicExportingMacros.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/RenderingInterface.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/EntryPoint.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/gui/UIFlags.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/gui/DockUI.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer/FrameBuffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/Component.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/components/TransformComponent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/common/maths/Vec.h
        ${CMAKE_CURRENT_SOURCE_DIR}/common/types/OpenGLTypes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/common/types/Types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/Entity.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/components/model/ModelComponent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/camera/movable/OrthoCamera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/ECS.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/gui/SceneUI.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/ecs/components/light/DirectionalLightComponent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/camera/movable/MovableCamera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/common/maths/VectorHelper.h
        ${CMAKE_CURRENT_SOURCE_DIR}/core/os/FileDialogue.h editor/gui/menu/MenuUI.h editor/gui/menu/FileMenu.h editor/assets/Assets.h common/errors/OpenGLErrors.h)

add_library(Vivid STATIC ${SOURCES} ${HEADERS})

target_include_directories(Vivid PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        )

target_include_directories(Vivid PUBLIC
        ${PROJECT_SOURCE_DIR}/vendor
        )

file(COPY editor/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/editor/assets/)

target_link_libraries(Vivid
        glfw
        libglew_static
        glm
        imgui
        stb
        glad
        imguizmo
        nfd
        )
