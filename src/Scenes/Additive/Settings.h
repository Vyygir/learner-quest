#ifndef SCENE_ADDITIVE_SETTINGS_H
#define SCENE_ADDITIVE_SETTINGS_H

#include <iostream>
#include "../../Scene.h"
#include "../../Utilities/Logger.h"
#include "../../UI/Elements.h"

using namespace UI;

namespace Scenes::Additive {
	class Settings : public Scene {
	public:
		void onLoad() override {
			Logger::log("Settings additive scene was loaded");

			addElement("WindowContainer", new UI::Box(
				{ 32, 32, 32, 128 },
				Scale{ 0.8f, 0.75f },
				Alignment{ HorizontalAlignment::Center, VerticalAlignment::Center }
			));
		}

		void onUpdate(float delta) override {
			getElement<UI::Box>("WindowContainer")->render();
		}
	};
}

#endif
