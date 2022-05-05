//
// Created by ebona on 05.05.2022.
//

#include "Time.hpp"


namespace ft
{
    Time* Time::m_instance = nullptr;

    void Time::init() {
        delete m_instance;
        m_instance = new Time();
        m_instance->m_startTime = glfwGetTime();
        std::cout << "Time initialized" << std::endl;
    }

    float Time::time() {
        ASSERT(m_instance != nullptr);
        return (float)m_instance->m_time;
    }

    float Time::deltaTime() {
        ASSERT(m_instance != nullptr);
        return (float)m_instance->m_deltaTime;
    }

    void Time::update() {
        ASSERT(m_instance != nullptr);
        double newTime = glfwGetTime() - m_instance->m_startTime;
        m_instance->m_deltaTime = newTime - m_instance->m_lastTime;
        m_instance->m_lastTime = m_instance->m_time;
        m_instance->m_time = newTime;
    }
}