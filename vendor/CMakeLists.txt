set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(glew-cmake)
add_subdirectory(glm)
add_subdirectory(stb_image)
add_subdirectory(imgui)
add_subdirectory(imguizmo)
add_subdirectory(nativefiledialog-extended)


