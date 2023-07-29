add_executable(Dizzy)

target_include_directories(Dizzy PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/implot/
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glm/
    ${Vulkan_INCLUDE_DIRS}
)

target_precompile_headers(Dizzy PRIVATE dzpch.h)

#Core of Dizzy
target_sources(Dizzy PRIVATE
    Core/Application.h
    Core/Application.cpp
    Core/Logger.h
    Core/DZCore.h
    Core/Logger.cpp
    Core/Layer.h
    Core/Layer.cpp
    Core/LayerStack.h
    Core/LayerStack.cpp
    Core/Window.h
    Core/ImGuiLayer.h
    Core/ImGuiBuild.cpp
    Events/Event.h
    Events/KeyEvent.h
    Events/MouseEvent.h
    Events/AppEvent.h
    Renderer/GraphicsContext.h
    Renderer/RendererAPI.h
    Renderer/RendererAPI.cpp
    Renderer/RenderCommand.h
    Renderer/RenderCommand.cpp
    main.cpp
)

#ImPlot sources
target_sources(Dizzy PRIVATE
    ../vendor/implot/implot.cpp
    ../vendor/implot/implot.h
    ../vendor/implot/implot_demo.cpp
    ../vendor/implot/implot_internal.h
    ../vendor/implot/implot_items.cpp
)

#Packaged dependencies
target_link_libraries(Dizzy PRIVATE imgui glfw glad)

#Link OS graphics implementations and threads and platform implementations
set(THREADS_PREFER_PTHREAD_FLAG On)
find_package(Threads REQUIRED)
if(APPLE)
    #Eventually replace this with metal implementations
    target_sources(Dizzy PRIVATE
        Platform/OpenGL/OpenGLContext.h
        Platform/OpenGL/OpenGLContext.cpp
        Platform/OpenGL/OpenGLAPI.h
        Platform/OpenGL/OpenGLAPI.cpp
        Platform/OpenGL/OpenGLWindow.h
        Platform/OpenGL/OpenGLWindow.cpp
        Platform/OpenGL/ImGuiLayerOGL.h
        Platform/OpenGL/ImGuiLayerOGL.cpp
        Platform/OpenGL/ImGuiBuildOGL.h
    )
    target_link_libraries(Dizzy PRIVATE "-framework Cocoa" "-framework CoreVideo" "-framework IOKit" "-framework OpenGL" "-framework Carbon" ${CMAKE_DL_LIBS} Threads::Threads)
    target_compile_definitions(Dizzy PRIVATE DZ_APPLE)
elseif(UNIX)
    #OpenGL on linux
    target_sources(Dizzy PRIVATE
        Platform/OpenGL/OpenGLContext.h
        Platform/OpenGL/OpenGLContext.cpp
        Platform/OpenGL/OpenGLAPI.h
        Platform/OpenGL/OpenGLAPI.cpp
        Platform/OpenGL/OpenGLWindow.h
        Platform/OpenGL/OpenGLWindow.cpp
        Platform/OpenGL/ImGuiLayerOGL.h
        Platform/OpenGL/ImGuiLayerOGL.cpp
        Platform/OpenGL/ImGuiBuildOGL.h
    )
    target_link_libraries(Dizzy PRIVATE libGL.so libX11.so ${CMAKE_DL_LIBS} Threads::Threads)
    target_compile_definitions(Dizzy PRIVATE DZ_LINUX)
elseif(MSVC)
    #Eh
    target_sources(Dizzy PRIVATE
        Platform/OpenGL/OpenGLContext.h
        Platform/OpenGL/OpenGLContext.cpp
        Platform/OpenGL/OpenGLAPI.h
        Platform/OpenGL/OpenGLAPI.cpp
        Platform/OpenGL/OpenGLWindow.h
        Platform/OpenGL/OpenGLWindow.cpp
        Platform/OpenGL/ImGuiLayerOGL.h
        Platform/OpenGL/ImGuiLayerOGL.cpp
        Platform/OpenGL/ImGuiBuildOGL.h
    )
    target_link_libraries(Dizzy PRIVATE opengl32.lib Threads::Threads)
    target_compile_definitions(Dizzy PRIVATE DZ_WINDOWS)
else()
    target_compile_definitions(Dizzy PRIVATE DZ_UNIDENTIFED_OS)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Dizzy PRIVATE DZ_RELEASE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Dizzy PRIVATE DZ_DEBUG)
endif()

#Some extra defs
target_compile_definitions(Dizzy PRIVATE 
    GLFW_INCLUDE_NONE 
    IMGUI_IMPL_OPENGL_LOADER_GLAD 
)

set_target_properties(Dizzy PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${DZ_BINARY_DIR})