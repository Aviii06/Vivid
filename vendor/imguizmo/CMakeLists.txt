file(GLOB_RECURSE imguizmo ./**.cpp)
file(GLOB_RECURSE imguizmoH ./**.h)

set(ROOTEX_INCLUDES
        ${ROOTEX_INCLUDES}
        ${CMAKE_CURRENT_LIST_DIR}
        CACHE INTERNAL "")

add_library(imguizmo STATIC ${imguizmo} ${imguizmoH})
set_property(TARGET imguizmo PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
set_target_properties(imguizmo PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(imguizmo PUBLIC
        ./
        ../ImGui/
        )