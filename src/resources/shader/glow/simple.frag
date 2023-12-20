#version 450

in vec3 fcolor; // must be the same name as the out variable in the vertex shader, only change from "out" to "in"
out vec4 fragColor; // must have at least one vec4 out variable
void main() {
    fragColor = vec4(fcolor, 1.0); // set the output variable to a vec4 value
}