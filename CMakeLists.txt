cmake_minimum_required(VERSION 3.26)
project(KMU)

set(CMAKE_CXX_STANDARD 20)

Include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.3.8
        GIT_SHALLOW 1 # Only fetch the head commit
)
FetchContent_MakeAvailable(glfw)
FetchContent_GetProperties(glfw)
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG 0.9.9.8
        GIT_SHALLOW 1 # Only fetch the head commit
)
FetchContent_MakeAvailable(glm)
FetchContent_GetProperties(glm)

find_package(OpenGL REQUIRED)

include_directories(include lib/gl3w/include)
add_executable(KMU lib/gl3w/gl3w.c
        #main.cpp
        opengl.cpp
        src/main/MyGlWindow.cpp
        src/main/Viewer.cpp
        src/main/ColorCube.cpp
        src/main/CheckeredFloor.cpp
        src/main/Global.cpp
        src/main/VBOTeapot.cpp
        src/main/VBOTorus.cpp
)
target_link_libraries(${PROJECT_NAME} glfw glm OpenGL::GL)
