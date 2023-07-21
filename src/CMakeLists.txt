add_executable(Dizzy)

target_include_directories(Dizzy PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/implot/
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glm/

)

target_precompile_headers(Dizzy PRIVATE dzpch.h)

target_sources(Dizzy PRIVATE
    Core/Application.h
    Core/Application.cpp
    Core/Logger.h
    Core/DZCore.h
    Core/Logger.cpp
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

#Link OS graphics implementations and threads
set(THREADS_PREFER_PTHREAD_FLAG On)
find_package(Threads REQUIRED)
if(APPLE)
    target_link_libraries(Dizzy PRIVATE "-framework Cocoa" "-framework CoreVideo" "-framework IOKit" "-framework OpenGL" "-framework Carbon" ${CMAKE_DL_LIBS} Threads::Threads)
    target_compile_definitions(Dizzy PRIVATE DZ_APPLE)
elseif(UNIX)
    target_link_libraries(Dizzy PRIVATE libGL.so libX11.so ${CMAKE_DL_LIBS} Threads::Threads)
    target_compile_definitions(Dizzy PRIVATE DZ_LINUX)
elseif(MSVC)
    target_link_libraries(Dizzy PRIVATE opengl32.lib Threads::Threads)
    target_compile_definitions(Dizzy PRIVATE DZ_WINDOWS)
endif()

#Some extra defs
target_compile_definitions(Dizzy PRIVATE 
    GLFW_INCLUDE_NONE 
    IMGUI_IMPL_OPENGL_LOADER_GLAD 
    IMGUI_DEFINE_MATH_OPERATORS
)

set_target_properties(Dizzy PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${DZ_BINARY_DIR})