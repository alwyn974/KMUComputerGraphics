//
// Created by alwyn on 17/12/2023.
//

#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "AbstractDrawable.hpp"
#include <vector>
#include <glm/glm.hpp>

class Cylinder : public AbstractDrawable {
public:
    explicit Cylinder(float baseRadius, float topRadius, float height, int slices, int stacks, const glm::vec3 &color);

    void init() override;
    void update(float currentTime, float deltaTime) override;
    void imgui(const std::string& mainWindowName) override;
    void draw() const override;

private:
    GLuint vboVertices = 0, vboIndices = 0, vboColors = 0;
    std::vector<glm::vec3> vertices;
    std::vector<GLushort> indices;
    std::vector<glm::vec3> colors;

    float baseRadius;
    float topRadius;
    float height;
    int slices;
    int stacks;
};


#endif //CYLINDER_HPP
