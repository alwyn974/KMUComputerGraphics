//
// Created by alwyn on 17/12/2023.
//

#include <iostream>
#include "object/LaserBeam.hpp"

LaserBeam::LaserBeam(float width, float height, float depth, std::optional<glm::vec3> color) : ColorCube(width, height, depth, color), _velocity(30)
{
}

void LaserBeam::update(float currentTime, float deltaTime)
{
    if (!_move)
        return;
    static float xPos = 0.0f;
    xPos += _velocity * deltaTime;

    if (xPos > 50.0f)
        xPos = -50.0f;

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(xPos, 1.0, 0.0f));
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
    _modelMatrix = translate * rotate * scale;
}

void LaserBeam::imgui(const std::string &mainWindowName, const ImGuiTreeNodeFlags_ &flags)
{
    ImGui::Begin(mainWindowName.c_str());
    if (ImGui::CollapsingHeader("Laser Beam Properties", flags)) {
        ImGui::Checkbox("Move", &_move);
        ImGui::SliderFloat("Velocity", &_velocity, 0.0f, 10000.0f);
    }
    ImGui::End();
}

void LaserBeam::init()
{
    ColorCube::init();

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0, 0.0f));
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
    _modelMatrix = translate * rotate * scale;
}
