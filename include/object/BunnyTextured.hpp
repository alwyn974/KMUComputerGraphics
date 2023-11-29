//
// Created by alwyn on 29/11/2023.
//

#ifndef KMU_BUNNYTEXTURED_HPP
#define KMU_BUNNYTEXTURED_HPP

#include "Loader.hpp"
#include <string>

class BunnyTextured {
public:
    explicit BunnyTextured(const std::string &texturePath);

    ~BunnyTextured();

    void draw() const;

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
    void initialize();

    std::string _texturePath;
    int _width, _height, _channels;
    unsigned char *_textureData;

    GLuint _vaoHandle;
    GLuint _textureId;
};

#endif //KMU_BUNNYTEXTURED_HPP
