//
// Created by alwyn on 16/12/2023.
//

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Loader.hpp"
#include "glm/glm.hpp"
#include "GL/gl3w.h"
#include <vector>
#include "glm/gtc/type_ptr.hpp"

class Particle {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 color;
    float life;
    float size;

    Particle() : position(0.0f), velocity(0.0f), color(1.0f), life(0.0f), size(0.0f) {}
};

class ParticleSystem {
public:
    explicit ParticleSystem(const unsigned int maxParticles);

    void generateParticles();

    void updateParticles(float deltaTime);

    void renderParticles(glm::mat4 mvp);

private:
    std::vector<Particle> particles;
    unsigned int maxParticles;
    GLuint VAO = 0;
    GLuint positionVBO = 0;
    GLuint colorVBO = 0;
    ShaderProgram shaderProgram;
};



#endif //PARTICLE_HPP
