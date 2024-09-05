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
			this->ui->setBackgroundColor({ 79, 177, 229 });

			this->interactiveText = new UI::InteractiveText(
				"Atkinson",
				"This text should be clickable and change to red when the mouse is over it.",
				{ 255, 255, 255, 255 },
				24,
				{ HorizontalAlignment::Center, VerticalAlignment::Bottom },
				{ 1.0f, 1.0f },
				{ 0, -40 }
			);
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

			this->interactiveText->addMouseOverEvent(
				[](const SDL_MouseMotionEvent &event, UI::InteractiveText *element) {
					element->setColor({ 255, 0, 0, 255 });
				}
			);

			this->interactiveText->addMouseOutEvent(
				[](const SDL_MouseMotionEvent &event, UI::InteractiveText *element) {
					element->setColor({ 255, 255, 255, 255 });
				}
			);

			this->interactiveText->addClickEvent(
				[this](const SDL_MouseButtonEvent &event, UI::InteractiveText *element) {
					this->sceneManager->changeScene("Second");
				}
			);

			this->ui->addElementEventHandler(this->interactiveText);
			this->interactiveText->render();

			(new UI::Image(
				"assets/media/logo.png",
				Scale{ 0.0f, 0.12f },
				Alignment{ HorizontalAlignment::Center, VerticalAlignment::Top },
				true,
				{ 0, 100 }
			))->render();
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

		UI::InteractiveText* interactiveText;
	};
}

#endif
