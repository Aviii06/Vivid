set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/inputs/InputHandler.cpp
        core/renderer/IndexBuffer.cpp
        core/renderer/Mesh.cpp
        core/renderer/Renderer.cpp
        core/renderer/Shader.cpp
        core/renderer/Texture.cpp
        core/renderer/VertexArray.cpp
        core/renderer/VertexBuffer.cpp
        editor/Camera.cpp
        core/renderer/PointLight.cpp
        core/renderer/shapes/Quad3d.cpp
        core/renderer/shapes/Sphere.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/Window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/Application.cpp
        editor/Camera.cpp
        core/renderer/PointLight.cpp
        core/renderer/shapes/Quad3d.cpp
        core/renderer/shapes/Sphere.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Error.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Timer.cpp
        core/renderer/Renderer2D.cpp
        core/renderer/Renderer3D.cpp
        editor/ui/UI.cpp core/renderer/FrameBuffer.cpp core/components/TransformComponent.cpp)

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/inputs/InputHandler.h
        core/renderer/IndexBuffer.h
        core/renderer/Mesh.h
        core/renderer/Renderer.h
        core/renderer/Shader.h
        core/renderer/shapes/Shape.h
        core/renderer/Texture.h
        core/renderer/VertexArray.h
        core/renderer/VertexBuffer.h
        core/renderer/VertexBufferLayout.h
        editor/Camera.h
        core/renderer/PointLight.h
        core/renderer/shapes/Quad3d.h
        core/renderer/shapes/Sphere.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/Window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/Application.h
        editor/Camera.h
        core/renderer/PointLight.h
        core/renderer/shapes/Quad3d.h
        core/renderer/shapes/Sphere.h
        common/types/SmartPointers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/confs/Config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Error.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Timer.h
        core/renderer/Renderer2D.h
        core/renderer/Renderer3D.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Vivid.h
        confs/DynamicExportingMacros.h editor/RenderingInterface.h editor/EntryPoint.h editor/ui/UIFlags.h editor/ui/UI.h core/renderer/FrameBuffer.h core/components/Component.h core/components/TransformComponent.h common/maths/Vec.h common/types/OpenGLTypes.h common/types/Types.h)

add_library(Vivid SHARED ${SOURCES} ${HEADERS})

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
        )
