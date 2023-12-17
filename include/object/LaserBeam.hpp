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
private:
    float _velocity;
    glm::vec3 _direction;
    glm::vec3 _position;
};

#endif //LASERBEAM_HPP
