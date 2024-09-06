#ifndef SCENE_THIRD_H
#define SCENE_THIRD_H

#include <iostream>
#include "../Scene.h"
#include "../Utilities/Logger.h"

namespace Scenes {
	class Third : public Scene {
	public:
		void onLoad() override {
			this->ui->setBackgroundColor({ 0, 0, 0 });

			addElement("TestText", new UI::Text(
				"Atkinson",
				"This is the third scene",
				{ 255, 255, 255, 255 },
				36,
				{ HorizontalAlignment::Center, VerticalAlignment::Center }
			));
		}

		void onUpdate(float delta) override {
			getElement<UI::Text>("TestText")->render();
		}

		void onExit() override {
//			Logger::log("Third scene has been exited");
		}
	};
}

#endif
