#version 450

layout (location = 0) in vec4 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexCoord;
layout (location = 3) in vec3 vertexTangent;
layout (location = 4) in vec3 vertexBitTangent;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;
out mat3x3 TangentMatrix;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main() {
    TexCoord = VertexTexCoord;
    Position = vec3(ModelViewMatrix * VertexPosition);

    vec3 Normal = normalize(NormalMatrix * VertexNormal);
    vec3 tang = normalize(NormalMatrix * vertexTangent);
    vec3 bittang = normalize(NormalMatrix * vertexBitTangent);
    TangentMatrix = transpose(mat3x3(tang, bittang, Normal));

    gl_Position = MVP * VertexPosition;
}