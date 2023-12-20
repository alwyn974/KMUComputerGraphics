//
// Created by alwyn on 01/11/2023.
//

#ifndef KMU_COLORCUBE_HPP
#define KMU_COLORCUBE_HPP

#include <optional>

#include "AbstractDrawable.hpp"
#include "glm/glm.hpp"
#include <vector>

class ColorCube : public AbstractDrawable {
public:
    explicit ColorCube(float width, float height, float depth = 1.0f, std::optional<glm::vec3> color = std::nullopt);

    void init() override;
    void update(float currentTime, float deltaTime) override;
    void imgui(const std::string& mainWindowName, const ImGuiTreeNodeFlags_ &flags = ImGuiTreeNodeFlags_None) override;
    void draw() const override;

private:
    GLuint vboCubeVertices, vboCubeColors, iboCubeElements;
    float _width;
    float _height;
    float _depth;
    std::vector<glm::vec3> cubeVertices;
    std::vector<glm::vec3> cubeColors;
    std::vector<GLushort> cubeElements;

    bool _resetColor = false;
    bool _rotateColor = false;
    float _rotatingSpeed = 0.1f;
};


#endif //KMU_COLORCUBE_HPP
