//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>

#include "Buffer.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"

#include "Window.hpp"
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Primitives.hpp"
#include "Shader.hpp"
#include "Camera.hpp"


namespace ft {
    class Engine {
    private:
        std::string _name;

    protected:
        std::unique_ptr<Window> window = std::make_unique<Window>();
        std::unique_ptr<Renderer> renderer = std::unique_ptr<Renderer>();

        const std::shared_ptr<Scene> scene = std::make_shared<Scene>();
        const std::shared_ptr<Camera> camera = std::make_shared<Camera>();

        virtual void start() {}

        virtual void update() {}

        Engine() = default;

    public:
        explicit Engine(const std::string & name,
               int screenWidth = Consts::DEFAULT_WINDOW_WIDTH,
               int screenHeight = Consts::DEFAULT_WINDOW_HEIGHT);
        virtual ~Engine() = default;

        void loop();
    };
}

#endif //ENGINE_HPP
