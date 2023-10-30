#include <iostream>

#include <glm/gtx/string_cast.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glfw/glfw3.h>
#include <format>

const double DEGREES_TO_RADIANS = glm::pi<float>() / 180;
const double RADIANS_TO_DEGREES = 180.0 / glm::pi<float>();

glm::mat4 perspective(float aspect, float fovy, float nearZ, float farZ);

int main() {
    // create simple window
     glfwInit();
     GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
     glfwMakeContextCurrent(window);

     // print OpenGL version
     std::cout << glGetString(GL_VERSION) << std::endl;
     while (!glfwWindowShouldClose(window)) {
         // clear screen
         glClear(GL_COLOR_BUFFER_BIT);

         // draw triangle
         glBegin(GL_TRIANGLES);
         glVertex2f(-0.5f, -0.5f);
         glVertex2f( 0.0f,  0.5f);
         glVertex2f( 0.5f, -0.5f);
         glEnd();

         // swap buffers
         glfwSwapBuffers(window);

         // poll events
         glfwPollEvents();
     }

//    // Move Point p(1,4, 5) by vector v(5,1,4).
//    glm::vec3 p(1, 4, 5);
//    glm::vec3 v(5, 1, 4);
//    glm::vec3 result = p + v;
//    std::cout << glm::to_string(result) << std::endl;
//
//    // Add vector v1(1,0,0) and vector v2(0,1,0)
//    glm::vec3 v1(1, 0, 0);
//    glm::vec3 v2(0, 1, 0);
//    glm::vec3 result2 = v1 + v2;
//    std::cout << glm::to_string(result2) << std::endl;
//
//    // Multiply v1(0,1,0) with scalar 5.
//    glm::vec3 result3 = v1 * 5.0f;
//    std::cout << glm::to_string(result3) << std::endl;
//
//    // Get a vector v starting at (8,2,5) and ending at (1,-1,4)
//    glm::vec3 v3(8, 2, 5);
//    glm::vec3 v4(1, -1, 4);
//    glm::vec3 result4 = v4 - v3;
//    std::cout << glm::to_string(result4) << std::endl;
//
//    // Normalize vector v(1,3,4).
//    glm::vec3 v5(1, 3, 4);
//    glm::vec3 result5 = glm::normalize(v5);
//    std::cout << glm::to_string(result5) << std::endl;

//    glm::vec3 v(2, -1, 1);
//    glm::vec3 u(1, 1, 2);
//
//    float d = glm::dot(v, u);
//    float c = d / (glm::length(u) * glm::length(v));
//    double deg = glm::degrees(glm::acos(c));
//    std::cout << std::format("Angle: {}", deg) << std::endl;

//    glm::vec3 u(1, 0, 0);
//    glm::vec3 v(-1, 1, 0); // Let's test |a| * |b| * sin(theta)
//
//    glm::vec3 c = glm::cross(u, v);
//
//    float l = glm::length(c);
//    float ang = glm::acos(glm::dot(u, v) / (glm::length(u) * glm::length(v)));
//    std::cout << std::format("Area: {}", l) << std::endl;
//
//    float l2 = glm::length(u) * glm::length(v) * glm::sin(ang); // l == l2
//    std::cout << std::format("Area: {}", l2) << std::endl;
//
//    glm::vec3 u2(1, 0, 0);
//    glm::vec3 v2(0, 1, 0); // Let's test the area of parallelogram
//    float area = glm::length(glm::cross(u2, v2));
//    std::cout << std::format("Area: {}", area) << std::endl;
//
//    glm::vec3 u3(1, 0, 0);
//    glm::vec3 v3(1, 0, 0); // Let's test when two vectors are parallel
//    float area2 = glm::length(glm::cross(u3, v3));
//    std::cout << std::format("Area: {}", area2) << std::endl;

//    glm::vec3 p1(1.0f, 0.0f, 0.0f);
//    glm::vec3 p2(1.0f, 1.0f, 0.0f);
//    glm::vec3 p3(-1.0f, 0.0f, 0.0f);
//
//    glm::vec3 v1 = p2 - p1;
//    glm::vec3 v2 = p3 - p1;
//
//    float area = glm::length(glm::cross(v1, v2)) / 2.0f;
//    std::cout << "Area of triangle: " << area << std::endl;

//    glm::vec3 p1(3, 0, 0);
//    glm::vec3 p2(1.5, 0.86, 0);
//    glm::vec3 p3(3, 0, -1);
//
//    glm::vec3 v1 = p2 - p1;
//    glm::vec3 v2 = p3 - p1;
//
//    glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
//    std::cout << "Normal: " << glm::to_string(normal) << std::endl;

//    glm::vec4 v1(1, 0, 1, -1);
//    glm::vec4 v2(1, 0, 1, -1);
//    glm::vec4 v3(1, 0, 1, -1);
//    glm::vec4 v4(1, 0, 1, -1);
//
//    glm::mat4 m(v1, v2, v3, v4);
////    glm::mat4 m = {
////            {1, 0, 1, -1}, // column 1
////            {1, 0, 1, -1}, // column 2
////            {1, 0, 1, -1}, // column 3
////            {1, 0, 1, -1} // column 4
////    };
//    std::cout << glm::to_string(m) << std::endl;

//    glm::mat2 m2 = {1, 0, 1, 1};
//    std::cout << to_string(m2) << std::endl;
//    glm::mat3x2 m3 = {{1, 0},
//                      {1, 1},
//                      {0, 1}};
//    std::cout << to_string(m3) << std::endl;
//    glm::mat4 m(1.0f); // identity matrix
//    std::cout << to_string(m) << std::endl;
//    std::cout << m[1][2] << std::endl;

//    glm::mat2 m1 = { 1, 0, 1, 1 };
//    glm::mat2 m2 = { 0, 1, 1, 0 };
//    glm::mat2 m3 = m1 + m2;
//    std::cout << to_string (m3) << std::endl;

//    glm::mat3 a({{1,  0, 2},
//                 {1,  2, 3},
//                 {-1, 0, 1}});
//    glm::mat3 b({{1, 0,  0},
//                 {0, -1, 1},
//                 {0, 1,  2}});
//    std::cout << to_string(a * b) << std::endl;
//    std::cout << to_string(b * a) << std::endl;
//
//    glm::mat2x2 m2x2 = {{0.f, 1.f},
//                        {1.f, 0.f}};
//
//    glm::mat3x2 m3x2 = {{1.0f, 0.0f},
//                        {1.0f, -1.0f},
//                        {0.0f, 1.0f}};
//    std::cout << to_string(m3x2) << std::endl;
//
//    glm::mat3x2 aze(1, 2, 3, 4, 5, 6);

//    auto m = m3x2 * m2x2;

//    glm::vec3 v(5, 6, 1);
//    glm::mat3 t(1); // identity matrix
////    t = glm::translate(t, glm::vec2(2, 3));
////    t = glm::scale(t, glm::vec2(3, 4)); // scale 3x in x axis and 4x in y axis
//    t = glm::rotate(t, glm::radians(45.0f)); // rotate 45 degrees
//
//    v = t * v;
//
//    std::cout << glm::to_string(t) << std::endl;
//    std::cout << glm::to_string(v) << std::endl;

//    glm::mat3 t(1); // identity matrix
//    t = glm::translate(t , glm::vec2(3, 4));
//    t = glm::rotate(t, glm::radians(-45.0f));
//    t = glm::scale(t, glm::vec2(2, 2));
//
//    std::cout << glm::to_string(t) << std::endl;
//
//    glm
//    mat3 o (
//            glm
//    mat3 s = glm scale o , glm vec2 (2,
//                                     glm
//    mat3 r = glm rotate o , 45.0f);
//    glm
//    mat3 tr = glm translate o , glm vec2 (3,
//                                          glm
//    mat3 composite = tr * r * s
//    std
//    cout << to_string composite ) << std endl

//    glm::vec3 p(2, 2, 1);
//    glm::vec3 q(1, -2, 0); // Let's test |a| * |b| * sin(theta)
//
//    float c = glm::dot(p, q);
//    glm::vec3 cross = glm::cross(p, q);
//    std::cout << std::format("Dot product: {}", c) << std::endl;
//    std::cout << std::format("Cross product: {}", glm::to_string(cross)) << std::endl;

//    glm::vec3 campos(5, 5, 5);
//    glm::vec3 look(0, 0, 0);
//    glm::vec3 up(0, 1, 0);
//    auto mat = lookAt(campos, look, up);
//    std::cout << glm::to_string(mat) << std::endl;

//    int width = 780;
//    int height = 750;
//    float fovy = 45.0f;
//    float nearZ = 0.1f;
//    float farZ = 500.0f;
//    float aspect = (float) width / (float) height;
//    auto mat = perspective(aspect, fovy, nearZ, farZ);
//    std::cout << glm::to_string(mat) << std::endl;

    return 0;
}

glm::mat4 lookAt(glm::vec3 campos, glm::vec3 look, glm::vec3 up) {
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

glm::mat4 perspective(float aspect, float fovy, float nearZ, float farZ)
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