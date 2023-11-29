//
// Created by alwyn on 29/11/2023.
//

#ifndef KMU_EARTH_HPP
#define KMU_EARTH_HPP

#include "Sphere.hpp"

class Earth : public Sphere {
public:
    explicit Earth(float rad, GLuint slices, GLuint stacks, const std::string &texturePath);

    void draw() override;

    const std::string &getTexturePath() const
    {
        return _texturePath;
    }

    int getWidth() const
    {
        return _width;
    }

    int getHeight() const
    {
        return _height;
    }

    int getChannels() const
    {
        return _channels;
    }

    unsigned char *getTextureData() const
    {
        return _textureData;
    }

    GLuint getTextureId() const
    {
        return _textureId;
    }

private:
    std::string _texturePath;
    int _width, _height, _channels;
    unsigned char *_textureData;

    GLuint _textureId;
};

#endif //KMU_EARTH_HPP
