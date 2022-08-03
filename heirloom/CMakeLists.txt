cmake_minimum_required(VERSION 3.21)
project(heirloom)

find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(thirdparty/entt)
#add_subdirectory(thirdparty/glfw)
#add_subdirectory(thirdparty/glm)
#add_subdirectory(thirdparty/spdlog)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_library(heirloom
        include/Heirloom.h
        #        src/hlpch.cpp
        #        src/hlpch.h
        thirdparty/stb_image/stb_image.cpp
        thirdparty/stb_image/stb_image.h
        thirdparty/imgui/imconfig.h
        thirdparty/imgui/imgui.h
        thirdparty/imgui/imgui_internal.h
        thirdparty/imgui/imstb_rectpack.h
        thirdparty/imgui/imstb_textedit.h
        thirdparty/imgui/imstb_truetype.h
        thirdparty/imgui/imgui.cpp
        thirdparty/imgui/imgui_demo.cpp
        thirdparty/imgui/imgui_draw.cpp
        thirdparty/imgui/imgui_tables.cpp
        thirdparty/imgui/imgui_widgets.cpp
        thirdparty/imgui/
        thirdparty/imgui/backends/imgui_impl_glfw.cpp
        thirdparty/imgui/backends/imgui_impl_opengl3.cpp
        thirdparty/glad/src/glad.c
        thirdparty/entt/src/entt/entt.hpp
        src/Heirloom/Core/Log.cpp
        src/Heirloom/Core/Log.h
        src/Heirloom/Profiler/Instrumentation.cpp
        src/Heirloom/Profiler/Instrumentation.h
        src/Heirloom/Core/EntryPoint.h
        src/Heirloom/Core/Application.cpp
        src/Heirloom/Core/Application.h
        src/Heirloom/Core/Core.h
        src/Heirloom/Core/Layer.cpp
        src/Heirloom/Core/Layer.h
        src/Heirloom/Core/Timestep.h
        src/Heirloom/Core/LayerStack.cpp
        src/Heirloom/Core/LayerStack.h
        src/Heirloom/Core/Window.h
        src/Heirloom/Events/ApplicationEventArgs.h
        src/Heirloom/Events/Event.h
        src/Heirloom/ImGui/ImGuiLayer.cpp
        src/Heirloom/ImGui/ImGuiLayer.h
        src/Heirloom/Events/KeyEventArgs.h
        src/Heirloom/Events/MouseEventArgs.h
        src/Heirloom/Core/Input.h
        src/Heirloom/Core/KeyCodes.h
        src/Heirloom/Core/LockFreeStack.h
        src/Heirloom/Core/MouseCodes.h
        src/Heirloom/ImGui/ImGuiBuild.cpp
        src/Heirloom/Renderer/Buffer.cpp
        src/Heirloom/Renderer/Buffer.h
        src/Heirloom/Renderer/FrameBuffer.cpp
        src/Heirloom/Renderer/FrameBuffer.h
        src/Heirloom/Renderer/GraphicsContext.h
        src/Heirloom/Renderer/OrthographicCamera.cpp
        src/Heirloom/Renderer/OrthographicCamera.h
        src/Heirloom/Renderer/OrthographicCameraController.cpp
        src/Heirloom/Renderer/OrthographicCameraController.h
        src/Heirloom/Renderer/RenderCommand.cpp
        src/Heirloom/Renderer/RenderCommand.h
        src/Heirloom/Renderer/Renderer.cpp
        src/Heirloom/Renderer/Renderer.h
        src/Heirloom/Renderer/Renderer2D.cpp
        src/Heirloom/Renderer/Renderer2D.h
        src/Heirloom/Renderer/RendererAPI.cpp
        src/Heirloom/Renderer/RendererAPI.h
        src/Heirloom/Renderer/Shader.cpp
        src/Heirloom/Renderer/Shader.h
        src/Heirloom/Renderer/Sprite.h
        src/Heirloom/Renderer/Texture.cpp
        src/Heirloom/Renderer/Texture.h
        src/Heirloom/Renderer/VertexArray.cpp
        src/Heirloom/Renderer/VertexArray.h
        src/Platform/OpenGL/OpenGLBuffer.cpp
        src/Platform/OpenGL/OpenGLBuffer.h
        src/Platform/OpenGL/OpenGLContext.cpp
        src/Platform/OpenGL/OpenGLContext.h
        src/Platform/OpenGL/OpenGLFrameBuffer.cpp
        src/Platform/OpenGL/OpenGLFrameBuffer.h
        src/Platform/OpenGL/OpenGLRendererAPI.cpp
        src/Platform/OpenGL/OpenGLRendererAPI.h
        src/Platform/OpenGL/OpenGLShader.cpp
        src/Platform/OpenGL/OpenGLShader.h
        src/Platform/OpenGL/OpenGLTexture.cpp
        src/Platform/OpenGL/OpenGLTexture.h
        src/Platform/OpenGL/OpenGLVertexArray.cpp
        src/Platform/OpenGL/OpenGLVertexArray.h
        src/Platform/Windows/WindowsInput.cpp
        src/Platform/Windows/WindowsWindow.cpp
        src/Platform/Windows/WindowsWindow.h
        src/Heirloom/Scene/Scene.cpp
        src/Heirloom/Scene/Scene.h
        src/Heirloom/Scene/Components.h src/Heirloom/Scene/Entity.h)

target_include_directories(heirloom PRIVATE
        src
#        thirdparty/spdlog/include
        thirdparty/stb_image
        thirdparty/glad/include
        thirdparty/imgui
        thirdparty/imgui/backends
        thirdparty/imgui/examples
        thirdparty/entt/src
        )

target_link_libraries(heirloom PRIVATE
        spdlog::spdlog
        glfw
        glm
        EnTT::EnTT
        ${CMAKE_DL_LIBS}
        )

# For some bizarre reason, precompiled headers just refuse to work when using GCC
if (CMAKE_CXX_COMPILER_ID STREQUAL "GCC")
    target_precompile_headers(heirloom PRIVATE src/hlpch.h src/hlpch.cpp)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_compile_definitions(heirloom PRIVATE
            HL_DEBUG
            HL_PROFILE
            IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS
            )
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    target_compile_definitions(heirloom PRIVATE
            IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS
            )
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL RelWithDebInfo)
    target_compile_definitions(heirloom PRIVATE
            HL_DEBUG
            HL_PROFILE
            IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS
            )
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL MinSizeRel)
    target_compile_definitions(heirloom PRIVATE
            IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS
            )
endif ()