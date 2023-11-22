//
// Created by alwyn on 16/10/2023.
//

#include <array>
#include "MyGlWindow.hpp"
#include "Cow.hpp"

static float DEFAULT_VIEW_POINT[3] = {5, 5, 5};
static float DEFAULT_VIEW_CENTER[3] = {0, 0, 0};
static float DEFAULT_UP_VECTOR[3] = {0, 1, 0};
struct Color {
    GLfloat shiness;
    glm::vec3 Ka;
    glm::vec3 Kd;
    glm::vec3 Ks;
};
static Color emerald = {
    76.8,
    glm::vec3(0.0215, 0.1745, 0.0215),
    glm::vec3(0.07568, 0.61424, 0.07568),
    glm::vec3(0.633, 0.727811, 0.633)
};
static Color ruby = {
    76.8,
    glm::vec3(0.1745, 0.01175, 0.01175),
    glm::vec3(0.61424, 0.04136, 0.04136),
    glm::vec3(0.727811, 0.626959, 0.626959)
};

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

GLuint vaoHandle;

void MyGLWindow::initialize()
{
    //    this->_shaderProgram.initFromFiles("src/resources/shader/lightning/phong.vert", "src/resources/shader/lightning/phong.frag");
    this->_shaderProgramFloor.initFromFiles("src/resources/shader/cube/simple.vert", "src/resources/shader/cube/simple.frag");
    this->_shaderProgramTeapot.initFromFiles("src/resources/shader/lightning/phong_in_frag.vert", "src/resources/shader/lightning/phong_in_frag.frag");
    this->_shaderProgramTorus.initFromFiles("src/resources/shader/lightning/phong_in_frag.vert", "src/resources/shader/lightning/phong_in_frag.frag");

    //    this->_shaderProgram.addUniform("model");
    //    this->_shaderProgram.addUniform("view");
    //    this->_shaderProgram.addUniform("projection");
    //    this->_shaderProgram.addUniform("LightLocation"); // Light Position : vec4
    //    this->_shaderProgram.addUniform("Kd"); // Diffuse Object Color :vec3
    //    this->_shaderProgram.addUniform("Ld"); // Diffuse Light Color : vec3
    const std::array<ShaderProgram *, 2> shaderPrograms = {&_shaderProgramTeapot, &_shaderProgramTorus};
    for (const auto &shaderProgram: shaderPrograms) {
        shaderProgram->addUniform("LightPosition");
        shaderProgram->addUniform("LightIntensity");
        shaderProgram->addUniform("Ka");
        shaderProgram->addUniform("Kd");
        shaderProgram->addUniform("Ks");
        shaderProgram->addUniform("shiness");

        shaderProgram->addUniform("ModelViewMatrix"); // View*Model : mat4
        shaderProgram->addUniform("NormalMatrix"); // Refer next slide : mat3
        shaderProgram->addUniform("MVP"); // Projection * View * Model : mat4
    }

    this->_shaderProgramFloor.addUniform("MVP"); // Projection * View * Model : mat4

    /*std::vector<glm::vec3> normals(1732); //# of vertices 1732 -> # of normal 1732
    std::vector<int> meanNormals(1732); // counter for mean normal
    for (int i = 0; i < 1732; i++) {
        const glm::vec3 &v0 = vertices[nvertices[i * 3]]; // 1st vertex
        const glm::vec3 &v1 = vertices[nvertices[i * 3 + 1]]; // 2nd vertex
        const glm::vec3 &v2 = vertices[nvertices[i * 3 + 2]]; // 3rd vertex
        glm::vec3 n = glm::cross((v1 - v0), (v2 - v0)); // Cross product
        n = glm::normalize(n);
        normals[nvertices[i * 3]] += n; //Set the same normal to each vertex
        meanNormals[nvertices[i * 3]]++;
        normals[nvertices[i * 3 + 1]] += n;
        meanNormals[nvertices[i * 3 + 1]]++;
        normals[nvertices[i * 3 + 2]] += n;
        meanNormals[nvertices[i * 3 + 2]]++;
    }
    for (const auto &item: meanNormals)
        normals[item] /= item;

    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    GLuint vboVertices;
    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
        0, // attribute
        3, // number of elements per vertex, here (x,y,z)
        GL_FLOAT, // type of each element
        GL_FALSE, // take our values as-is
        0, // stride
        nullptr // array buffer offset
    );
    glEnableVertexAttribArray(0);

    GLuint vboNormals;
    glGenBuffers(1, &vboNormals);
    glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(
        1, // attribute
        3, // number of elements per vertex, here (x,y,z)
        GL_FLOAT, // type of each element
        GL_FALSE, // take our values as-is
        0, // stride
        nullptr // array buffer offset
    );
    glEnableVertexAttribArray(1);

    GLuint iboElements;
    glGenBuffers(1, &iboElements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboElements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(nvertices), &nvertices, GL_STATIC_DRAW);

    glBindVertexArray(0);*/

    _floor = CheckeredFloor(100, 10);

    _teapot = VBOTeapot(64, glm::mat4(1.0f));
    _torus = VBOTorus(1.5f, 0.75f, 50, 50);

    //    _cube = ColorCube(_width, _height);
}

void MyGLWindow::draw()
{
    // position, size
    glViewport(0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST); // enable depth testing
//    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    //    GLfloat shiness = 10;
    //    glm::vec3 Ka(0.3, 0.3, 0.3);
    //    glm::vec3 Kd(0.9, 0.9, 0.9);
    //    glm::vec3 Ks(0.2, 0.2, 0.2);

    //    glm::vec4 lightPos(50, 50, 50, 1); // light position
    //    glm::vec3 Kd(1, 1, 0); // Diffuse Object Color
    //    glm::vec3 Ld(1, 1, 1); // Diffuse Light Color
    glm::vec4 lightPos(10, 10, 0, 1);
    glm::vec3 lightIntensity(0.9, 0.9, 0.9);

    {
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0, 0.0f));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
        glm::mat4 model = translate * rotate * scale; // Combination of transformation matrix

        glm::vec3 eye = viewer->getViewPoint();
        glm::vec3 look = viewer->getViewCenter();
        glm::vec3 up = viewer->getUpVector();
        glm::mat4 view = lookAt(eye, look, up); // Calculate view matrix from paramters of viewer

        glm::mat4 projection = perspective(45.0f, 1.0f * (float) _width / (float) _height, 0.1f, 500.0f);
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

    // call shader program
    {
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0, 0.0f));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
        glm::mat4 model = translate * rotate * scale; // Combination of transformation matrix

        glm::vec3 eye = viewer->getViewPoint();
        glm::vec3 look = viewer->getViewCenter();
        glm::vec3 up = viewer->getUpVector();
        glm::mat4 view = lookAt(eye, look, up); // Calculate view matrix from paramters of viewer

        glm::mat4 projection = perspective(45.0f, 1.0f * (float) _width / (float) _height, 0.1f, 500.0f);
        glm::mat4 mView = view * model;
        glm::mat4 mvp = projection * view * model;

        glm::mat4 inverseMVP = glm::inverse(mView);
        glm::mat3 normalMatrix = glm::mat3(glm::transpose(inverseMVP)); // normal matrix

        this->_shaderProgramTeapot.use();
        // draw

        glUniform4fv(this->_shaderProgramTeapot.uniform("LightPosition"), 1, glm::value_ptr(lightPos));
        glUniform3fv(this->_shaderProgramTeapot.uniform("LightIntensity"), 1, glm::value_ptr(lightIntensity));
        glUniform3fv(this->_shaderProgramTeapot.uniform("Ka"), 1, glm::value_ptr(emerald.Ka));
        glUniform3fv(this->_shaderProgramTeapot.uniform("Kd"), 1, glm::value_ptr(emerald.Kd));
        glUniform3fv(this->_shaderProgramTeapot.uniform("Ks"), 1, glm::value_ptr(emerald.Ks));
        glUniform1fv(this->_shaderProgramTeapot.uniform("shiness"), 1, &emerald.shiness);

        glUniformMatrix3fv(this->_shaderProgramTeapot.uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(mView));
        glUniformMatrix3fv(this->_shaderProgramTeapot.uniform("NormalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniformMatrix4fv(this->_shaderProgramTeapot.uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

        //    if (_cube.has_value())
        //        _cube->draw();

        if (_teapot.has_value())
            _teapot->draw();

        // draw cow - start
        /*glBindVertexArray(vaoHandle);
        int size;
        glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
        glDrawElements(GL_TRIANGLES, size / sizeof(glm::uint32), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);*/
        // draw cow - end

        // unbind shader program
        this->_shaderProgramTeapot.disable();
    }

    {
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.5f, 0.0f));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
        glm::mat4 model = translate * rotate * scale; // Combination of transformation matrix

        glm::vec3 eye = viewer->getViewPoint();
        glm::vec3 look = viewer->getViewCenter();
        glm::vec3 up = viewer->getUpVector();
        glm::mat4 view = lookAt(eye, look, up); // Calculate view matrix from paramters of viewer

        glm::mat4 projection = perspective(45.0f, 1.0f * (float) _width / (float) _height, 0.1f, 500.0f);
        glm::mat4 mView = view * model;
        glm::mat4 mvp = projection * view * model;

        glm::mat4 inverseMVP = glm::inverse(mView);
        glm::mat3 normalMatrix = glm::mat3(glm::transpose(inverseMVP)); // normal matrix

        this->_shaderProgramTorus.use();

        glUniform4fv(this->_shaderProgramTorus.uniform("LightPosition"), 1, glm::value_ptr(lightPos));
        glUniform3fv(this->_shaderProgramTorus.uniform("LightIntensity"), 1, glm::value_ptr(lightIntensity));
        glUniform3fv(this->_shaderProgramTorus.uniform("Ka"), 1, glm::value_ptr(ruby.Ka));
        glUniform3fv(this->_shaderProgramTorus.uniform("Kd"), 1, glm::value_ptr(ruby.Kd));
        glUniform3fv(this->_shaderProgramTorus.uniform("Ks"), 1, glm::value_ptr(ruby.Ks));
        glUniform1fv(this->_shaderProgramTorus.uniform("shiness"), 1, &ruby.shiness);

        glUniformMatrix3fv(this->_shaderProgramTorus.uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(mView));
        glUniformMatrix3fv(this->_shaderProgramTorus.uniform("NormalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniformMatrix4fv(this->_shaderProgramTorus.uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

        if (_torus.has_value())
            _torus->draw();

        this->_shaderProgramTorus.disable();
    }
}
