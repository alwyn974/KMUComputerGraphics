//
// Created by alwyn on 07/03/2024.
//

#include <iostream>

//#define _USE_MATH_DEFINES
//#include <cmath>

#include "core.h"

int main()
{
    cyclone::Vector3 p(1, 4, -5);
    cyclone::Vector3 v(5, 1, 4);

    std::cout << "pv " << (v + p).toString() << std::endl;
}