//
// Created by alwyn on 16/10/2023.
//

#include "MyGlWindow.hpp"

MyGLWindow::MyGLWindow(int width, int height) {
    _width = width;
    _height = height;

    this->setupBuffer();
}

GLuint vaoHandle, vboPosition, vboColor;

void MyGLWindow::draw() {
    // position, size
    glViewport(0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST); // enable depth testing

    // call shader program
    this->_shaderProgram.use();
    // draw

    if (_cube.has_value())
        _cube->draw();

    // unbind shader program
    this->_shaderProgram.disable();
}

void MyGLWindow::setSize(int width, int height) {
    _width = width;
    _height = height;
}

void MyGLWindow::setupBuffer() {
    this->_shaderProgram.initFromFiles("src/resources/shader/simple.vert", "src/resources/shader/simple.frag");

    _cube = ColorCube(_width, _height);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    /*float vertices[] = {
            -0.2f, -0.2f, 0.0f, 1.0f,  // bottom left
            -0, 0.2f, 0.0f, 1.0f,  // top
            0.2f, -0.2f, 0.0f, 1.0f,  // bottom right
    };
    float colors[] = {
            1.0f, 0.0f, 0.0f,  // bottom left
            0.0f, 1.0f, 0.0f,  // top
            0.0f, 0.0f, 1.0f,  // bottom right
    };*/

    /*float vertices[] = {
            -0.2f, -0.2f, 0.0f, 1.0f,  // bottom left
            -0.2, 0.2, 0.0f, 1.0f,  // top
            0.2f, 0.2f, 0.0f, 1.0f,  // top right
            -0.2f, -0.2f, 0.0f, 1.0f,  // bottom left
            0.2f, -0.2f, 0.0f, 1.0f,  // bottom right
            0.2f, 0.2f, 0.0f, 1.0f,  // top right
    };
    float colors[] = {
            1.0f, 0.0f, 0.0f,  // bottom left
            0.0f, 1.0f, 0.0f,  // top
            0.0f, 0.0f, 1.0f,  // bottom right
            1.0f, 0.0f, 0.0f,  // bottom left
            0.0f, 1.0f, 0.0f,  // top
            0.0f, 0.0f, 1.0f,  // bottom right
    };*/

    /*float vertex[] = {
            -0.2f, -0.2f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, // bottom left
            -0.2, 0.2, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f, // top
            0.2f, 0.2f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top right

            -0.2f, -0.2f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, // bottom left
            0.2f, -0.2f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f, // bottom right
            0.2f, 0.2f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top right
    };*/
}
