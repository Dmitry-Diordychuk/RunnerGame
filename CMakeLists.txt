cmake_minimum_required(VERSION 3.22)

project(42run)

set(SCENE 42run/Scenes/GameScene.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wpedantic")

file(GLOB PROJECT_SOURCES
        42run/Sources/Engine.cpp
        42run/Sources/Window.cpp
        42run/Sources/GlError.cpp
        42run/Sources/GraphicsContext.cpp
        42run/Sources/Event.cpp
        42run/Sources/Time.cpp
        42run/Sources/GameObject.cpp
        42run/Sources/Transform.cpp
        42run/Sources/Model.cpp
        42run/Sources/Texture.cpp
        42run/Sources/RigidBody.cpp
        42run/Sources/Collider.cpp
        42run/Sources/Buffer.cpp
        42run/Sources/VertexArray.cpp
        42run/Sources/Model.cpp
        42run/Sources/Scene.cpp
        42run/Sources/Camera.cpp
        42run/Sources/Renderer.cpp
        42run/Sources/Shader.cpp
        42run/Sources/Font.cpp
        42run/Sources/Text.cpp
)
file(GLOB PROJECT_SHADERS
        42run/Shaders/*.comp
        42run/Shaders/*.frag
        42run/Shaders/*.geom
        42run/Shaders/*.vert)
set(STB_IMAGE_HEADER 42run/Vendor/stb/stb_image.h)


include_directories(
        42run/Headers
        42run/Vendor/stb
)

add_definitions(-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME} ${SCENE} ${PROJECT_SOURCES} ${PROJECT_SHADERS} ${STB_IMAGE_HEADER})

unset(CMAKE_CXX_FLAGS)
remove_definitions(-DGLFW_INCLUDE_NONE)

# Libs
add_subdirectory(42run/Vendor/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(42run/Vendor/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(42run/Vendor/glm)
target_link_libraries(${PROJECT_NAME} glm)

add_subdirectory(42run/Vendor/assimp)
target_link_libraries(${PROJECT_NAME} assimp)
