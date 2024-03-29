set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/inputs/InputHandler.cpp
        core/renderer/IndexBuffer.cpp
        core/ecs/components/model/Mesh.cpp
        core/renderer/Renderer.cpp
        core/renderer/Shader.cpp
        core/renderer/Texture.cpp
        core/renderer/VertexArray.cpp
        core/renderer/VertexBuffer.cpp
        editor/camera/movable/EditorCamera.cpp
        core/ecs/components/light/PointLightComponent.cpp
        core/renderer/shapes/Quad3d.cpp
        core/renderer/shapes/Sphere.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/Window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/Application.cpp
        editor/camera/movable/EditorCamera.cpp
        core/ecs/components/light/PointLightComponent.cpp
        core/renderer/shapes/Quad3d.cpp
        core/renderer/shapes/Sphere.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Error.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Timer.cpp
        core/renderer/Renderer2D.cpp
        core/renderer/Renderer3D.cpp
        editor/gui/DockUI.cpp core/renderer/FrameBuffer.cpp core/ecs/components/TransformComponent.cpp core/ecs/Entity.cpp core/ecs/components/model/ModelComponent.cpp editor/camera/movable/OrthoCamera.cpp core/ecs/ECS.cpp editor/gui/SceneUI.cpp editor/gui/UIFlags.cpp)

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/inputs/InputHandler.h
        core/renderer/IndexBuffer.h
        core/ecs/components/model/Mesh.h
        core/renderer/Renderer.h
        core/renderer/Shader.h
        core/renderer/shapes/Shape.h
        core/renderer/Texture.h
        core/renderer/VertexArray.h
        core/renderer/VertexBuffer.h
        core/renderer/VertexBufferLayout.h
        editor/camera/movable/EditorCamera.h
        core/ecs/components/light/PointLightComponent.h
        core/renderer/shapes/Quad3d.h
        core/renderer/shapes/Sphere.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/Window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/Application.h
        editor/camera/movable/EditorCamera.h
        core/ecs/components/light/PointLightComponent.h
        core/renderer/shapes/Quad3d.h
        core/renderer/shapes/Sphere.h
        common/types/SmartPointers.h
        common/maths/Vec.h
        common/maths/VectorHelper.h
        ${CMAKE_CURRENT_SOURCE_DIR}/confs/Config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Error.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Timer.h
        core/renderer/Renderer2D.h
        core/renderer/Renderer3D.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Vivid.h
        confs/DynamicExportingMacros.h editor/RenderingInterface.h editor/EntryPoint.h editor/gui/UIFlags.h editor/gui/DockUI.h core/renderer/FrameBuffer.h core/ecs/Component.h core/ecs/components/TransformComponent.h common/maths/Vec.h common/types/OpenGLTypes.h common/types/Types.h core/ecs/Entity.h core/ecs/components/model/ModelComponent.h editor/camera/movable/OrthoCamera.h core/ecs/ECS.h editor/gui/SceneUI.h core/ecs/components/light/DirectionalLightComponent.cpp core/ecs/components/light/DirectionalLightComponent.h editor/camera/movable/MovableCamera.h common/maths/VectorHelper.h)

add_library(Vivid STATIC ${SOURCES} ${HEADERS})

target_include_directories(Vivid PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        )

target_include_directories(Vivid PUBLIC
        ${PROJECT_SOURCE_DIR}/vendor
        )

target_link_libraries(Vivid
        glfw
        libglew_static
        glm
        imgui
        stb
        glad
        imguizmo
        )
