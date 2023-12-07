#version 450

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
in mat3x3 TangentMatrix;

uniform sampler2D ColorTex;
uniform sampler2D NormalMapTex;

uniform vec4 LightPosition;
uniform vec3 LightIntensity; // Ia=Id=Is, LightColor
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Shiness;

layout (location = 0) out vec4 FragColor;

void main()
{
    vec3 L = normalize(TangentMatrix * (LightPosition.xyz - Position.xyz));
    vec3 V = normalize(TangentMatrix * (-Position.xyz));
    vec3 N = texture(NormalMapTex, TexCoord).xyz;
    vec3 R = reflect(-L, N); // Calculate the reflection vector (not normalized
//    vec3 H = normalize(L + V); // Calculate the half-way vector

    vec4 Kd = texture(ColorTex, TexCoord);

    vec3 ambient = LightIntensity * Ka;
    vec3 diffuse = LightIntensity * Kd.xyz * max(dot(L, N), 0.0);
    vec3 specular = Ks * LightIntensity * pow(max(dot(R, V), 0.0), Shiness);
//    vec3 specular = LightIntensity * Ks * pow(max(dot(H, N), 0.0), Shiness); // Use the half-way vector here

//    vec4 texColor = texture(ColorTex, TexCoord);
//    vec4 texColor2 = texture(NormalMapTex, TexCoord);
//    vec4 texColor3 = mix(texColor2, texColor, texColor2.a);

    vec3 finalColor = ambient + diffuse + specular;

    FragColor = vec4(finalColor, 1.0);
//    FragColor = (vec4((ambient + diffuse), 1) * texColor3) + vec4(specular, 1.0);
}