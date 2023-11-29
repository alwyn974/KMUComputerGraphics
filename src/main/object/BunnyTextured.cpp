//
// Created by alwyn on 29/11/2023.
//

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"
#include "object/BunnyTextured.hpp"
#include "object/data/BunnyTexturedData.hpp"

BunnyTextured::BunnyTextured(const std::string &texturePath) : _vaoHandle(0), _height(0), _width(0), _channels(0), _textureData(nullptr)
{
    _texturePath = texturePath;
    initialize();
}

BunnyTextured::~BunnyTextured()
{
//    glDeleteTextures(1, &_textureId);
//    glDeleteVertexArrays(1, &_vaoHandle);
}

void BunnyTextured::draw() const
{
    glBindVertexArray(_vaoHandle);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->_textureId);
    glDrawElements(GL_TRIANGLES, sizeof(modelIndices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
//    glBindVertexArray(_vaoHandle);
//    int size;
//    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
//    glDrawElements(GL_TRIANGLES, size / sizeof(glm::uint32), GL_UNSIGNED_INT, nullptr);
//    glBindVertexArray(0);
}

void BunnyTextured::initialize()
{
    glGenVertexArrays(1, &_vaoHandle);
    glBindVertexArray(_vaoHandle);

    GLuint vboVertices;
    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(modelVertices), &modelVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
        0, // attribute
        3, // number of elements per vertex, here (x,y,z)
        GL_FLOAT, // type of each element
        GL_FALSE, // take our values as-is
        sizeof(float) * 8, // stride
        nullptr // array buffer offset
    );
    glEnableVertexAttribArray(0);

    GLuint vboNormals;
    glGenBuffers(1, &vboNormals);
    glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(modelVertices), &modelVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
        1, // attribute
        3, // number of elements per vertex, here (x,y,z)
        GL_FLOAT, // type of each element
        GL_FALSE, // take our values as-is
        sizeof(float) * 8, // stride
        (void *) (sizeof(float) * 3) // array buffer offset
    );
    glEnableVertexAttribArray(1);

    GLuint vboTexCoords;
    glGenBuffers(1, &vboTexCoords);
    glBindBuffer(GL_ARRAY_BUFFER, vboTexCoords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(modelVertices), &modelVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
        2, // attribute
        2, // number of elements per vertex, here (x,y,z)
        GL_FLOAT, // type of each element
        GL_FALSE, // take our values as-is
        sizeof(float) * 8, // stride
        (void *) (sizeof(float) * 6) // array buffer offset
    );
    glEnableVertexAttribArray(2);

    GLuint vboIndices;
    glGenBuffers(1, &vboIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(modelIndices), &modelIndices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &this->_textureId);
    glBindTexture(GL_TEXTURE_2D, this->_textureId);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    this->_textureData = stbi_load(this->_texturePath.c_str(), &this->_width, &this->_height, &this->_channels, 0);
    if (this->_textureData == nullptr)
    {
        std::cerr << "Error loading texture: " << this->_texturePath << std::endl;
        exit(1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->_textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(this->_textureData);
    glBindTexture(GL_TEXTURE_2D, 0);
}
