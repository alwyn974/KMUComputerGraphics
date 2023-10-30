#version 450

// Note that the layout location is only required for the vertex shader
layout(location = 0) in vec4 position; // attribute number 0
layout(location = 1) in vec3 color; // attribute number 1

out vec3 fcolor;
void main() {
    fcolor = color;
    // gl_Position: clip coordinates
    // Make sure that gl_Position is a vec4
    gl_Position = position;
}