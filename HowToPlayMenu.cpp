#include "HowToPlayMenu.h"
#include "Constants.h"
#include "Utils.h"

const std::string HowToPlayTitle = std::string("How To Play:");

const std::string HowToPlayTexts[]{
	"- Use the A and D keys to move the ball forward or backwards",
	"- Use the space button to jump",
	"- to restart the game press the R button",
	"- Your goal is to touch the finish brick"
};

HowToPlayMenu::HowToPlayMenu() {
	m_IsVisible = false;


	auto render = std::make_shared<Render>(HowToPlayTitle);
	render->SetScale(Tmpl8::vec2(
		Utils::CalulcateH1TextWidth(HowToPlayTitle.length()),
		Constants::H1LableHeight));

	auto textElement = std::make_shared<TextElement>
		(
			std::make_shared<Tmpl8::vec2>(10.0f, 10.0f),
			render
			
		);

	m_Renders.push_back(textElement);


	int c = 0;
	for (auto text : HowToPlayTexts) {
		auto render = std::make_shared<Render>(text);
		render->SetScale(Tmpl8::vec2(
			Utils::CalulcateH2TextWidth(text.length()),
			Constants::H2LableHeight));

		auto textElement = std::make_shared<TextElement>
			(
				std::make_shared<Tmpl8::vec2>(10.0f, 100.0f + (c++) * 50),
				render

				);

		m_Renders.push_back(textElement);

	}



}

void HowToPlayMenu::Draw(
	Tmpl8::Surface& target,
	Tmpl8::vec2& const worldOffset) {

	if (!m_IsVisible) {
		return;
	}

	for (auto render : m_Renders) {
		auto position = *render->position.get();
		
		render->render->Draw(
			position, 
			target);
	}
}

void HowToPlayMenu::FlipIsVisible() {
	m_IsVisible = !m_IsVisible;
}