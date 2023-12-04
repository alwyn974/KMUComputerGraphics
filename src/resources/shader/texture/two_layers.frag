#version 450

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D Tex1;
uniform sampler2D Tex2;

uniform vec4 LightPosition;
uniform vec3 LightIntensity; // Ia=Id=Is, LightColor
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Shiness;

layout (location = 0) out vec4 FragColor;

void main()
{
    vec3 N = normalize(Normal);
    vec3 L = normalize(LightPosition - vec4(Position, 1.0)).xyz;
    vec3 V = normalize(-Position);
    //    vec3 R = reflect(-L, N);
    vec3 H = normalize(L + V); // Calculate the half-way vector

    vec3 ambient = LightIntensity * Ka;
    vec3 diffuse = LightIntensity * Kd * max(dot(N, L), 0.0);
    //    vec3 specular = Ks * LightIntensity * pow(max(dot(R, V), 0.0), Shiness);
    vec3 specular = LightIntensity * Ks * pow(max(dot(H, N), 0.0), Shiness); // Use the half-way vector here

    vec4 texColor = texture(Tex1, TexCoord);
    vec4 texColor2 = texture(Tex2, TexCoord);
    vec4 texColor3 = mix(texColor2, texColor, texColor2.a);

    FragColor = (vec4((ambient + diffuse), 1) * texColor3) + vec4(specular, 1.0);
}