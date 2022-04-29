//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#ifndef GLITTER_ENGINE_HPP
#define GLITTER_ENGINE_HPP

#include "Screen.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Primitives.hpp"
#include "Shader.hpp"

namespace ft {
    class Engine {
    private:
        std::string _name;

    protected:
        const std::shared_ptr<Screen> screen = std::make_shared<Screen>();
        const std::shared_ptr<Scene> scene = std::make_shared<Scene>();
        const std::shared_ptr<Shader> shader = std::make_shared<Shader>();

        virtual void start() {}

        virtual void update() {}

    public:
        Engine();
        virtual ~Engine() = default;

        void create(int screenWidth = Consts::DEFAULT_SCREEN_WIDTH,
                int screenHeight = Consts::DEFAULT_SCREEN_HEIGHT,
                const std::string &name = Consts::DEFAULT_PROJECT_NAME);

    };
}

#endif //GLITTER_ENGINE_HPP
