cmake_minimum_required(VERSION 3.16)
project(SnakeOpenGL)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-DGLEW_STATIC)

add_executable(SnakeOpenGL src/main.cpp src/model/Level.cpp src/model/Level.h
        src/controller/Coordinates.cpp src/controller/Coordinates.h
        src/controller/Inputs.cpp src/controller/Inputs.h
        src/view/IndexBuffer.cpp src/view/IndexBuffer.h
        src/view/VertexBuffer.cpp src/view/VertexBuffer.h
        src/view/Renderer.cpp src/view/Renderer.h
        src/view/VertexArray.cpp src/view/VertexArray.h
        src/view/Shader.cpp src/view/Shader.h src/model/Snake.cpp src/model/Snake.h src/view/ErrorCatcher.h)

include_directories(Dependencies/GLFW/include)
include_directories(Dependencies/GLEW/include)

target_include_directories(SnakeOpenGL PRIVATE ${GLFW_LIBRARIES})
target_include_directories(SnakeOpenGL PRIVATE ${GLEW_LIBRARIES})

target_link_libraries(SnakeOpenGL ${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib/libglfw3.a opengl32)
target_link_libraries(SnakeOpenGL ${PROJECT_SOURCE_DIR}/Dependencies/GLEW/lib/glew32s.lib glu32 opengl32)