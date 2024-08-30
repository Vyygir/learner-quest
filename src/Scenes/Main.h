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
            this->ui->addImage(
                "assets/media/logo.png",
                Scale{ 0.75f, 0.75f },
                { HorizontalAlignment::Center, VerticalAlignment::Top },
                { 0, 100 }
            );

            this->ui->addText("Atkinson Bold", "This is some extra long text that should be very readable.", { 255, 255, 255, 255}, 36, { HorizontalAlignment::Center, VerticalAlignment::Center });
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
