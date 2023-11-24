//
// Created by alwyn on 23/11/2023.
//

#include "MaterialColor.hpp"
#include <glm/gtc/type_ptr.hpp>

const MaterialColor MaterialColor::emerald = {
    {0.0215, 0.1745, 0.0215},
    {0.07568, 0.61424, 0.07568},
    {0.633, 0.727811, 0.633},
    76.8
};

const MaterialColor MaterialColor::jade = {
    {0.135, 0.2225, 0.1575},
    {0.54, 0.89, 0.63},
    {0.316228, 0.316228, 0.316228},
    12.8
};

const MaterialColor MaterialColor::obsidian = {
    {0.05375, 0.05, 0.06625},
    {0.18275, 0.17, 0.22525},
    {0.332741, 0.328634, 0.346435},
    38.4
};

const MaterialColor MaterialColor::pearl = {
    {0.25, 0.20725, 0.20725},
    {1, 0.829, 0.829},
    {0.296648, 0.296648, 0.296648},
    10.24
};

const MaterialColor MaterialColor::ruby = {
    {0.1745, 0.01175, 0.01175},
    {0.61424, 0.04136, 0.04136},
    {0.727811, 0.626959, 0.626959},
    76.8
};

const MaterialColor MaterialColor::turquoise = {
    {0.1, 0.18725, 0.1745},
    {0.396, 0.74151, 0.69102},
    {0.297254, 0.30829, 0.306678},
    12.8
};

const MaterialColor MaterialColor::brass = {
    {0.329412, 0.223529, 0.027451},
    {0.780392, 0.568627, 0.113725},
    {0.992157, 0.941176, 0.807843},
    27.89743616
};

const MaterialColor MaterialColor::bronze = {
    {0.2125, 0.1275, 0.054},
    {0.714, 0.4284, 0.18144},
    {0.393548, 0.271906, 0.166721},
    25.6
};

const MaterialColor MaterialColor::chrome = {
    {0.25, 0.25, 0.25},
    {0.4, 0.4, 0.4},
    {0.774597, 0.774597, 0.774597},
    76.8
};

const MaterialColor MaterialColor::copper = {
    {0.19125, 0.0735, 0.0225},
    {0.7038, 0.27048, 0.0828},
    {0.256777, 0.137622, 0.086014},
    12.8
};

const MaterialColor MaterialColor::gold = {
    {0.24725, 0.1995, 0.0745},
    {0.75164, 0.60648, 0.22648},
    {0.628281, 0.555802, 0.366065},
    51.2
};

const MaterialColor MaterialColor::silver = {
    {0.19225, 0.19225, 0.19225},
    {0.50754, 0.50754, 0.50754},
    {0.508273, 0.508273, 0.508273},
    51.2
};

const MaterialColor MaterialColor::blackPlastic = {
    {0.0, 0.0, 0.0},
    {0.01, 0.01, 0.01},
    {0.50, 0.50, 0.50},
    32
};

const MaterialColor MaterialColor::cyanPlastic = {
    {0.0, 0.1, 0.06},
    {0.0, 0.50980392, 0.50980392},
    {0.50196078, 0.50196078, 0.50196078},
    32
};

const MaterialColor MaterialColor::greenPlastic = {
    {0.0, 0.0, 0.0},
    {0.1, 0.35, 0.1},
    {0.45, 0.55, 0.45},
    32
};

const MaterialColor MaterialColor::redPlastic = {
    {0.0, 0.0, 0.0},
    {0.5, 0.0, 0.0},
    {0.7, 0.6, 0.6},
    32
};

const MaterialColor MaterialColor::whitePlastic = {
    {0.0, 0.0, 0.0},
    {0.55, 0.55, 0.55},
    {0.70, 0.70, 0.70},
    32
};

const MaterialColor MaterialColor::yellowPlastic = {
    {0.0, 0.0, 0.0},
    {0.5, 0.5, 0.0},
    {0.60, 0.60, 0.50},
    32
};

const MaterialColor MaterialColor::blackRubber = {
    {0.02, 0.02, 0.02},
    {0.01, 0.01, 0.01},
    {0.4, 0.4, 0.4},
    10.0
};

const MaterialColor MaterialColor::cyanRubber = {
    {0.0, 0.05, 0.05},
    {0.4, 0.5, 0.5},
    {0.04, 0.7, 0.7},
    10.0
};

const MaterialColor MaterialColor::greenRubber = {
    {0.0, 0.05, 0.0},
    {0.4, 0.5, 0.4},
    {0.04, 0.7, 0.04},
    10.0
};

const MaterialColor MaterialColor::redRubber = {
    {0.05, 0.0, 0.0},
    {0.5, 0.4, 0.4},
    {0.7, 0.04, 0.04},
    10.0
};

const MaterialColor MaterialColor::whiteRubber = {
    {0.05, 0.05, 0.05},
    {0.5, 0.5, 0.5},
    {0.7, 0.7, 0.7},
    10.0
};

const std::vector<MaterialColor> MaterialColor::values = {
    MaterialColor::emerald,
    MaterialColor::jade,
    MaterialColor::obsidian,
    MaterialColor::pearl,
    MaterialColor::ruby,
    MaterialColor::turquoise,
    MaterialColor::brass,
    MaterialColor::bronze,
    MaterialColor::chrome,
    MaterialColor::copper,
    MaterialColor::gold,
    MaterialColor::silver,
    MaterialColor::blackPlastic,
    MaterialColor::cyanPlastic,
    MaterialColor::greenPlastic,
    MaterialColor::redPlastic,
    MaterialColor::whitePlastic,
    MaterialColor::yellowPlastic,
    MaterialColor::blackRubber,
    MaterialColor::cyanRubber,
    MaterialColor::greenRubber,
    MaterialColor::redRubber,
    MaterialColor::whiteRubber
};

void MaterialColor::populateShaderProgram(ShaderProgram &shaderProgram, const MaterialColor &color,
                                          const std::unordered_map<MaterialColor::Variable, std::string> &uniforms)
{
    for (auto &uniform: uniforms) {
        switch (uniform.first) {
            case Ka:
                glUniform3fv(shaderProgram.uniform(uniform.second), 1, glm::value_ptr(color.ka));
                break;
            case Kd:
                glUniform3fv(shaderProgram.uniform(uniform.second), 1, glm::value_ptr(color.kd));
                break;
            case Ks:
                glUniform3fv(shaderProgram.uniform(uniform.second), 1, glm::value_ptr(color.ks));
                break;
            case Shiness:
                glUniform1fv(shaderProgram.uniform(uniform.second), 1, &color.shiness);
                break;
        }
    }
}
