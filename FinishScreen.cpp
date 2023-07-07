#include "FinishScreen.h"

#include "Constants.h"
#include "Utils.h"

FinishScreen::FinishScreen(
	std::shared_ptr<Level> level,
	std::string& const text) {

	m_Level = level;

	m_TextScale = std::make_shared<Tmpl8::vec2>(Utils::CalulcateH1TextWidth(text.length()), Constants::H1LableHeight);
	m_TextPosition = std::make_shared<Tmpl8::vec2>(
		(Constants::WindowWidth / 2) - (m_TextScale->x / 2), 
		(Constants::WindowHeight / 2) - (m_TextScale->y / 2));

	auto scale = *m_TextScale.get();

	m_Render = std::make_shared<Render>(text);
	m_Render->SetScale(scale);

	m_Visible = false;
}


void FinishScreen::Draw(
	Tmpl8::Surface& target,
	Tmpl8::vec2& const worldOffset) {

	if (!m_Visible) {
		return;
	}

	auto position = *m_TextPosition.get();
	m_Render->Draw(position, target);
}


void FinishScreen::SetVisible(bool b) {
	m_Visible = b;
}