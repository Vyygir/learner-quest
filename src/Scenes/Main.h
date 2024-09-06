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

			addElement("CloudBackground", new UI::RepeatableImage(
				"assets/media/menu/background.png",
				true,
				false,
				Scale{ 0.0f, 0.55f },
				Alignment{ HorizontalAlignment::Left, VerticalAlignment::Top },
				this->backgroundOffset,
				true
			));

			addElement("Logo", new UI::Image(
				"assets/media/logo.png",
				Scale{ 0.0f, 0.12f },
				Alignment{ HorizontalAlignment::Center, VerticalAlignment::Top },
				true,
				{ 0, 100 }
			));

			addElement("ExampleLabel", new UI::Text(
				"Atkinson",
				"This is some extra long text that should be very readable.",
				{ 255, 255, 255, 255 },
				36,
				{ HorizontalAlignment::Center, VerticalAlignment::Center }
			));

			auto* exampleInteractiveText = new UI::InteractiveText(
				"Atkinson",
				"This text should be clickable and change to red when the mouse is over it.",
				{ 255, 255, 255, 255 },
				24,
				{ HorizontalAlignment::Center, VerticalAlignment::Bottom },
				{ 1.0f, 1.0f },
				{ 0, -40 }
			);

			this->ui->addElementEventHandler(exampleInteractiveText);
			addElement("ExampleInteractiveText", exampleInteractiveText);
		}

		void onUpdate(float delta) override {
			getElement<UI::RepeatableImage>("CloudBackground")->render();
			getElement<UI::Image>("Logo")->render();
			getElement<UI::Text>("ExampleLabel")->render();

			auto* button = getElement<UI::InteractiveText>("ExampleInteractiveText");

			button->addMouseOverEvent(
				[](const SDL_MouseMotionEvent &event, UI::InteractiveText *element) {
					element->setColor({ 255, 0, 0, 255 });
				}
			);

			button->addMouseOutEvent(
				[](const SDL_MouseMotionEvent &event, UI::InteractiveText *element) {
					element->setColor({ 255, 255, 255, 255 });
				}
			);

			button->addClickEvent(
				[this](const SDL_MouseButtonEvent &event, UI::InteractiveText *element) {
					this->sceneManager->changeScene("Second");
				}
			);

			button->render();
		}

		void onTick() override {
			this->backgroundOffset = { this->backgroundOffset.x - 1, 0 };
			getElement<UI::RepeatableImage>("CloudBackground")->setOffset(this->backgroundOffset);
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

		UI::RepeatableImage* clouds;
		UI::InteractiveText* interactiveText;
	};
}

#endif
