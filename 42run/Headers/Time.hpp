//
// Created by ebona on 05.05.2022.
//

#ifndef TIME_HPP
#define TIME_HPP

#include "GlError.hpp"
#include <GLFW/glfw3.h>

#include <iostream>

namespace ft {
    class Time {
    private:
        static Time *m_instance;

        double m_time = 0;
        double m_deltaTime = 0;
        double m_startTime = 0;
        double m_lastTime = 0;

        Time() = default;

    public:
        Time(const Time&) = delete;
        Time& operator=(Time&) = delete;

        static void init();
        static float time();
        static float deltaTime();
        static void update();
    };
}

#endif //TIME_HPP
