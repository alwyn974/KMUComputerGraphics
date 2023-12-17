#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

uniform mat4 MVP;

out vec4 color;

void main() {
    color = inColor;

    gl_Position = MVP * vec4(inPosition, 1.0);
//    gl_Position = vec4(inPosition, 1.0);
}