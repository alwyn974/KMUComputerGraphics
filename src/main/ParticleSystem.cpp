//
// Created by alwyn on 16/12/2023.
//

#include "ParticleSystem.hpp"
#include "AbstractDrawable.hpp"

ParticleSystem::ParticleSystem(const unsigned int maxParticles)
{
    this->maxParticles = maxParticles;
    particles.resize(maxParticles);
    shaderProgram.initFromFiles("src/resources/shader/particle/particle.vert", "src/resources/shader/particle/particle.frag");
    shaderProgram.addUniform("MVP");

    generateParticles();
}

void ParticleSystem::generateParticles()
{
    for (auto &particle: particles) {
        // randomize position
        //        float x = ((float) rand() / (RAND_MAX)) * 2 - 1;
        //        float y = ((float) rand() / (RAND_MAX)) * 2 - 1;
        //        float z = ((float) rand() / (RAND_MAX)) * 2 - 1;
        //        particle.position = glm::vec3(x, y, z);
        particle.position = glm::vec3(0.0f); // Set initial position
        // set velocity to make particles move like a fountain
        float vx = ((float) rand() / (RAND_MAX)) * 2 - 1;
        float vy = ((float) rand() / (RAND_MAX)) * 2 - 1;
        float vz = ((float) rand() / (RAND_MAX)) * 2 - 1;
        particle.velocity = glm::vec3(vx, vy, vz);
        //        particle.velocity = glm::vec3(0.0f); // Set initial velocity
        particle.color = glm::vec3(1.0f, 0, 0); // Set initial color
        particle.life = 1.0f; // Set initial life
        particle.size = 1.0f; // Set initial size
    }

    // Generate VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate VBO for positions
    glGenBuffers(1, &positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    // Generate VBO for colors
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    // Unbind VAO
    glBindVertexArray(0);
}

void ParticleSystem::updateParticles(float deltaTime)
{
    for (auto &particle: particles) {
        particle.position += particle.velocity * deltaTime;
        particle.life -= deltaTime;
        if (particle.life <= 0.0f) {
            // Reset particle
            particle.position = glm::vec3(0.0f);
            particle.life = 1.0f;
        }
    }
}

void ParticleSystem::renderParticles(glm::mat4 mvp)
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> colors;
    static int drawType = GL_POINTS;
    static std::string drawTypeString = "GL_POINTS";
    static std::string drawTypesString[] = {"GL_POINTS","GL_LINES","GL_LINE_LOOP","GL_LINE_STRIP","GL_TRIANGLES","GL_TRIANGLE_STRIP","GL_TRIANGLE_FAN","GL_QUADS"};
    static int drawTypes[] = {GL_POINTS,GL_LINES,GL_LINE_LOOP,GL_LINE_STRIP,GL_TRIANGLES,GL_TRIANGLE_STRIP,GL_TRIANGLE_FAN,GL_QUADS};

    ImGui::Begin("Objects");
    if (ImGui::CollapsingHeader("Particles Properties")) {
        ImGui::SliderInt("Draw Type", &drawType, 0, 7, drawTypeString.c_str());
        drawTypeString = drawTypesString[drawType];
    }
    ImGui::End();

    for (const auto &particle: particles) {
        positions.push_back(particle.position);
        colors.push_back(particle.color);
    }
    //    shaderProgram.use();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_DYNAMIC_DRAW);

    glUniformMatrix4fv(shaderProgram.uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawArrays(drawType, 0, positions.size());

    glBindVertexArray(0);
    //    shaderProgram.disable();
}
