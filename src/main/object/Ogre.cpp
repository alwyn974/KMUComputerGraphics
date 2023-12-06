//
// Created by alwyn on 06/12/2023.
//

#include "object/Ogre.hpp"
#include "object/data/OgreData.hpp"
#include "external/stb_image.h"

Ogre::Ogre(const std::string &texturePath, const std::string &normalMapPath) : _vaoHandle(0), _textureIds{0, 0}
{
    _texturePath = texturePath;
    _normalMapPath = normalMapPath;
    initialize();
}

void Ogre::draw(ShaderProgram &shaderProgram) const
{
    glEnable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE0); //Activate texture 0
    glBindTexture(GL_TEXTURE_2D, this->_textureIds[0]);
    glUniform1i(shaderProgram.uniform("ColorTex"), 0);

    glActiveTexture(GL_TEXTURE1); //Activate texture 1
    glBindTexture(GL_TEXTURE_2D, this->_textureIds[1]);
    glUniform1i(shaderProgram.uniform("NormalMapTex"), 1);

    glBindVertexArray(_vaoHandle);
    glDrawElements(GL_TRIANGLES, sizeof(modelIndices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void Ogre::initialize()
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

    const auto &[indexedTangents, indexedBitTangent] = computeTangentBasis();

    GLuint tangentbuffer;
    glGenBuffers(1, &tangentbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexedTangents.size() * sizeof(glm::vec3), &indexedTangents[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint bitangentbuffer;
    glGenBuffers(1, &bitangentbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexedBitTangent.size() * sizeof(glm::vec3), &indexedBitTangent[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &this->_textureIds[0]);

    glBindTexture(GL_TEXTURE_2D, this->_textureIds[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    int _width, _height, _channels;
    unsigned char *textureData = stbi_load(this->_texturePath.c_str(), &_width, &_height, &_channels, 0);
    if (textureData == nullptr) {
        std::cerr << "Error loading texture: " << this->_texturePath << std::endl;
        exit(1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureData);

    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &this->_textureIds[1]);

    glBindTexture(GL_TEXTURE_2D, this->_textureIds[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    int width, height, channels;
    unsigned char *secondTextureData = stbi_load(this->_normalMapPath.c_str(), &width, &height, &channels, 0);
    if (secondTextureData == nullptr) {
        std::cerr << "Error loading texture: " << this->_normalMapPath << std::endl;
        exit(1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, secondTextureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(secondTextureData);

    glBindTexture(GL_TEXTURE_2D, 0);
}

std::tuple<std::vector<glm::vec3>, std::vector<glm::vec3>> Ogre::computeTangentBasis()
{
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;

    for (int i = 0; i < 19985; i += 3) {
        // Shortcuts for vertices
        const glm::vec3 &v0 = modelVertices[i + 0].position;
        const glm::vec3 &v1 = modelVertices[i + 1].position;
        const glm::vec3 &v2 = modelVertices[i + 2].position;

        // Shortcuts for UVs
        const glm::vec2 &uv0 = modelVertices[i + 0].uv;
        const glm::vec2 &uv1 = modelVertices[i + 1].uv;
        const glm::vec2 &uv2 = modelVertices[i + 2].uv;

        // Edges of the triangle : position delta
        const glm::vec3 deltaPos1 = v1 - v0;
        const glm::vec3 deltaPos2 = v2 - v0;

        // UV delta
        const glm::vec2 deltaUV1 = uv1 - uv0;
        const glm::vec2 deltaUV2 = uv2 - uv0;

        const float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        const glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
        const glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;
        // Set the same tangent for all three vertices of the triangle.
        // They will be merged later, in vboindexer.cpp
        tangents.push_back(tangent);
        tangents.push_back(tangent);
        tangents.push_back(tangent);

        // Same thing for bitangents
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
    }

    return {tangents, bitangents};
}
