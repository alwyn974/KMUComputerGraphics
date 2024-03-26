cmake_minimum_required(VERSION 3.8)
project(KMU)

set(CMAKE_CXX_STANDARD 20)

Include(FetchContent)
#FetchContent_Declare(
#        glfw
#        GIT_REPOSITORY https://github.com/glfw/glfw
#        GIT_TAG 3.3.8
#        GIT_SHALLOW 1 # Only fetch the head commit
#)
#FetchContent_MakeAvailable(glfw)
#FetchContent_GetProperties(glfw)
#FetchContent_Declare(
#        glm
#        GIT_REPOSITORY https://github.com/g-truc/glm
#        GIT_TAG 0.9.9.8
#        GIT_SHALLOW 1 # Only fetch the head commit
#)
#FetchContent_MakeAvailable(glm)
#FetchContent_GetProperties(glm)
#FetchContent_Declare(
#        freeglut
#        GIT_REPOSITORY https://github.com/freeglut/freeglut
#        GIT_TAG v3.4.0
#        GIT_SHALLOW 1 # Only fetch the head commit
#)
#FetchContent_MakeAvailable(freeglut)
#FetchContent_GetProperties(freeglut)

find_package(OpenGL REQUIRED)

include_directories(
        include
        libraries/include
        libraries/fltk/include
        libraries/Cyclone/include
        "${CMAKE_CURRENT_SOURCE_DIR}/src/external/imgui"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/external/imgui/misc/cpp"
)
file(GLOB_RECURSE CYCLONE_FILES "libraries/Cyclone/*.cpp" "libraries/Cyclone/*.h")
add_executable(KMU
        ${CYCLONE_FILES}

#        src/external/imgui/imgui.cpp
#        src/external/imgui/imgui_draw.cpp
#        src/external/imgui/imgui_tables.cpp
#        src/external/imgui/imgui_widgets.cpp
#        src/external/imgui/misc/cpp/imgui_stdlib.cpp
#        src/external/imgui/imgui_demo.cpp
#        src/external/imgui/imgui_impl_glfw.cpp
#        src/external/imgui/imgui_impl_opengl3.cpp

        main.cpp
        src/main/3DUtils.cpp
        src/main/DrawUtils.cpp
        src/main/MMatrix.cpp
        src/main/MyGlWindow.cpp
        src/main/object.cpp
        src/main/stdafx.cpp
        src/main/timing.cpp
        src/main/Viewer.cpp
)
target_link_directories(${PROJECT_NAME} PUBLIC libraries/fltk/lib)
target_link_libraries(${PROJECT_NAME}  #[[glm]] opengl32.lib glu32.lib fltk.lib fltk_gl.lib)

# Set the startup project in Visual Studio
if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    message(STATUS "Setting startup project to ${PROJECT_NAME}")

    # Enable Hot Reload for MSVC compilers if supported.
    if (POLICY CMP0141)
        cmake_policy(SET CMP0141 NEW)
        set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
    endif()
endif (MSVC)
