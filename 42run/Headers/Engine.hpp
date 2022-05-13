//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>

#include "Buffer.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

#include "Window.hpp"
#include "Renderer.hpp"
#include "Time.hpp"
#include "Model.hpp"
#include "Event.hpp"

#include "GameObject.hpp"
#include "Scene.hpp"
#include "Primitives.hpp"
#include "Shader.hpp"
#include "Camera.hpp"


namespace ft {
    template <typename T>
    using Ref = std::shared_ptr<T>;

    template <typename T>
    using Scop = std::unique_ptr<T>;

    class Engine {
    private:
        std::string _name;

    protected:
        Scop<EventHandler> eventHandler = std::make_unique<EventHandler>();
        Scop<Window> window = std::make_unique<Window>();
        Scop<Renderer> renderer = std::unique_ptr<Renderer>();
        Scop<Time> time = std::unique_ptr<Time>();

        const Ref<Scene> scene = std::make_shared<Scene>();
        const Ref<Camera> camera = std::make_shared<Camera>();

        virtual void start() {}

        virtual void update() {}

        virtual void onKeyEvent(std::shared_ptr<Event>&) {}

        virtual void onWindowEvent(std::shared_ptr<Event>&) {}

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
