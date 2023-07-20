add_executable(Dizzy)

target_include_directories(Dizzy PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/implot/
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glm/

)