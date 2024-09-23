#ifndef SCENE_TEST_H
#define SCENE_TEST_H

#include <iostream>
#include "../Scene.h"
#include "../Utilities/Logger.h"
#include "../UI/Elements.h"

using namespace UI;

namespace Scenes {
	class TestScene : public Scene {
	public:
		void onLoad() override {
			this->ui->setBackgroundColor({ 0, 0, 0 });

			addElement("ParentBackground", new UI::Box(
				{ 64, 0, 0, 255 },
				Scale{ 0.5f, 0.5f },
				Alignment{ HorizontalAlignment::Center, VerticalAlignment::Center }
			));

			// props
			SDL_Color boxColor = { 255, 255, 255, 255};
			Dimensions boxDimensions = { 20, 20 };

			// Top
			addElement("TopLeftBox", "ParentBackground", new UI::Box(
				boxColor,
				boxDimensions,
				Alignment{ HorizontalAlignment::Left, VerticalAlignment::Top }
			));

			addElement("TopMiddleBox", "ParentBackground", new UI::Box(
				boxColor,
				boxDimensions,
				Alignment{ HorizontalAlignment::Center, VerticalAlignment::Top }
			));

			addElement("TopRightBox", "ParentBackground", new UI::Box(
				boxColor,
				boxDimensions,
				Alignment{ HorizontalAlignment::Right, VerticalAlignment::Top }
			));

			// Middle
			addElement("MiddleLeftBox", "ParentBackground", new UI::Box(
				boxColor,
				boxDimensions,
				Alignment{ HorizontalAlignment::Left, VerticalAlignment::Center }
			));

			addElement("MiddleRightBox", "ParentBackground", new UI::Box(
				boxColor,
				boxDimensions,
				Alignment{ HorizontalAlignment::Right, VerticalAlignment::Center }
			));

			// Bottom
			addElement("BottomLeftBox", "ParentBackground", new UI::Box(
				boxColor,
				boxDimensions,
				Alignment{ HorizontalAlignment::Left, VerticalAlignment::Bottom }
			));

			addElement("BottomMiddleBox", "ParentBackground", new UI::Box(
				boxColor,
				boxDimensions,
				Alignment{ HorizontalAlignment::Center, VerticalAlignment::Bottom }
			));

			addElement("BottomRightBox", "ParentBackground", new UI::Box(
				boxColor,
				boxDimensions,
				Alignment{ HorizontalAlignment::Right, VerticalAlignment::Bottom }
			));
		}

		void onUpdate(float delta) override {
			getElement<UI::Box>("ParentBackground")->render();
			getElement<UI::Box>("TopLeftBox")->render();
			getElement<UI::Box>("TopMiddleBox")->render();
			getElement<UI::Box>("TopRightBox")->render();
			getElement<UI::Box>("MiddleLeftBox")->render();
			getElement<UI::Box>("MiddleRightBox")->render();
			getElement<UI::Box>("BottomLeftBox")->render();
			getElement<UI::Box>("BottomMiddleBox")->render();
			getElement<UI::Box>("BottomRightBox")->render();
		}
	};
}

#endif
