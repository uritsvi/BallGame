#include "TileEntity.h"
#include "TexturesLoader.h"

TileEntity::TileEntity(
	Tmpl8::vec2 position,
	Tmpl8::vec2 scale,
	int textureIndex) {

	m_Position = std::make_shared<Tmpl8::vec2>(position);

	Texture texture;
	
	TexturesLoader::GetInstance().GetTexture(
		textureIndex, 
		texture);

	m_Render = std::make_shared<Render>(
		texture.surface, 
		texture.info->numOfFrames);

	if (texture.info->useAnimation) {
		m_Render->InitAnimation(texture.info->animationInterval);
	}

	m_Render->SetScale(scale);
}

void TileEntity::Draw(
	Tmpl8::Surface& target,
	Tmpl8::vec2& const worldOffset) {

	auto position = *m_Position.get();
	m_Render->Draw(position + worldOffset, target);
}
