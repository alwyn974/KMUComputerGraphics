//
// Created by alwyn on 29/11/2023.
//

#ifndef KMU_BUNNYTEXTURED_HPP
#define KMU_BUNNYTEXTURED_HPP

#include "Loader.hpp"
#include <string>

class BunnyTextured {
public:
    explicit BunnyTextured(const std::string &texturePath, const std::string &secondTexturePath);

    void draw(ShaderProgram &shaderProgram) const;

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

    const GLuint *getTextureIds() const
    {
        return _textureIds;
    }

private:
    void initialize();

    std::string _texturePath;
    std::string _secondTexturePath;
    int _width, _height, _channels;
    unsigned char *_textureData;
    unsigned char *_secondTextureData;

    GLuint _vaoHandle;
    GLuint _textureIds[2];
};

#endif //KMU_BUNNYTEXTURED_HPP
