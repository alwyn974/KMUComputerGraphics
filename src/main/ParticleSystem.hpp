//
// Created by alwyn on 16/12/2023.
//

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Loader.hpp"
#include <glm/glm.hpp>
#include <GL/gl3w.h>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

class Particle {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec4 color;
    float life;
    float size;

    Particle() : position(0.0f), velocity(0.0f), color(1.0f), life(0.0f), size(0.0f) {}
};

class ParticleSystem {
public:
    std::vector<Particle> particles;
    unsigned int maxParticles;
    GLuint VAO = 0;
    GLuint positionVBO = 0;
    GLuint colorVBO = 0;
    ShaderProgram shaderProgram;

    explicit ParticleSystem(const unsigned int maxParticles) : maxParticles(maxParticles) {
        particles.resize(maxParticles);
        shaderProgram.initFromFiles("src/resources/shader/particle/particle.vert", "src/resources/shader/particle/particle.frag");
        shaderProgram.addUniform("MVP");
        generateParticles();
    }

    void generateParticles() {
        for (auto &particle : particles) {
            particle.position = glm::vec3(0.0f); // Set initial position
            particle.velocity = glm::vec3(0.0f); // Set initial velocity
            particle.color = glm::vec4(1.0f); // Set initial color
            particle.life = 1.0f; // Set initial life
            particle.size = 1.0f; // Set initial size
        }

        // Generate VAO
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Generate VBO for positions
        glGenBuffers(1, &positionVBO);
        glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        // Generate VBO for colors
        glGenBuffers(1, &colorVBO);
        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

        // Unbind VAO
        glBindVertexArray(0);
    }

    void updateParticles(float deltaTime) {
        for (auto &particle : particles) {
            particle.position += particle.velocity * deltaTime;
            particle.life -= deltaTime;
            if (particle.life <= 0.0f) {
                // Reset particle
                particle.position = glm::vec3(0.0f);
                particle.life = 1.0f;
            }
        }
    }

    void renderParticles(glm::mat4 mvp) {
        std::vector<glm::vec3> positions;
        std::vector<glm::vec4> colors;

        for (const auto &particle : particles) {
            positions.push_back(particle.position);
            colors.push_back(particle.color);
        }

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
        glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4), colors.data(), GL_DYNAMIC_DRAW);

        shaderProgram.use();
        glUniformMatrix4fv(shaderProgram.uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));
        glDrawArrays(GL_POINTS, 0, particles.size());

        glBindVertexArray(0);
        shaderProgram.disable();
    }
};



#endif //PARTICLE_HPP
