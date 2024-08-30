#ifndef SCENE_SECOND_H
#define SCENE_SECOND_H

#include <iostream>
#include "../Scene.h"
#include "../Utilities/Logger.h"

namespace Scenes {
    class Second : public Scene {
    public:
        void onLoad() override {
            Logger::log("Second scene has been loaded");
        }

        void onUpdate(float delta) override {
            this->ui->addText("crang", "Second Scene", {255, 255, 255, 255}, 32, { 0, 0 }, { HorizontalAlignment::Center, VerticalAlignment::Center });
        }

        void onExit() override {
            Logger::log("Second scene has been exited");
        }
    };
}

#endif
