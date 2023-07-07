#pragma once

#include <string>
#include <memory>

#include "surface.h"
#include "template.h"

class Render
{
public:
	Render(
		std::shared_ptr<Tmpl8::Surface> texture, 
		int numOfFrames = 1);

	Render(std::string text);

	void InitAnimation(int interval);
	void SetScale(Tmpl8::vec2& const scale);

	void RenderAnimationNextFramCallback(void* p);

	void Draw(
		Tmpl8::vec2& const position, 
		Tmpl8::Surface& target);

private:
	std::shared_ptr<Tmpl8::Surface> m_Surface;
	std::shared_ptr<Tmpl8::Sprite> m_Sprite;

	std::shared_ptr<std::string> m_Text;

	int m_NumOfFrames;
	int m_CurrentFrame;

};

