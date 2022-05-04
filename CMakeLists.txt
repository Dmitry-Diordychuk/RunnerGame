cmake_minimum_required(VERSION 3.0)
project(42run)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(42run/Vendor/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(42run/Vendor/assimp)

option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)


if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(42run/Headers/
        42run/Vendor/assimp/include/
        42run/Vendor/glad/include/
        42run/Vendor/glfw/include/
        42run/Vendor/glm/
        42run/Vendor/stb/)

file(GLOB VENDORS_SOURCES 42run/Vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS 42run/Headers/*.hpp)
file(GLOB PROJECT_SOURCES 42run/Sources/Scene/Triangle.cpp 42run/Sources/*.cpp)
file(GLOB PROJECT_SHADERS 42run/Shaders/*.comp
        42run/Shaders/*.frag
        42run/Shaders/*.geom
        42run/Shaders/*.vert)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES} 42run/Headers/ResourceManager.hpp 42run/Sources/ResourceManager.cpp 42run/Headers/Window.hpp 42run/Sources/Window.cpp 42run/Headers/GraphicsContext.hpp 42run/Sources/GraphicsContext.cpp 42run/Headers/VertexArray.hpp 42run/Headers/Buffer.hpp 42run/Headers/GlError.hpp 42run/Sources/Buffer.cpp 42run/Sources/GlError.cpp 42run/Sources/VertexArray.cpp 42run/Sources/TextureScene.cpp 42run/Sources/Texture.cpp 42run/Sources/3DboxScene.cpp)
target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/42run/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS})
