#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include <iostream>
#include "../Scene.h"
#include "../Utilities/Logger.h"
#include "../UI/Elements.h"

using namespace UI;

namespace Scenes {
	class Main : public Scene {
	public:
		void onLoad() override {
			Interface::getInstance().setBackgroundColor({ 79, 177, 229 });
//			this->ui->setBackgroundColor({ 79, 177, 229 });
		}

		void onUpdate(float delta) override {
			(new UI::RepeatableImage(
				"assets/media/menu/background.png",
				true,
				false,
				Scale{ 0.0f, 0.55f },
				Alignment{ HorizontalAlignment::Left, VerticalAlignment::Top },
				this->backgroundOffset,
				true
			))->render();

			this->backgroundOffset = { this->backgroundOffset.x - 1, 0 };

			(new UI::Text(
				"Atkinson",
				"This is some extra long text that should be very readable.",
				{ 255, 255, 255, 255 },
				36,
				{ HorizontalAlignment::Center, VerticalAlignment::Center }
			))->render();

			(new UI::Image(
				"assets/media/logo.png",
				Scale{ 0.0f, 0.12f },
				Alignment{ HorizontalAlignment::Center, VerticalAlignment::Top },
				true,
				{ 0, 100 }
			))->render();

//			this->ui->addInteractableText(
//				"Atkinson",
//				"Hoverable Text",
//				{ 255, 255, 255 },
//				{ 255, 0, 0 },
//				24,
//				{ HorizontalAlignment::Center, VerticalAlignment::Bottom },
//				{ 0, -150 },
//				[]() {
//					Logger::log("Clicked");
//				}
//			);
		}

		void onMouseMove(SDL_MouseMotionEvent event) override {
//            Logger::log("User is moving the mouse");
		}

		void onMouseButton(SDL_MouseButtonEvent event) override {
//			Logger::log("User has submitted mouse button input");
//
//			if (event.button == SDL_BUTTON_LEFT) {
//				Logger::log("User has left clicked");
//			}
//
//			if (event.button == SDL_BUTTON_RIGHT) {
//				Logger::log("User has right clicked");
//			}
		}

		void onExit() override {
//			Logger::log("Main scene has been exited");
		}

	private:
		Offset backgroundOffset = { -100, 0 };
	};
}

#endif
