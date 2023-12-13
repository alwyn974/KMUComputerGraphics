//
// Created by alwyn on 11/12/2023.
//

#include <array>
#include "../../include/Skybox.hpp"

#include "external/stb_image.h"

Skybox::Skybox(/*const std::vector<std::string> &faces*/) : textureID(0), VAO(0), VBO(0)/*, faces(faces)*/
{
    initialize();
}

void Skybox::draw(ShaderProgram &shaderProgram)
{
    glUniform1i(shaderProgram.uniform("DrawSkyBox"), GL_TRUE); //indicate that we are doing SKybox
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(shaderProgram.uniform("CubeMapTex"), 0);

    glBindVertexArray(VAO); // select _vaoHandle
    int size = 0;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void Skybox::initialize()
{
    float side = 500.0f; //size of cube
    float side2 = side / 2.0f;
    float v[24 * 3] = {
        // Front
        -side2, -side2, side2,
        side2, -side2, side2,
        side2, side2, side2,
        -side2, side2, side2,
        // Right
        side2, -side2, side2,
        side2, -side2, -side2,
        side2, side2, -side2,
        side2, side2, side2,
        // Back
        -side2, -side2, -side2,
        -side2, side2, -side2,
        side2, side2, -side2,
        side2, -side2, -side2,
        // Left
        -side2, -side2, side2, //12
        -side2, side2, side2, //13
        -side2, side2, -side2, //14
        -side2, -side2, -side2, //15
        // Bottom
        -side2, -side2, side2,
        -side2, -side2, -side2,
        side2, -side2, -side2,
        side2, -side2, side2,
        // Top
        -side2, side2, side2,
        side2, side2, side2,
        side2, side2, -side2,
        -side2, side2, -side2
    };
    GLuint el[] = {
        0, 2, 1, 0, 3, 2, 4, 6, 5, 4, 7, 6,
        8, 10, 9, 8, 11, 10, 12, 14, 13, 12, 15, 14,
        16, 18, 17, 16, 19, 18, 20, 22, 21, 20, 23, 22
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint vboVertices;
    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), &v, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    GLuint vboIndices;
    glGenBuffers(1, &vboIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(el), &el, GL_STATIC_DRAW);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    const std::array<std::string, 6> suffixes = {"left", "right", "top2", "down", "back", "front"};
    GLuint targets[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };
    int width, height, channel;
    for (int i = 0; i < suffixes.size(); i++) {
        std::string filename = "src/resources/textures/skybox/" + suffixes[i] + ".JPG"; //or PNG
        unsigned char *image = stbi_load(filename.c_str(), &width, &height, &channel, 0);
        if (!image) {
            std::cerr << filename << " not found" << std::endl;
        }
        glTexImage2D(targets[i], 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(image);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
