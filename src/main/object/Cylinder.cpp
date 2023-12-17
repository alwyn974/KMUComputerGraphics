//
// Created by alwyn on 17/12/2023.
//

#include "object/Cylinder.hpp"

Cylinder::Cylinder(float baseRadius, float topRadius, float height, int slices, int stacks, const glm::vec3&color)
{
    this->baseRadius = baseRadius;
    this->topRadius = topRadius;
    this->height = height;
    this->slices = slices;
    this->stacks = stacks;

    float stackHeight = height / stacks;
    float radiusStep = (topRadius - baseRadius) / stacks;
    float sectorStep = 2.0f * M_PI / slices;
    float sectorAngle, x, y, z, radius;

    for (int i = 0; i <= stacks; ++i) {
        y = -0.5f * height + i * stackHeight;
        radius = baseRadius + i * radiusStep;

        for (int j = 0; j <= slices; ++j) {
            sectorAngle = j * sectorStep;

            x = radius * cosf(sectorAngle);
            z = radius * sinf(sectorAngle);

            vertices.push_back(glm::vec3(x, y, z));
            colors.push_back(color);
        }
    }

    for (int i = 0; i < stacks; ++i) {
        int k1 = i * (slices + 1);
        int k2 = k1 + slices + 1;

        for (int j = 0; j < slices; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stacks - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

void Cylinder::init()
{
    AbstractDrawable::init();

    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vboIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors[0]) * colors.size(), colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Cylinder::update(float currentTime, float deltaTime)
{
}

void Cylinder::imgui(const std::string&mainWindowName)
{
}

void Cylinder::draw() const
{
    AbstractDrawable::draw();

    glBindVertexArray(vaoHandle);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}
