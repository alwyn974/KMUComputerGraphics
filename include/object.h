#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "core.h"
#include "particle.h"

class Mover {

public:

    float size;
    cyclone::Vector3 m_position;
    cyclone::Vector3 m_velocity;

    cyclone::Particle *m_particle;
    cyclone::Vector3 wind;

    Mover()
    {
        size = 1.0f;
        m_position = cyclone::Vector3(3, 1, 0);
        m_velocity = cyclone::Vector3(5, 0, 0);

        wind = cyclone::Vector3(1, 0, 0);

        m_particle = new cyclone::Particle();
        m_particle->setPosition(5, 2, 0);  //initial pos
//        m_particle->setVelocity(0, 0, 0); //initial vel
//        m_particle->setMass(1.0f); //mass
//        m_particle->setDamping(0.99f); //damping
//        m_particle->setAcceleration(cyclone::Vector3::GRAVITY);  //initial acc.

        //Laser
//        m_particle->setMass(0.1f);
//        m_particle->setVelocity(0, 0, 100);
//        m_particle->setAcceleration(0, 0, 0);
//        m_particle->setDamping(0.99f);

        //Fireball
        m_particle->setMass(1.0f); // 1.0kg - mostly blast damage
        m_particle->setVelocity(0.0f, 0.0f, 10.0f); // 5m/s
        m_particle->setAcceleration(0.0f, 0.6f, 0.0f); // Floats up
        m_particle->setDamping(0.9f);

        //Artillery
//        m_particle->setMass(200.0f); // 200.0kg
//        m_particle->setVelocity(0.0f, 30.0f, 40.0f); // 50m/s
//        m_particle->setAcceleration(0.0f, -20.0f, 0.0f);
//        m_particle->setDamping(0.99f);

        //Pistol
//        m_particle->setMass(2.0f); // 2.0kg
//        m_particle->setVelocity(0.0f, 0.0f, 35.0f); // 35m/s
//        m_particle->setAcceleration(0.0f, -1.0f, 0.0f);
//        m_particle->setDamping(0.99f);
    };

    void checkEdges()
    {
        cyclone::Vector3 pos;
        m_particle->getPosition(&pos);

        if (pos.y <= size) {
            pos.y = size;
            m_particle->setPosition(pos);

            cyclone::Vector3 vel;
            m_particle->getVelocity(&vel);
            vel.y = -vel.y;
            m_particle->setVelocity(vel);
        }
        // build invisible wall in x 100
        if (pos.x >= 100) {
            pos.x = 100;
            m_particle->setPosition(pos);

            cyclone::Vector3 vel;
            m_particle->getVelocity(&vel);
            vel.x = -vel.x;
            m_particle->setVelocity(vel);
        }
    }

    void update(float duration)
    {
//        m_particle->addForce(wind);
        m_particle->integrate(duration);
//        checkEdges();  // Make this function to check collision
    }

    void stop()
    {
    }

    void draw(int shadow)
    {
        cyclone::Vector3 position;
        m_particle->getPosition(&position); //get the current pos of particle

        if (shadow)
            glColor3f(0.1f, 0.1f, 0.1f);
        else
            glColor3f(1.0, 0, 0);

        glPushMatrix();
        {
            glTranslatef(position.x, position.y, position.z);
            //            glTranslated(m_position.x, m_position.y, m_position.z);
            glutSolidSphere(size, 30, 30);
        }
        glPopMatrix();
    }
};

