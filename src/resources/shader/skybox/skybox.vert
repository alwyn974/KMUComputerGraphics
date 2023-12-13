#version 450

layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 VertexNormal;

out vec3 ReflectDir;

uniform vec3 WorldCameraPosition;
uniform bool DrawSkyBox;
uniform mat4 ModelMatrix;
uniform mat4 MVP;

void main()
{
    if (DrawSkyBox)
        ReflectDir = VertexPosition;
    else {
        //calculate N,P,V and ReflectDir
        vec3 Normal = normalize((ModelMatrix * vec4(VertexNormal, 0.0)).xyz);
        vec3 VertexPositionWorld = (ModelMatrix * vec4(VertexPosition, 1.0)).xyz;
        vec3 VertexToCamera = normalize(WorldCameraPosition - VertexPositionWorld);
        ReflectDir = reflect(-VertexToCamera, Normal);
        //ReflectDir = reflect(VertexPosition, VertexNormal);
    }

    gl_Position = MVP * vec4(VertexPosition, 1.0);
}
