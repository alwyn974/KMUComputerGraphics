//
// Created by alwyn on 01/11/2023.
//

#ifndef KMU_COLORCUBE_HPP
#define KMU_COLORCUBE_HPP

#include "AbstractDrawable.hpp"
#include "glm/glm.hpp"
#include <vector>

class ColorCube : public AbstractDrawable {
public:
    explicit ColorCube(int width, int height);

    void init() override;
    void update(float currentTime, float deltaTime) override;
    void imgui(const std::string& mainWindowName) override;
    void draw() const override;

private:
    GLuint vboCubeVertices, vboCubeColors, iboCubeElements;
    int _width;
    int _height;
    std::vector<GLfloat> cubeVertices; // TODO: replace later with glm::vec3
    std::vector<GLfloat> cubeColors;
    std::vector<GLushort> cubeElements;

    bool _resetColor = false;
    bool _rotateColor = false;
    float _rotatingSpeed = 0.1f;
};


#endif //KMU_COLORCUBE_HPP
