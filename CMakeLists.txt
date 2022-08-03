cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(heirloom)

project(Sandbox)

add_executable(Sandbox Sandbox/src/Sandbox2D.cpp Sandbox/src/Sandbox2D.h Sandbox/src/SandboxApp.cpp)

target_include_directories(Sandbox PRIVATE
        heirloom/include
        heirloom/src
        heirloom/thirdparty/spdlog/include
        heirloom/thirdparty/imgui
        heirloom/thirdparty/glm
        heirloom/thirdparty/entt/src
        )

target_link_libraries(Sandbox PRIVATE
        heirloom
        )

add_custom_command(
        TARGET Sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Sandbox/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
)

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_compile_definitions(Sandbox PRIVATE HL_DEBUG HL_PROFILE)
#    target_compile_definitions(Editor PRIVATE HL_DEBUG HL_PROFILE)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    target_compile_definitions(Sandbox PRIVATE)
#    target_compile_definitions(Editor PRIVATE)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL RelWithDebInfo)
    target_compile_definitions(Sandbox PRIVATE HL_DEBUG HL_PROFILE)
#    target_compile_definitions(Editor PRIVATE HL_DEBUG HL_PROFILE)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL MinSizeRel)
    target_compile_definitions(Sandbox PRIVATE)
#    target_compile_definitions(Editor PRIVATE)
endif ()