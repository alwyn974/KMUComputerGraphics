//
// Created by alwyn on 16/10/2023.
//

#include <array>
#include "MyGlWindow.hpp"

static float DEFAULT_VIEW_POINT[3] = {-0.25, 12, 34};
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

    const glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
    const glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
    const glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);

    const float aspect = static_cast<float>(width) / static_cast<float>(height);
    viewer = Viewer(viewPoint, viewCenter, upVector, 45.0f, aspect);

    this->initialize();
}

// #include "ParticleSystem.hpp"
//
// std::optional<ParticleSystem> particleSystem;

void MyGLWindow::initialize()
{
    this->_shaderProgramColor.initFromFiles("src/resources/shader/color/simple.vert", "src/resources/shader/color/simple.frag");
    this->_shaderProgramColor.addUniform("MVP"); // Projection * View * Model : mat4

    this->_shaderProgramLaserBeam.initFromFiles("src/resources/shader/color/simple.vert", "src/resources/shader/color/simple.frag");
    this->_shaderProgramLaserBeam.addUniform("MVP");

    _floor = CheckeredFloor(100, 10);
    _floor->init();

    // _teapot = VBOTeapot(64, glm::mat4(1.0f));
    //    _torus = VBOTorus(1.5f, 0.75f, 50, 50);

    //    _bunny = Bunny();

    // _bunnyTextured = BunnyTextured("src/resources/textures/bunny.png", "src/resources/textures/moss.png");
    //    _earth = Earth(1, 50, 50, "src/resources/textures/earth.jpg");

    // _ogre = Ogre("src/resources/textures/ogre_diffuse2.png", "src/resources/textures/ogre_normalmap2.png");

    // Create skybox
    /*const std::vector<std::string> faces = {
        "src/resources/textures/skybox/right.jpg",
        "src/resources/textures/skybox/left.jpg",
        "src/resources/textures/skybox/top.jpg",
        "src/resources/textures/skybox/bottom.jpg",
        "src/resources/textures/skybox/front.jpg",
        "src/resources/textures/skybox/back.jpg"
    };*/
    // _skybox = Skybox(/*faces*/);

    // particleSystem = ParticleSystem(1000);

    // _cow = Cow();
    // _sphere = Sphere(5, 50, 50);

    _cube = ColorCube(0.5, 0.5, 0.5);
    _cube->init();

    const float multiplier = 4;
    _laserBeam = LaserBeam(0.8f * multiplier, 0.1f * multiplier, 0.1f * multiplier, glm::vec3(0, 0, 1));
    _laserBeam->init();

//    _drawable = std::make_unique<LaserBeam>(0.8, 0.1, 0.1, glm::vec3(0, 0, 1));
//    _drawable->init();
}

glm::vec3 raycast(float mouseX, float mouseY, int width, int height, glm::mat4 projection, glm::mat4 view)
{
    // Convert from screen space to normalized device coordinates
    float x = (2.0f * mouseX) / width - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / height;

    // Start and end points in normalized device coordinates
    glm::vec4 rayStartNDC(x, y, -1.0f, 1.0f); // near plane
    glm::vec4 rayEndNDC(x, y, 1.0f, 1.0f); // far plane

    // Inverse projection matrix
    glm::mat4 invProjMatrix = glm::inverse(projection);

    // Convert points to eye space
    glm::vec4 rayStartEye = invProjMatrix * rayStartNDC;
    rayStartEye /= rayStartEye.w;
    glm::vec4 rayEndEye = invProjMatrix * rayEndNDC;
    rayEndEye /= rayEndEye.w;

    // Inverse view matrix
    glm::mat4 invViewMatrix = glm::inverse(view);

    // Convert points to world space
    glm::vec4 rayStartWorld = invViewMatrix * rayStartEye;
    glm::vec4 rayEndWorld = invViewMatrix * rayEndEye;

    // Calculate ray direction
    glm::vec3 rayDirWorld(rayEndWorld - rayStartWorld);
    rayDirWorld = glm::normalize(rayDirWorld);

    return rayDirWorld;
}

void MyGLWindow::draw(const float currentTime, const float deltaTime)
{
    // position, size
    glViewport(0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST); // enable depth testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    glm::vec3 eye = viewer->getViewPoint();
    glm::vec3 look = viewer->getViewCenter();
    glm::vec3 up = viewer->getUpVector();
    glm::mat4 view = lookAt(eye, look, up); // Calculate view matrix from paramters of viewer
    std::cout << glm::to_string(view) << std::endl;
    std::cout << glm::to_string(eye) << std::endl;
    std::cout << glm::to_string(look) << std::endl;
    std::cout << glm::to_string(up) << std::endl;
    std::cout <<" glm::to_string(viewer->getProjectionMatrix()) "<< std::endl;

    static std::string windowName = "Objects";
    static bool open = true;
    static bool drawPlane = true;
    static bool drawLaserBeam = true;

    ImGui::Begin(windowName.c_str(), &open, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Checkbox("Draw Plane", &drawPlane);

    glm::mat4 projection = perspective(45.0f, 1.0f * (float) _width / (float) _height, 0.1f, 10000.0f);
    if (drawPlane) {
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0, 0.0f));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));
        glm::mat4 model = translate * rotate * scale; // Combination of transformation matrix

        glm::mat4 mvp = projection * view * model;

        this->_shaderProgramColor.use();

        glUniformMatrix4fv(this->_shaderProgramColor.uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));
        if (_floor.has_value())
            _floor->draw();

        this->_shaderProgramColor.disable();
    }

    ImGui::Checkbox("Draw Laser Beam", &drawLaserBeam);
    if (drawLaserBeam) {
        glm::mat4 model = _laserBeam->getModelMatrix(); // Combination of transformation matrix

        glm::mat4 mvp = projection * view * model;

        _shaderProgramLaserBeam.use();

        glUniformMatrix4fv(this->_shaderProgramLaserBeam.uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

        {
            _laserBeam->imgui(windowName, ImGuiTreeNodeFlags_DefaultOpen);
            _laserBeam->update(currentTime, deltaTime);
            _laserBeam->draw();
        }

        _shaderProgramLaserBeam.disable();
    }
    ImGui::End();

    // particleSystem->updateParticles(delta); // Update the particles
    // particleSystem->renderParticles(mvp); // Render the particles

    // call shader program
    /*{
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.0, 0.0f));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), glm::vec3(1.0, 0.0, 0.0));
        if (spinning)
            spinAngle += rotationSpeed;
        spinAngle = std::fmod(spinAngle, 360.0f);
        glm::mat4 spin = glm::rotate(glm::mat4(1.0f), glm::radians(spinAngle), glm::vec3(0.0, 0.0, 1.0));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
        glm::mat4 model = translate * rotate * spin * scale; // Combination of transformation matrix

        glm::mat4 mView = view * model;
        glm::mat4 mvp = projection * view * model;

        glm::mat4 inverseMVP = glm::inverse(mView);
        glm::mat3 normalMatrix = glm::mat3(glm::transpose(inverseMVP)); // normal matrix

        this->_shaderProgramOgre.use();
        // draw

        glUniform4fv(this->_shaderProgramOgre.uniform("LightPosition"), 1, glm::value_ptr(lightPos));
        glUniform3fv(this->_shaderProgramOgre.uniform("LightIntensity"), 1, glm::value_ptr(lightIntensity));
        const MaterialColor color = {
            .ka = glm::vec3(0.3, 0.3, 0.3),
            .ks = glm::vec3(0.1, 0.1, 0.1),
            .shiness = 3.0f
        };
        MaterialColor::populateShaderProgram(this->_shaderProgramOgre, color, {
            {MaterialColor::Variable::Ka,      "Ka"},
            {MaterialColor::Variable::Ks,      "Ks"},
            {MaterialColor::Variable::Shiness, "Shiness"},
        });

        glUniformMatrix4fv(this->_shaderProgramOgre.uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(mView));
        glUniformMatrix3fv(this->_shaderProgramOgre.uniform("NormalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
        glUniformMatrix4fv(this->_shaderProgramOgre.uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

        if (_ogre.has_value()) {
            //            glUniform1i(this->_shaderProgramOgre.uniform("Tex1"), 0);
            _ogre->draw(this->_shaderProgramOgre);
        }
        /*if (_earth.has_value()) {
            glUniform1i(this->_shaderProgramBunnyTextured.uniform("Tex1"), 0);
            _earth->draw();
        }#1#
        //    if (_cube.has_value())
        //        _cube->draw();

        //        if (_teapot.has_value())
        //            _teapot->draw();

        //        if (_bunny.has_value())
        //            _bunny->draw();

        //        if (_sphere.has_value())
        //            _sphere->draw();

        // unbind shader program
        this->_shaderProgramOgre.disable();
    }*/

    /*{
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0, 0.0f));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
        glm::mat4 model = translate * rotate * scale; // Combination of transformation matrix

        glm::mat4 view2 = glm::mat4(glm::mat3(view));
        glm::mat4 mvp2 = projection * view2 * model;

        this->_shaderProgramSkybox.use();
        // draw
        glUniformMatrix4fv(this->_shaderProgramSkybox.uniform("ModelMatrix"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(this->_shaderProgramSkybox.uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp2));

        glUniform3fv(this->_shaderProgramSkybox.uniform("WorldCameraPosition"), 1, glm::value_ptr(eye));
        glUniform3fv(this->_shaderProgramSkybox.uniform("MaterialColor"), 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
        glUniform1f(this->_shaderProgramSkybox.uniform("ReflectFactor"), 0.2f);

        glDepthMask(GL_FALSE);
        if (_skybox.has_value())
            _skybox->draw(_shaderProgramSkybox);
        glDepthMask(GL_TRUE);

        if (_teapot.has_value()) {
            glUniform1i(_shaderProgramSkybox.uniform("DrawSkyBox"), GL_FALSE); //indicate that we are doing SKybox
            translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0, 0.0f));
            rotate = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), glm::vec3(1.0, 0.0, 0.0));
            scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
            model = translate * rotate * scale; // Combination of transformation matrix

            glm::mat4 mvp = projection * view * model;
            glUniformMatrix4fv(this->_shaderProgramSkybox.uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));
            _teapot->draw();
        }

        this->_shaderProgramSkybox.disable();
    }*/

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

glm::vec3 Vector3Unproject(glm::vec3 source, glm::mat4 projection, glm::mat4 view)
{
    glm::vec4 sourceVec4 = glm::vec4(source, 1.0f);

    glm::mat4 inverseMatrix = glm::inverse(projection * view);
    glm::vec4 unprojectedVec4 = inverseMatrix * sourceVec4;

    glm::vec3 unprojectedVec3 = glm::vec3(unprojectedVec4) / unprojectedVec4.w;

    return unprojectedVec3;
}

Ray MyGLWindow::getMouseRay(glm::mat4 view, mat4 projection)
{
    Ray ray = {};
    auto mouse = this->getMousePosition();

    // Calculate normalized device coordinates
    // NOTE: y value is negative
    float x = (2.0f * mouse.x) / (float) this->_width - 1.0f;
    float y = 1.0f - (2.0f * mouse.y) / (float) this->_height;
    float z = 1.0f;

    // Store values in a vector
    glm::vec3 deviceCoords = {x, y, z};

    // Unproject far/near points
    glm::vec3 nearPoint = Vector3Unproject((glm::vec3) {deviceCoords.x, deviceCoords.y, 0.0f}, projection, view);
    glm::vec3 farPoint = Vector3Unproject((glm::vec3) {deviceCoords.x, deviceCoords.y, 1.0f}, projection, view);

    // Unproject the mouse cursor in the near plane.
    // We need this as the source position because orthographic projects, compared to perspective doesn't have a
    // convergence point, meaning that the "eye" of the camera is more like a plane than a point.
    glm::vec3 cameraPlanePointerPos = Vector3Unproject(glm::vec3{deviceCoords.x, deviceCoords.y, -1.0f}, projection, view);

    // Calculate normalized direction vector
    glm::vec3 direction = glm::normalize(farPoint - nearPoint);

    ray.position = viewer->getViewPoint();
    // Apply calculated vectors to ray
    ray.direction = direction;

    return ray;
}
