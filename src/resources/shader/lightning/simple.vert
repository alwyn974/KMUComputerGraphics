#version 450

layout(location = 0) in vec4 vertexPosition; //attribute number 0
layout(location = 1) in vec3 vertexNormal; //attribute number 1

//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
uniform vec4 LightLocation;
uniform vec3 Kd;
uniform vec3 Ld;
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

out vec3 LightIntensity;

void main()
{
    vec3 N = normalize(NormalMatrix * vertexNormal);
    //How to transform the VertexPosition into Eye Coordinate?
    vec4 P = ModelViewMatrix * vertexPosition;
    //Vector from Light Location to P
    vec3 L = normalize(LightLocation - P).xyz;

    LightIntensity = Kd * Ld * max(dot(N, L), 0.0f);

    // clip coordinates
    gl_Position = MVP * vertexPosition;
}

//void main()
//{
//    LightIntensity = vertexNormal;
//    gl_Position = MVP * vertexPosition;
//}