#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "core.h"

class Mover {

public:

    float size;
    cyclone::Vector3 m_position;
    cyclone::Vector3 m_velocity;

    Mover()
    {
        size = 1.0f;
        m_position = cyclone::Vector3(3, 1, 0);
        m_velocity = cyclone::Vector3(5, 0, 0);
    };

    void update(float duration)
    {
        m_position += m_velocity * duration;

        if (m_position.x > 100)
            m_position.x = 0;
    }

    void stop()
    {
    }

    void draw(int shadow)
    {
        if (shadow)
            glColor3f(0.1f, 0.1f, 0.1f);
        else
            glColor3f(1.0, 0, 0);

        glPushMatrix();
        glTranslated(m_position.x, m_position.y, m_position.z);
        glutSolidSphere(size, 30, 30);
        glPopMatrix();
    }
};

