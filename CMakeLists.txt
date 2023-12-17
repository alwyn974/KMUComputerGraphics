cmake_minimum_required(VERSION 3.22)
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

include_directories(
        include
        lib/gl3w/include
        "${CMAKE_CURRENT_SOURCE_DIR}/src/external/imgui"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/external/imgui/misc/cpp"
)
add_executable(KMU lib/gl3w/gl3w.c
        src/external/imgui/imgui.cpp
        src/external/imgui/imgui_draw.cpp
        src/external/imgui/imgui_tables.cpp
        src/external/imgui/imgui_widgets.cpp
        src/external/imgui/misc/cpp/imgui_stdlib.cpp
        src/external/imgui/imgui_demo.cpp
        src/external/imgui/imgui_impl_glfw.cpp
        src/external/imgui/imgui_impl_opengl3.cpp
        #main.cpp
        opengl.cpp
        src/main/MyGlWindow.cpp
        src/main/Viewer.cpp
        src/main/object/ColorCube.cpp
        src/main/object/CheckeredFloor.cpp
        src/main/Global.cpp
        src/main/object/VBOTeapot.cpp
        src/main/object/VBOTorus.cpp
        src/main/object/Bunny.cpp
        src/main/object/Sphere.cpp
        src/main/MaterialColor.cpp
        src/main/object/Cow.cpp
        src/main/object/BunnyTextured.cpp
        src/main/object/Earth.cpp
        src/main/object/Ogre.cpp
        src/main/Skybox.cpp
        src/main/ParticleSystem.cpp
        include/AbstractDrawable.hpp
)
target_link_libraries(${PROJECT_NAME} glfw glm OpenGL::GL)

# Set the startup project in Visual Studio
if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    message(STATUS "Setting startup project to ${PROJECT_NAME}")
endif (MSVC)
