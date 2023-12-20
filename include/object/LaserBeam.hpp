//
// Created by alwyn on 17/12/2023.
//

#ifndef LASERBEAM_HPP
#define LASERBEAM_HPP

#include <glm/vec3.hpp>

#include "ColorCube.hpp"

class LaserBeam : public ColorCube {
public:
    explicit LaserBeam(float width = 0.8, float height = 0.2, float depth = 1.0f, std::optional<glm::vec3> color = std::nullopt);

    void init() override;

    void update(float currentTime, float deltaTime) override;

    glm::mat4 getModelMatrix()
    {
        return _modelMatrix;
    }

    float getVelocity() const
    {
        return _velocity;
    }

    void imgui(const std::string &mainWindowName, const ImGuiTreeNodeFlags_ &flags = ImGuiTreeNodeFlags_None) override;

private:
    float _velocity;
    bool _move = false;
    glm::mat4 _modelMatrix;
};

#endif //LASERBEAM_HPP
