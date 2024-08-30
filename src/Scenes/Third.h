#ifndef SCENE_THIRD_H
#define SCENE_THIRD_H

#include <iostream>
#include "../Scene.h"
#include "../Utilities/Logger.h"

namespace Scenes {
    class Third : public Scene {
    public:
        void onLoad() override {
            Logger::log("Third scene has been loaded");
        }

        void onUpdate(float delta) override {
            this->ui->addText("crang", "Third Scene", {255, 255, 255, 255}, 32, { HorizontalAlignment::Center, VerticalAlignment::Center });
        }

        void onExit() override {
            Logger::log("Third scene has been exited");
        }
    };
}

#endif
