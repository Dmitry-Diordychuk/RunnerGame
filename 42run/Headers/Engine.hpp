//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Pointer.hpp"
#include "Window.hpp"
#include "Time.hpp"

#include "GameObject.hpp"

//#include "Buffer.hpp"
//#include "VertexArray.hpp"
//#include "Texture.hpp"
//#include "Transform.hpp"
//
//
#include "Renderer.hpp"

//#include "Model.hpp"


#include "Scene.hpp"
//#include "Primitives.hpp"
//#include "Shader.hpp"
//#include "Camera.hpp"


namespace ft {
    using namespace std;

    class Engine {
    private:
        string _name;

    protected:
        Scope<EventHandler> eventHandler = make_unique<EventHandler>();
        Scope<Window> window = make_unique<Window>();
        Scope<Renderer> renderer = unique_ptr<Renderer>();
        Scope<Time> time = unique_ptr<Time>();

        const Ref<Scene> scene = make_shared<Scene>();
        const Ref<Camera> camera = make_shared<Camera>();

        virtual void start() {}

        virtual void update() {}

        virtual void onKeyEvent(Ref<Event>&) {}

        virtual void onWindowEvent(Ref<Event>&) {}

        Engine() = default;

    public:
        explicit Engine(const string & name,
               int screenWidth = Consts::DEFAULT_WINDOW_WIDTH,
               int screenHeight = Consts::DEFAULT_WINDOW_HEIGHT);
        virtual ~Engine() = default;

        void loop();
    };
}

#endif //ENGINE_HPP
