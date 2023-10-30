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
    glBindVertexArray(vaoHandle); // select VAO
    glDrawArrays(GL_TRIANGLES, 0, 8); // first: primitive type, second: start index, third: number of vertices
    int size = 0;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, nullptr);

    // unbind shader program
    this->_shaderProgram.disable();
}

void MyGLWindow::setupBuffer() {
    this->_shaderProgram.initFromFiles("src/resources/shader/simple.vert", "src/resources/shader/simple.frag");

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

    GLfloat cube_vertices[] = {
            // front
            -1.0, -1.0, 1.0,
            1.0, -1.0, 1.0,
            1.0, 1.0, 1.0,
            -1.0, 1.0, 1.0,
            // back
            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            1.0, 1.0, -1.0,
            -1.0, 1.0, -1.0,
    };

    GLfloat cube_colors[] = {
            // front colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
            // back colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
    };


    glGenVertexArrays(1, &vaoHandle); // create VAO
    glBindVertexArray(vaoHandle); // select this VAO and make it active
    // create VBO: position
    glGenBuffers(1, &vboPosition); // create VBO
    glBindBuffer(GL_ARRAY_BUFFER, vboPosition); // select this VBO and do something about it
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices) /*vertices*/, cube_vertices, GL_STATIC_DRAW); // copy data to VBO
    glVertexAttribPointer(
            0, // property or attribute index
            3, // number of components per vertex attribute
            GL_FLOAT, // data type
            GL_FALSE, // normalized?
            0, // stride
            nullptr // array buffer offset
    );
    glEnableVertexAttribArray(0); // enable this attribute index

    // create VBO: color
    glGenBuffers(1, &vboColor); // create VBO
    glBindBuffer(GL_ARRAY_BUFFER, vboColor); // select this VBO and do something about it
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors) /*colors*/, cube_colors, GL_STATIC_DRAW); // copy data to VBO*
    glVertexAttribPointer(
            1, // property or attribute index
            3, // number of components per vertex attribute
            GL_FLOAT, // data type
            GL_FALSE, // normalized?
            0, // stride
            nullptr // array buffer offset
    );
    glEnableVertexAttribArray(1); // enable this attribute index

    GLushort cube_elements[] = {
            0, 1, 2, 2, 3, 0, 1, 5, 6,
            6, 2, 1, 7, 6, 5, 5, 4, 7,
            4, 0, 3, 3, 7, 4, 4, 5, 1,
            1, 0, 4, 3, 2, 6, 6, 7, 3
    };
    GLuint ibo_cube_elements;
    glGenBuffers(1, &ibo_cube_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

    glBindVertexArray(0); // close the current VAO
}
