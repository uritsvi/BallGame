#include "SolidEntity.h"
#include "Constants.h"
#include "TexturesLoader.h"

SolidEntity::SolidEntity(
	Tmpl8::vec2 position,
	Tmpl8::vec2 scale,
	int textureIndex) {
	
	m_Physics = 
		std::make_shared<Physics>(
			position, 
			scale,
			nullptr,
			nullptr);

	m_Physics->SetAABBColider();

	Texture texture;
	TexturesLoader::GetInstance().GetTexture(
		textureIndex, 
		texture);

	m_Render =
		std::make_shared<Render>(
			texture.surface, 
			texture.info->numOfFrames);

	if (texture.info->useAnimation) {
		m_Render->InitAnimation(texture.info->animationInterval);
	}

	m_Render->SetScale(scale);
}

void SolidEntity::Draw(
	Tmpl8::Surface& target, 
	Tmpl8::vec2& const worldOffset) {
	
	Tmpl8::vec2 position;
	m_Physics->GetPosition(position);

	m_Render->Draw(
		position - worldOffset,
		target);
}

