#include "DamageEntiy.h"
#include "TexturesLoader.h"

void DamageEntiyOnColide(
	Collider& c1,
	Collider& c2,
	CollisionInfo& const info,
	void* p) {

	auto entity = reinterpret_cast<DamageEntiy*>(p);
	entity->CollideCallack(
		c1, 
		c2, 
		info, 
		p);
}

DamageEntiy::DamageEntiy(
	Tmpl8::vec2 position,
	Tmpl8::vec2 scale,
	int textureIndex,
	OnTouchDamageEntity callback,
	void* p) {

	m_P = p;
	m_Callback = callback;

	m_Physics =
		std::make_shared<Physics>(
			position,
			scale,
			DamageEntiyOnColide,
			this);

	m_Physics->SetAABBColider();

	Texture texture;
	TexturesLoader::GetInstance().GetTexture(
		textureIndex,
		texture);

	m_Render =
		std::make_shared<Render>(texture.surface, texture.info->numOfFrames);
	
	if (texture.info->useAnimation) {
		m_Render->InitAnimation(texture.info->animationInterval);
	}

	m_Render->SetScale(scale);
}

void DamageEntiy::Draw(
	Tmpl8::Surface& target,
	Tmpl8::vec2& const worldOffset) {
	
	Tmpl8::vec2 position;
	m_Physics->GetPosition(position);

	m_Render->Draw(
		position - worldOffset,
		target);
}

void DamageEntiy::CollideCallack(
	Collider& c1,
	Collider& c2,
	CollisionInfo& const info,
	void* p) {
	
	m_Callback(
		*this, 
		m_P);
}


