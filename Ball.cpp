#include "Ball.h"
#include "Constants.h"
#include "TexturesLoader.h"

const float jumpVelocity = 3.5f;
const float moveVelocity = 2.5f;

const float JumpMoveInXVelocity = 40.0f;

const float maxVelocity = -15.0f;

const int numOfJumps = 1;

void _OnColideCallback(
	Collider& c1,
	Collider& c2,
	CollisionInfo& const info,
	void* p) {

	Ball* ball = reinterpret_cast<Ball*>(p);
	ball->OnColideCallback(
		c1, 
		c2, 
		info,
		p);

}

Ball::Ball(
	int textureIndex,
	Tmpl8::vec2 position,
	Tmpl8::vec2 scale) {

	m_NumOfJumps = 0;

	m_WorldOffset = position;
	m_StartPosition = position;

	m_Physics = std::make_shared<Physics>(
		position,
		scale,
		_OnColideCallback,
		this);

	m_Physics->InitGravity(maxVelocity);
	m_Physics->SetCircularColider();

	Texture texture;
	TexturesLoader::GetInstance().GetTexture(
		textureIndex, 
		texture);

	
	m_Render =
		std::make_shared<Render>(texture.surface);
		

	m_Render->SetScale(scale);

	m_LastCollideSide = UP;

}

void Ball::Draw(
	Tmpl8::Surface& target,
	Tmpl8::vec2& const worldOffset) {
	
	Tmpl8::vec2 position;
	m_Physics->GetPosition(position);

	m_Render->Draw(
		position - worldOffset,
		target);

}

void Ball::PhysicsTick() {
	m_Physics->Tick();
}

void Ball::Jump() {
	if (m_NumOfJumps++ >= numOfJumps) {
		return;
	}

	m_Physics->SetVelocity(Tmpl8::vec2(
		0.0f, 
		-jumpVelocity));
}

void Ball::MoveLeft() {
	m_Physics->AddVelocity(Tmpl8::vec2(-moveVelocity, 0.0f));

}
void Ball::MoveRight() {
	m_Physics->AddVelocity(Tmpl8::vec2(moveVelocity, 0.0f));
}

void Ball::OnColideCallback(
	Collider& c1,
	Collider& c2,
	CollisionInfo& const info,
	void* p) {

	if (m_LastCollideSide != DOWN) {
		m_NumOfJumps = 0;
	}

	m_LastCollideSide = info.direction;

}

void Ball::SetPosition(Tmpl8::vec2& const position) {
	m_Physics->SetPosition(position);
}

void Ball::Tick(
	Camera& const camera) {
	
	Tmpl8::vec2 position;
	m_Physics->GetPosition(position);

		camera.AddPositionOffset(
			Tmpl8::vec2(position.x, position.y) -
			Tmpl8::vec2(m_WorldOffset.x, m_WorldOffset.y));

}

void Ball::Reset() {
	SetPosition(m_StartPosition);
	m_Physics->SetVelocity(Tmpl8::vec2(0.0f, 0.0f));
}