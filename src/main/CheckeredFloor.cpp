//
// Created by alwyn on 15/11/2023.
//

#include "CheckeredFloor.hpp"

CheckeredFloor::CheckeredFloor(int size, int nsquare) : _size(size), _nsquare(nsquare), vao(0), vboVertices(0), vboColors(0) {
    generate();
}

void CheckeredFloor::generate()
{
    float squareSize = static_cast<float>(_size) / _nsquare;
    float halfSize = _size * 0.5f;
    glm::vec3 color1(0.7f, 0.7f, 0.7f);
    glm::vec3 color2(0.3f, 0.3f, 0.3f);

    for (int i = 0; i < _nsquare; ++i) {
        for (int j = 0; j < _nsquare; ++j) {
            float x = i * squareSize - halfSize;
            float z = j * squareSize - halfSize;

            glm::vec3 color = (i + j) % 2 == 0 ? color1 : color2;

            // Add vertices and colors for each square
            // Triangle 1
            vertices.insert(vertices.end(), {
                glm::vec3(x, 0, z),
                glm::vec3(x + squareSize, 0, z),
                glm::vec3(x + squareSize, 0, z + squareSize)
            });

            colors.insert(colors.end(), { color, color, color });

            // Triangle 2
            vertices.insert(vertices.end(), {
                glm::vec3(x, 0, z),
                glm::vec3(x + squareSize, 0, z + squareSize),
                glm::vec3(x, 0, z + squareSize)
            });

            colors.insert(colors.end(), { color, color, color });
        }
    }

    // Generate and bind VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Generate and bind VBO for vertices
    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    // Generate and bind VBO for colors
    glGenBuffers(1, &vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    // Unbind VAO
    glBindVertexArray(0);
}

void CheckeredFloor::draw()
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}
