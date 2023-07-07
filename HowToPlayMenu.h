#pragma once

#include <string>
#include <memory>
#include <list>

#include "Object.h"
#include "Render.h"
#include "Level.h"
#include "template.h"

class HowToPlayMenu : public Object
{
public:
	HowToPlayMenu();

	void Draw(
		Tmpl8::Surface& target,
		Tmpl8::vec2& const worldOffset);

	void FlipIsVisible();

private:
	struct TextElement {
		TextElement(
			std::shared_ptr<Tmpl8::vec2> position,
			std::shared_ptr<Render> render) {

			this->position = position;
			this->render = render;
		}

		std::shared_ptr<Tmpl8::vec2> position;
		std::shared_ptr<Render> render;
	};

	std::list<std::shared_ptr<TextElement>> m_Renders;

	bool m_IsVisible;
};

