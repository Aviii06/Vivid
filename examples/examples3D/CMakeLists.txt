add_executable(suzanne "suzanne_example.cpp")
add_executable(ecs_test "ecs_test.cpp")
add_executable(instancing "instancing.cpp")
add_executable(bump_map "bump_map.cpp")
if (MSVC)
    set_target_properties(suzanne PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
            "${CMAKE_BINARY_DIR}/")
    set_target_properties(ecs_test PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
            "${CMAKE_BINARY_DIR}/")
    set_target_properties(instancing PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
            "${CMAKE_BINARY_DIR}/")
    set_target_properties(bump_map PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
            "${CMAKE_BINARY_DIR}/")
endif ()

file(COPY ../../assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../assets/)

target_link_libraries(suzanne Vivid)
target_link_libraries(ecs_test Vivid)
target_link_libraries(instancing Vivid)
target_link_libraries(bump_map Vivid)
