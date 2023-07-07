#include <SDL_timer.h>

#include "Render.h"

using namespace Tmpl8;

Uint32 AnimationNextFramCallback(
	Uint32 interval, 
	void* p){

	Render* instance = reinterpret_cast<Render*>(p);
	instance->RenderAnimationNextFramCallback(p);

	return interval;
}

Render::Render(
	std::shared_ptr<Tmpl8::Surface> texture,
	int numOfFrames){
	
	m_Surface = texture;
	m_Sprite = std::make_shared<Sprite>(
		m_Surface.get(), 
		numOfFrames);

	m_NumOfFrames = numOfFrames;
	m_CurrentFrame = 0;

}

Render::Render(std::string text) {
	m_Text = std::make_shared<std::string>(text);

	m_Surface = std::make_shared<Tmpl8::Surface>(
		8 * text.length(),
		10);

	m_Surface->Clear(0);

	
	m_Surface->Print(
		(char*)text.c_str(), 
		0, 
		0, 
		0xffffff);


	m_Sprite = std::make_shared<Sprite>(
		m_Surface.get(),
		1);

	m_NumOfFrames = 1;
	m_CurrentFrame = 0;
}

void Render::InitAnimation(int interval) {
	SDL_AddTimer(interval, AnimationNextFramCallback, this);
}

void Render::RenderAnimationNextFramCallback(void* p) {
	m_CurrentFrame++;
	if (m_CurrentFrame >= m_NumOfFrames) {
		m_CurrentFrame = 0;
	}

	m_Sprite->SetFrame(m_CurrentFrame);
}

void Render::SetScale(Tmpl8::vec2& const scale) {
	auto tempSprite = std::make_unique<Sprite>(
		m_Sprite->GetSurface(),
		1);

	auto newSurface =
		std::make_shared<Surface>(
			scale.x * m_NumOfFrames, 
			scale.y);


	newSurface->Clear(0);
	
	tempSprite->DrawScaled(
		0, 
		0, 
		scale.x * m_NumOfFrames,
		scale.y, 
		newSurface.get());


	m_Sprite = std::make_shared<Sprite>(
		newSurface.get(), 
		m_NumOfFrames);

	m_Surface = newSurface;
	m_Sprite->SetFrame(0);

	
}

void Render::Draw(
	vec2& const position,
	Surface& target) {

	m_Sprite->Draw(
		&target,
		position.x, 
		position.y);

	
}
