#pragma once

#include <string>
#include <memory>

#include "Object.h"
#include "Render.h"
#include "Level.h"
#include "template.h"

class FinishScreen : public Object
{
public:
	FinishScreen(
		std::shared_ptr<Level> level, 
		std::string& const text);
	
	void FinishScreen::Draw(
		Tmpl8::Surface& target,
		Tmpl8::vec2& const worldOffset);

	void SetVisible(bool b);

private:
	std::shared_ptr<Render> m_Render;
	
	std::shared_ptr<Tmpl8::vec2> m_TextPosition;
	std::shared_ptr<Tmpl8::vec2> m_TextScale;

	std::shared_ptr<Level> m_Level;

	bool m_Visible;
};

