//
// Created by ebona on 13.05.2022.
//

#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "glm/glm.hpp"

namespace ft {
    class RigidBody {
    public:
        RigidBody() : m_physicsOn(true), m_velocity(glm::vec3(0.0f, 0.0f, 0.0f)), m_acceleration(glm::vec3(0.0f, 0.0f, 0.0f)) {}
        void setAcceleration(const glm::vec3& acceleration);
        void addVelocity(const glm::vec3& velocity);
        void setVelocity(const glm::vec3& velocity);
        void updateVelocity(float deltaTime);

        glm::vec3 velocity() { return m_velocity; }

        void activatePhysics() { m_physicsOn = true; };
        void deactivatePhysics() { m_physicsOn = false; };
        bool isPhysicsOn() const { return m_physicsOn; }

    private:
        bool m_physicsOn;
        glm::vec3 m_velocity;
        glm::vec3 m_acceleration;

    };
}

#endif //RIGIDBODY_HPP
