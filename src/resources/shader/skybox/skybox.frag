#version 450

in vec3 ReflectDir;

uniform samplerCube CubeMapTex;

uniform bool DrawSkyBox;
uniform float ReflectFactor;
uniform vec4 MaterialColor;

out vec4 FragColor;

void main() {
    // Access the cube map texture
    vec4 cubeMapColor = texture(CubeMapTex, ReflectDir);
    if (DrawSkyBox)
        FragColor = cubeMapColor;
    else {
        //mix up the CubeMapColor with the MaterialColor based on the ReflectFactor
        FragColor = mix(cubeMapColor, MaterialColor, ReflectFactor);
    }
}
