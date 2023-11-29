//
// Created by alwyn on 16/10/2023.
//

#include <array>
#include "MyGlWindow.hpp"

static float DEFAULT_VIEW_POINT[3] = {7, 7, 7};
static float DEFAULT_VIEW_CENTER[3] = {0, 0, 0};
static float DEFAULT_UP_VECTOR[3] = {0, 1, 0};

// there is a glm::lookAt function also
static glm::mat4 lookAt(glm::vec3 campos, glm::vec3 look, glm::vec3 up)
{
    glm::vec3 zaxis = glm::normalize(campos - look);
    glm::vec3 xaxis = glm::normalize(glm::cross(up, zaxis));
    glm::vec3 yaxis = glm::cross(zaxis, xaxis);

    glm::mat4 view = glm::mat4(1.0f);
    view[0][0] = xaxis.x;
    view[1][0] = xaxis.y;
    view[2][0] = xaxis.z;
    view[0][1] = yaxis.x;
    view[1][1] = yaxis.y;
    view[2][1] = yaxis.z;
    view[0][2] = zaxis.x;
    view[1][2] = zaxis.y;
    view[2][2] = zaxis.z;
    view[3][0] = -glm::dot(xaxis, campos);
    view[3][1] = -glm::dot(yaxis, campos);
    view[3][2] = -glm::dot(zaxis, campos);
    return view;
}

static glm::mat4 perspective(float fovy, float aspect, float nearZ, float farZ)
{
    float f = 1.0f / (float) glm::tan(glm::radians(fovy * 0.5f));

    glm::mat4 mat = glm::mat4(0.0f);
    mat[0][0] = f / aspect;
    mat[1][1] = f;
    mat[2][2] = (farZ + nearZ) / (nearZ - farZ);
    mat[2][3] = -1.0f;
    mat[3][2] = (2.0f * farZ * nearZ) / (nearZ - farZ);
    return mat;
}

MyGLWindow::MyGLWindow(int width, int height)
{
    _width = width;
    _height = height;

    glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
    glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
    glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);

    float aspect = (float) width / (float) height;
    viewer = Viewer(viewPoint, viewCenter, upVector, 45.0f, aspect);

    this->initialize();
}

void MyGLWindow::initialize()
{
    //    this->_shaderProgram.initFromFiles("src/resources/shader/lightning/phong.vert", "src/resources/shader/lightning/phong.frag");
    this->_shaderProgramFloor.initFromFiles("src/resources/shader/color/simple.vert", "src/resources/shader/color/simple.frag");
    this->_shaderProgramBunnyTextured.initFromFiles("src/resources/shader/texture/simple.vert", "src/resources/shader/texture/simple.frag");
//    this->_shaderProgramTeapot.initFromFiles("src/resources/shader/lightning/phong_in_frag.vert", "src/resources/shader/lightning/phong_in_frag.frag");
//    this->_shaderProgramTorus.initFromFiles("src/resources/shader/lightning/phong_in_frag.vert", "src/resources/shader/lightning/phong_in_frag.frag");
    // TODO: use only one shader program for teapot and torus

    /*const std::array<ShaderProgram *, 2> shaderPrograms = {&_shaderProgramTeapot, &_shaderProgramTorus};
    for (const auto &shaderProgram: shaderPrograms) {
        shaderProgram->addUniform("LightPosition");
        shaderProgram->addUniform("LightIntensity");
        shaderProgram->addUniform("Ka");
        shaderProgram->addUniform("Kd");
        shaderProgram->addUniform("Ks");
        shaderProgram->addUniform("Shiness");

        shaderProgram->addUniform("ModelViewMatrix"); // View*Model : mat4
        shaderProgram->addUniform("NormalMatrix"); // Refer next slide : mat3
        shaderProgram->addUniform("MVP"); // Projection * View * Model : mat4
    }*/
    this->_shaderProgramBunnyTextured.addUniform("LightPosition");
    this->_shaderProgramBunnyTextured.addUniform("LightIntensity");
    this->_shaderProgramBunnyTextured.addUniform("Ka");
    this->_shaderProgramBunnyTextured.addUniform("Kd");
    this->_shaderProgramBunnyTextured.addUniform("Ks");
    this->_shaderProgramBunnyTextured.addUniform("Shiness");

    this->_shaderProgramBunnyTextured.addUniform("ModelViewMatrix"); // View*Model : mat4
    this->_shaderProgramBunnyTextured.addUniform("NormalMatrix"); // Refer next slide : mat3
    this->_shaderProgramBunnyTextured.addUniform("MVP"); // Projection * View * Model : mat4
    this->_shaderProgramBunnyTextured.addUniform("Tex1");

    this->_shaderProgramFloor.addUniform("MVP"); // Projection * View * Model : mat4

    _floor = CheckeredFloor(100, 10);

//    _teapot = VBOTeapot(64, glm::mat4(1.0f));
//    _torus = VBOTorus(1.5f, 0.75f, 50, 50);

//    _bunny = Bunny();

    _bunnyTextured = BunnyTextured("src/resources/textures/bunny.png");
    _earth = Earth(1, 50, 50, "src/resources/textures/earth.jpg");

//    _cow = Cow();
//    _sphere = Sphere(1, 50, 50);

    //    _cube = ColorCube(_width, _height);
}

void MyGLWindow::draw()
{
    // position, size
    glViewport(0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST); // enable depth testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    glm::vec3 eye = viewer->getViewPoint();
    glm::vec3 look = viewer->getViewCenter();
    glm::vec3 up = viewer->getUpVector();
    glm::mat4 view = lookAt(eye, look, up); // Calculate view matrix from paramters of viewer

    glm::mat4 projection = perspective(45.0f, 1.0f * (float) _width / (float) _height, 0.1f, 500.0f);

    {
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0, 0.0f));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
        glm::mat4 model = translate * rotate * scale; // Combination of transformation matrix

        glm::mat4 mView = view * model;
        glm::mat4 mvp = projection * view * model;

        glm::mat4 inverseMVP = glm::inverse(mView);
        glm::mat3 normalMatrix = glm::mat3(glm::transpose(inverseMVP)); // normal matrix

        this->_shaderProgramFloor.use();

        glUniformMatrix4fv(this->_shaderProgramFloor.uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));
        if (_floor.has_value())
            _floor->draw();

        this->_shaderProgramFloor.disable();
    }

    glm::vec4 lightPos(10, 10, 0, 1);
    glm::vec3 lightIntensity(1, 1, 1);
    // call shader program
    {
        static float rotationSpeed = 0.01f;
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.0, 0.0f));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
        glm::mat4 model = translate * rotate * scale; // Combination of transformation matrix

        glm::mat4 mView = view * model;
        glm::mat4 mvp = projection * view * model;

        glm::mat4 inverseMVP = glm::inverse(mView);
        glm::mat3 normalMatrix = glm::mat3(glm::transpose(inverseMVP)); // normal matrix

        this->_shaderProgramBunnyTextured.use();
        // draw

        glUniform4fv(this->_shaderProgramBunnyTextured.uniform("LightPosition"), 1, glm::value_ptr(lightPos));
        glUniform3fv(this->_shaderProgramBunnyTextured.uniform("LightIntensity"), 1, glm::value_ptr(lightIntensity));
        const MaterialColor color = {
            .ka = glm::vec3(0.3, 0.3, 0.3),
            .kd = glm::vec3(1, 1, 1),
            .ks = glm::vec3(0.3, 0.3, 0.3),
            .shiness = 10
        };
        MaterialColor::populateShaderProgram(_shaderProgramBunnyTextured, color);

        glUniformMatrix4fv(this->_shaderProgramBunnyTextured.uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(mView));
        glUniformMatrix3fv(this->_shaderProgramBunnyTextured.uniform("NormalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniformMatrix4fv(this->_shaderProgramBunnyTextured.uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

        /*if (_bunnyTextured.has_value()) {
            glUniform1i(this->_shaderProgramBunnyTextured.uniform("Tex1"), 0);
            _bunnyTextured->draw();
        }*/
        if (_earth.has_value()) {
            glUniform1i(this->_shaderProgramBunnyTextured.uniform("Tex1"), 0);
            _earth->draw();
        }
        //    if (_cube.has_value())
        //        _cube->draw();

//        if (_teapot.has_value())
//            _teapot->draw();

//        if (_bunny.has_value())
//            _bunny->draw();

//        if (_sphere.has_value())
//            _sphere->draw();

        // unbind shader program
        this->_shaderProgramBunnyTextured.disable();
    }

    /*{
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.5f, 0.0f));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
        glm::mat4 model = translate * rotate * scale; // Combination of transformation matrix

        glm::mat4 mView = view * model;
        glm::mat4 mvp = projection * view * model;

        glm::mat4 inverseMVP = glm::inverse(mView);
        glm::mat3 normalMatrix = glm::mat3(glm::transpose(inverseMVP)); // normal matrix

        this->_shaderProgramTorus.use();

        glUniform4fv(this->_shaderProgramTorus.uniform("LightPosition"), 1, glm::value_ptr(lightPos));
        glUniform3fv(this->_shaderProgramTorus.uniform("LightIntensity"), 1, glm::value_ptr(lightIntensity));
        MaterialColor::populateShaderProgram(_shaderProgramTorus, MaterialColor::ruby);

        glUniformMatrix4fv(this->_shaderProgramTorus.uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(mView));
        glUniformMatrix3fv(this->_shaderProgramTorus.uniform("NormalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniformMatrix4fv(this->_shaderProgramTorus.uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

        if (_torus.has_value())
            _torus->draw();

        this->_shaderProgramTorus.disable();
    }*/
}
