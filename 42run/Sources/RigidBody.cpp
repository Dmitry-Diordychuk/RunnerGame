//
// Created by ebona on 13.05.2022.
//

#include "RigidBody.hpp"

namespace ft
{

    void RigidBody::setAcceleration(const glm::vec3 &acceleration) {
        m_acceleration = acceleration;
    }

    void RigidBody::addVelocity(const glm::vec3 &velocity) {
        m_velocity += velocity;
    }

    void RigidBody::setVelocity(const glm::vec3 &velocity) {
        m_velocity = velocity;
    }

    void RigidBody::updateVelocity(float deltaTime) {
        addVelocity(m_acceleration * deltaTime);
    }
}