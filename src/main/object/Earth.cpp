//
// Created by alwyn on 29/11/2023.
//

#include "object/Earth.hpp"
#include "external/stb_image.h"

Earth::Earth(float rad, GLuint slices, GLuint stacks, const std::string &texturePath) : Sphere(rad, slices, stacks)
{
    _texturePath = texturePath;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &this->_textureId);
    glBindTexture(GL_TEXTURE_2D, this->_textureId);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    this->_textureData = stbi_load(this->_texturePath.c_str(), &this->_width, &this->_height, &this->_channels, 0);
    if (this->_textureData == nullptr) {
        std::cerr << "Error loading texture: " << this->_texturePath << std::endl;
        exit(1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->_textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(this->_textureData);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Earth::draw()
{
    glBindTexture(GL_TEXTURE_2D, this->_textureId);

    Sphere::draw();

    glBindTexture(GL_TEXTURE_2D, 0);
}
