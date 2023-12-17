//
// Created by alwyn on 15/11/2023.
//

#ifndef KMU_CHECKEREDFLOOR_HPP
#define KMU_CHECKEREDFLOOR_HPP

#include "AbstractDrawable.hpp"
#include <vector>
#include <glm/vec3.hpp>

class CheckeredFloor : public AbstractDrawable {
public:
    explicit CheckeredFloor(int size, int nsquare);

    void generate();

    void init() override;

    void update(float currentTime, float deltaTime) override;

    void imgui(const std::string& mainWindowName) override;

    void draw() const override;

    int getSize() const
    {
        return _size;
    }

    int getNsquare() const
    {
        return _nsquare;
    }

private:
    int _size;
    int _nsquare;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;
    GLuint vboVertices, vboColors;
};

#endif //KMU_CHECKEREDFLOOR_HPP
