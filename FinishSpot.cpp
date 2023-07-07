#include "FinishSpot.h"
#include "ColiderManager.h"
#include "Level.h"
#include "TexturesLoader.h"

void FinishSpotOnColide(
	Collider& c1,
	Collider& c2,
	CollisionInfo& const info,
	void* p) {

	auto inststance = 
		reinterpret_cast<FinishSpot*>(p);

	inststance->OnColideFinishSpot(
		c1, 
		c2, 
		info, 
		p);
}

FinishSpot::FinishSpot(
	std::shared_ptr<Level> level,
	OnEnter callback,
	void* p,
	Tmpl8::vec2& position,
	Tmpl8::vec2& scale,
	int textureIndex) {
	
	m_Level = level;
	m_OnEnter = callback;

	m_P = p;

	m_Physics = std::make_shared<Physics>(
		position, 
		scale, 
		FinishSpotOnColide,
		this);

	m_Physics->SetAABBColider();

	Texture texture;
	TexturesLoader::GetInstance().GetTexture(
		textureIndex, 
		texture);

	m_Render = std::make_shared<Render>(texture.surface);
	m_Render->SetScale(scale);
}

void FinishSpot::Draw(
	Tmpl8::Surface& target,
	Tmpl8::vec2& const worldOffset) {

	Tmpl8::vec2 position;
	m_Physics->GetPosition(position);

	m_Render->Draw(
		position - worldOffset,
		target);
}

void FinishSpot::OnColideFinishSpot(
	Collider& c1,
	Collider& c2,
	CollisionInfo& const info,
	void* p) {
	
	LevelIndex index;
	m_Level->GetLevelIndex(index);

	m_OnEnter(
		index, 
		m_P);
}