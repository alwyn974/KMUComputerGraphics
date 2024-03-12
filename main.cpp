//
// Created by alwyn on 07/03/2024.
//

#include <iostream>

//#define _USE_MATH_DEFINES
//#include <cmath>

#include "core.h"

void cyclonePractice()
{
    // Move point p(1,4,-5) to vector v(5,1,4)
    cyclone::Vector3 p(1, 4, -5);
    cyclone::Vector3 v(5, 1, 4);
    p += v;

    std::cout << "p + v: " << p.toString() << std::endl;

    // Add vector v1(1,0,0) and vector v2(0,1,0)
    cyclone::Vector3 v1(1, 0, 0);
    cyclone::Vector3 v2(0, 1, 0);
    cyclone::Vector3 v3 = v1 + v2;

    std::cout << "v1 + v2: " << v3.toString() << std::endl;

    // Multiply v1(0,1,0) with scalar 5
    v1 = cyclone::Vector3(0, 1, 0);
    v1 *= 5;

    std::cout << "v1 * 5: " << v1.toString() << std::endl;

    // Get a vector v starting at (8,2,5) and ending at (1,-1,4)
    cyclone::Vector3 start(8, 2, 5);
    cyclone::Vector3 end(1, -1, 4);
    cyclone::Vector3 v4 = end - start;

    std::cout << "v4: " << v4.toString() << std::endl;

    // Normalize vector v(1,3,4)
    cyclone::Vector3 v5(1, 3, 4);
    v5.normalise();

    std::cout << "v5: " << v5.toString() << std::endl;
}

void dotProduct()
{
    const double DEGREES_TO_RADIAN = M_PI / 180.0f;
    const double RADIANS_TO_DEGREES = 180.0f / M_PI;
    cyclone::Vector3 v(2, -1, 1);
    cyclone::Vector3 u(1, 1, 2);
    float d = v.dot(u);
    float c = d / (u.magnitude() * v.magnitude());
    double deg = acos(c) * RADIANS_TO_DEGREES;

    std::cout << "Angle: " << deg << std::endl;
}

int main()
{
    dotProduct();
}