//
// Created by alwyn on 23/11/2023.
//

#ifndef KMU_MATERIALCOLOR_HPP
#define KMU_MATERIALCOLOR_HPP

#include "Loader.hpp"
#include <glm/glm.hpp>
#include <GL/gl3w.h>
#include <vector>
#include <string>
#include <unordered_map>

class MaterialColor {
public:
    enum Variable {
        Ka, Kd, Ks, Shiness
    };

    /**
     * Ambient color
     */
    glm::vec3 ka;
    /**
     * Diffuse color
     */
    glm::vec3 kd;
    /**
     * Specular color
     */
    glm::vec3 ks;
    /**
     * Shiness
     */
    GLfloat shiness;

    /**
     * Populate the shader program with the material color
     * @param shaderProgram  the shader program to populate
     * @param color          the material color
     * @param uniforms       the uniforms to populate. For example (default one):
     * <pre>{{MaterialColor::Variable::Ka "Ka"}, {MaterialColor::Variable::Kd,"Kd"}, {MaterialColor::Variable::Ks, "Ks"}, {MaterialColor::Variable::Shiness,"Shiness"}}</pre>
     */
    static void populateShaderProgram(ShaderProgram
                                      &shaderProgram,
                                      const MaterialColor &color,
                                      const std::unordered_map<MaterialColor::Variable, std::string> &uniforms = {
                                          {Ka,      "Ka"},
                                          {Kd,      "Kd"},
                                          {Ks,      "Ks"},
                                          {Shiness, "Shiness"},
                                      }
    );

    const static MaterialColor emerald;
    const static MaterialColor jade;
    const static MaterialColor obsidian;
    const static MaterialColor pearl;
    const static MaterialColor ruby;
    const static MaterialColor turquoise;
    const static MaterialColor brass;
    const static MaterialColor bronze;
    const static MaterialColor chrome;
    const static MaterialColor copper;
    const static MaterialColor gold;
    const static MaterialColor silver;
    const static MaterialColor blackPlastic;
    const static MaterialColor cyanPlastic;
    const static MaterialColor greenPlastic;
    const static MaterialColor redPlastic;
    const static MaterialColor whitePlastic;
    const static MaterialColor yellowPlastic;
    const static MaterialColor blackRubber;
    const static MaterialColor cyanRubber;
    const static MaterialColor greenRubber;
    const static MaterialColor redRubber;
    const static MaterialColor whiteRubber;

    /**
     * All default material colors
     */
    const static std::vector<MaterialColor> values;
};

#endif //KMU_MATERIALCOLOR_HPP
