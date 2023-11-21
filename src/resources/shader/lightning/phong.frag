#version 450

in vec3 LightIntensity; // must match the name in the vertex shader, only difference is in vs it's out
layout(location = 0) out vec4 FragColor;

void main()
{
    FragColor = vec4(LightIntensity, 1.0f); // set the output to the color specified in the vertex shader
}