#version 450

layout(location = 0) in vec4 VertexPosition;
layout(location = 1) in vec3 VertexNormal;

out vec3 Position;
out vec3 Normal;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main() {
    Position = vec3(ModelViewMatrix * VertexPosition);
    Normal = NormalMatrix * VertexNormal;

    gl_Position = MVP * VertexPosition;
}