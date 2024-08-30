#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include <iostream>
#include "../Scene.h"
#include "../Utilities/Logger.h"

namespace Scenes {
    class Main : public Scene {
    public:
        void onLoad() override {
            Logger::log("Main scene has been loaded");
        }

        void onUpdate(float delta) override {
            this->ui->addText("crang", "Main Scene", {255, 255, 255, 255}, 32, 0, 0, HorizontalAlignment::Center, VerticalAlignment::Center);
        }

        void onMouseMove(SDL_MouseMotionEvent event) override {
//            Logger::log("User is moving the mouse");
        }

        void onMouseButton(SDL_MouseButtonEvent event) override {
            Logger::log("User has submitted mouse button input");

            if (event.button == SDL_BUTTON_LEFT) {
                Logger::log("User has left clicked");
            }

            if (event.button == SDL_BUTTON_RIGHT) {
                Logger::log("User has right clicked");
            }
        }

        void onExit() override {
            Logger::log("Main scene has been exited");
        }
    };
}

#endif
