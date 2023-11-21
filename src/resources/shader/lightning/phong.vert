#version 450

layout(location = 0) in vec4 vertexPosition; //attribute number 0
layout(location = 1) in vec3 vertexNormal; //attribute number 1

struct LightInfo {
    vec4 Position; // Light position in eye coords.
    vec3 La; // Ambient light intensity
    vec3 Ld; // Diffuse light intensity
    vec3 Ls; // Specular light intensity
};
uniform LightInfo Light;

struct MaterialInfo {
    vec3 Ka; // Ambient reflectivity
    vec3 Kd; // Diffuse reflectivity
    vec3 Ks; // Specular reflectivity
    float Shiness; // Specular shininess factor (phong exponent)
};
uniform MaterialInfo Material;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

out vec3 LightIntensity;

void main()
{
    vec3 N = normalize(NormalMatrix * vertexNormal);
    // How to transform the VertexPosition into Eye Coordinate?
    vec4 P = ModelViewMatrix * vertexPosition;
    // Vector from Light Location to P
    vec3 L = normalize(Light.Position - P).xyz;

    vec3 R = reflect(-L,N);
    vec3 V = normalize(-P.xyz);

    vec3 ambient = Light.La * Material.Ka;
    vec3 diffuse = Light.Ld * Material.Kd * max(dot(L, N), 0);
    vec3 spec = Light.Ls * Material.Ks * pow(max(dot(R,V), 0.0), Material.Shiness);

    LightIntensity = LightIntensity = ambient + diffuse + spec;

    // clip coordinates
    gl_Position = MVP * vertexPosition;
}