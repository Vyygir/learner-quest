#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include <iostream>
#include "../Scene.h"
#include "../Utilities/Logger.h"
#include "../UI/Elements.h"

using namespace UI;

namespace Scenes {
	struct MenuItem {
		const std::string name;
		const std::string label;
		std::function<void(const SDL_MouseMotionEvent &, InteractiveText*)> onMouseOver;
		std::function<void(const SDL_MouseMotionEvent &, InteractiveText*)> onMouseOut;
		std::function<void(const SDL_MouseButtonEvent &, InteractiveText*)> onClick;
		SDL_Color color = { 255, 255, 255, 255 };
		int fontSize = 58;
	};

	class MainMenu : public Scene {
	public:
		void onLoad() override {
			this->ui->setBackgroundColor({ 79, 177, 229 });

			addElement("CloudBackground", new UI::RepeatableImage(
				"assets/media/menu/background.png",
				true,
				false,
				Scale{ 0.0f, 0.48f },
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

			addElement("InDevelopment", new UI::Text(
				"Atkinson",
				"This software is in early development and is purely a proof of concept.",
				{ 255, 255, 255, 192 },
				15,
				{ HorizontalAlignment::Left, VerticalAlignment::Bottom },
				{ 10, -10 }
			));

			createMenuItems();
		}

		void onUpdate(float delta) override {
			getElement<UI::RepeatableImage>("CloudBackground")->render();
			getElement<UI::Image>("Logo")->render();
			getElement<UI::Text>("InDevelopment")->render();

			renderMenuItems();
		}

		void onTick() override {
			this->backgroundOffset = { this->backgroundOffset.x - 1, 0 };
			getElement<UI::RepeatableImage>("CloudBackground")->setOffset(this->backgroundOffset);
		}

		void onResize(int newWidth, int newHeight) override {
			updateMenuItemSpacing(newHeight);
		}

	private:
		Offset backgroundOffset = { -100, 0 };

		const int MENU_ITEM_SPACING = 50;
		std::vector<MenuItem> menuItems{
			MenuItem{
				"MenuItemStart",
				"Start",
				[](const SDL_MouseMotionEvent &event, UI::InteractiveText *element) {
					element->setColor({ 255, 255, 255, 180 });
				},
				[](const SDL_MouseMotionEvent &event, UI::InteractiveText *element) {
					element->setColor({ 255, 255, 255, 255 });
				}
			},
			MenuItem{
				"MenuItemOptions",
				"Options",
				[](const SDL_MouseMotionEvent &event, UI::InteractiveText *element) {
					element->setColor({ 255, 255, 255, 180 });
				},
				[](const SDL_MouseMotionEvent &event, UI::InteractiveText *element) {
					element->setColor({ 255, 255, 255, 255 });
				}
			},
			MenuItem{
				"MenuItemCredits",
				"Credits",
				[](const SDL_MouseMotionEvent &event, UI::InteractiveText *element) {
					element->setColor({ 255, 255, 255, 180 });
				},
				[](const SDL_MouseMotionEvent &event, UI::InteractiveText *element) {
					element->setColor({ 255, 255, 255, 255 });
				}
			},
			MenuItem{
				"MenuItemQuit",
				"Quit",
				[](const SDL_MouseMotionEvent &event, UI::InteractiveText *element) {
					element->setColor({ 255, 255, 255, 180 });
				},
				[](const SDL_MouseMotionEvent &event, UI::InteractiveText *element) {
					element->setColor({ 255, 255, 255, 255 });
				},
				[this](const SDL_MouseButtonEvent &event, UI::InteractiveText *element) {
					if (event.type == SDL_MOUSEBUTTONDOWN && event.button == SDL_BUTTON_LEFT) {
						this->game->quit();
					}
				}
			}
		};

		void createMenuItems() {
			if (this->menuItems.empty()) {
				return;
			}

			int index = 0;

			for (auto& item : this->menuItems) {
				auto* element = new UI::InteractiveText(
					"Mini Pixel",
					item.label,
					item.color,
					item.fontSize,
					{ HorizontalAlignment::Center, VerticalAlignment::Center },
					{ 0, 0 },
					true
				);

				if (index > 0) {
					element->setOffset({ 0, (element->getRect().h + MENU_ITEM_SPACING) * index });
				}

				if (item.onMouseOver) {
					element->addMouseOverEvent(item.onMouseOver);
				}

				if (item.onMouseOut) {
					element->addMouseOutEvent(item.onMouseOut);
				}

				if (item.onClick) {
					element->addClickEvent(item.onClick);
				}

				this->ui->addElementEventHandler(element);
				addElement(item.name, element);

				index++;
			}
		}

		void renderMenuItems() {
			if (this->menuItems.empty()) {
				return;
			}

			for (auto& item : this->menuItems) {
				getElement<UI::InteractiveText>(item.name)->render();
			}
		}

		void updateMenuItemSpacing(int windowHeight) {
			if (this->menuItems.empty()) {
				return;
			}

			int index = 0;

			for (auto &item: this->menuItems) {
				if (index > 0) {
					auto *element = getElement<UI::InteractiveText>(item.name);
					int spacing = (MENU_ITEM_SPACING * windowHeight) / DEFAULT_WINDOW_HEIGHT;

					element->setOffset({ 0, (element->getRect().h + spacing) * index });
				}

				index++;
			}
		}
	};
}

#endif
