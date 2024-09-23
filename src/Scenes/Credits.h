#ifndef SCENE_TEST_H
#define SCENE_TEST_H

#include <iostream>
#include <fstream>
#include "../Scene.h"
#include "../Utilities/Logger.h"
#include "../UI/Elements.h"

using namespace UI;

namespace Scenes {
	class Credits : public Scene {
	private:
		int scrollerOffset = 0;
		int scrollerSpeed = 1;

		int lineOffset = 0;
		int spacerHeight = 30;

		std::string baseFont = "Atkinson";
		int baseFontSize = 20;
		SDL_Color baseColor = { 255, 255, 255, 255 };

		// @todo this should probably be optimised
		std::vector<std::string> lineNames;

	public:
		void onLoad() override {
			this->ui->setBackgroundColor({ 0, 0, 0 });

			addElement("ScrollingText", new UI::Box(
				{ 0, 0, 0, 255 },
				Scale{ 0.75f, 1.0f },
				Alignment{ HorizontalAlignment::Center, VerticalAlignment::Top }
			));

			std::string line;
			std::ifstream credits("assets/text/credits.txt");

			if (!credits.is_open()) {
				Logger::error("Unable to open credits.txt");
				return;
			}

			int i = 0;

			while (getline(credits, line)) {
				if (line.empty()) {
					this->lineOffset += this->spacerHeight;
					continue;
				}

				std::string lineFont = this->baseFont;
				int lineSize = this->baseFontSize;
				SDL_Color lineColor = this->baseColor;

				if (line.substr(0, 2) == "++") {
					lineFont = "Mini Pixel";
					lineSize = 100;
					line.erase(0, 2);
				} else if (line.substr(0, 1) == "+") {
					lineFont = "Mini Pixel";
					lineSize = 44;
					line.erase(0, 1);
				} else if (line.substr(0, 1) == "-") {
					lineSize = 14;
					line.erase(0, 1);
				}

				const std::string lineName = "CreditsLine" + std::to_string(i);
				auto* element = new UI::Text(
					lineFont,
					line,
					lineColor,
					lineSize,
					{ HorizontalAlignment::Center, VerticalAlignment::Top },
					{ 0, this->lineOffset },
					true
				);

				addElement(lineName, "ScrollingText", element);

				this->lineNames.push_back(lineName);
				this->lineOffset += element->getRect().h;

				i++;
			}

			credits.close();
		}

		void onUpdate(float delta) override {
			getElement<UI::Box>("ScrollingText")->render();

			if (!this->lineNames.empty()) {
				for (auto& lineName : this->lineNames) {
					getElement<UI::Text>(lineName)->render();
				}
			}
		}

		void onTick() override {
			this->scrollerOffset -= this->scrollerSpeed;
			getElement<UI::Box>("ScrollingText")->setOffset({ 0, this->scrollerOffset });

			if (this->scrollerOffset < -this->lineOffset) {
				this->sceneManager->changeScene("MainMenu");
			}
		}

		void onInputStart(SDL_Keycode key) override {
			if (key == SDLK_SPACE || key == SDLK_DOWN) {
				this->scrollerSpeed = 18;
			}
		}

		void onInputEnd(SDL_Keycode key) override {
			if (key == SDLK_SPACE || key == SDLK_DOWN) {
				this->scrollerSpeed = 4;
			}
		}
	};
}

#endif
