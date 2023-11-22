#version 450

in vec3 Position;
in vec3 Normal;

uniform vec4 LightPosition;
uniform vec3 LightIntensity; // Ia=Id=Is, LightColor
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float shiness;

layout(location = 0) out vec4 FragColor;

void main()
{
    vec3 N = normalize(Normal);
    vec3 L = normalize(LightPosition - vec4(Position, 1.0)).xyz;
    vec3 V = normalize(-Position);
//    vec3 R = reflect(-L, N);
    vec3 H = normalize(L + V); // Calculate the half-way vector

    vec3 ambient = LightIntensity * Ka;
    vec3 diffuse = LightIntensity * Kd * max(dot(N, L), 0.0);
//    vec3 specular = Ks * LightIntensity * pow(max(dot(R, V), 0.0), shiness);
    vec3 specular = LightIntensity * Ks * pow(max(dot(H, N), 0.0), shiness); // Use the half-way vector here

    vec3 color = ambient + diffuse + specular;

    FragColor = vec4(color, 1.0);
}