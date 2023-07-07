#include "Colliders.h"
#include "Physics.h"

#include <iostream>

Rect::Rect(
	float x,
	float y,
	float dx,
	float dy
) {
	this->x = x;
	this->dx = dx;
	this->y = y;
	this->dy = dy;
}

ColliderInfo::ColliderInfo(
	std::weak_ptr<Physics> physics,
	OnColide callback,
	void* p) {

	this->physics = physics;
	this->p = p;
	this->callback = callback;
}

Collider::Collider(ColliderInfo& const info) {
	m_Info = std::make_shared<ColliderInfo>();

	m_Info->callback = info.callback;
	m_Info->p = info.p;
	m_Info->physics = info.physics;
}

bool AABBCollider::AcceptCollider(Collider& collider) {
	return collider.ColideWith(*this);
}
bool CircularCollider::AcceptCollider(Collider& collider) {
	return collider.ColideWith(*this);
}

void Collider::GetColliderInfo(ColliderInfo& out) {
	out.callback = m_Info->callback;
	out.p = m_Info->p;
	out.physics = m_Info->physics;
}

AABBCollider::AABBCollider(ColliderInfo& const info) : Collider(info) {
	m_Rect = std::make_shared<Rect>(
		0.0f, 
		0.0f, 
		0.0f, 
		0.0f);
}

CircularCollider::CircularCollider(ColliderInfo& const info) : Collider(info) {
	m_Radius = 0.0f;
	m_Center = std::make_shared<Tmpl8::vec2>(
		0.0f,
		0.0f);
}

void AABBCollider::UpdateData() {
	ColliderInfo info;
	GetColliderInfo(info);

	auto physics = info.physics.lock();
	if (physics == nullptr) {
		return;
	}

	Tmpl8::vec2 position;
	Tmpl8::vec2 scale;

	physics->GetPosition(position);
	physics->GetScale(scale);

	m_Rect->x = position.x;
	m_Rect->y = position.y;
	m_Rect->dx = position.x + scale.x;
	m_Rect->dy = position.y + scale.y;
}

void CircularCollider::UpdateData() {
	ColliderInfo info;
	GetColliderInfo(info);

	auto physics = info.physics.lock();
	if (physics == nullptr) {
		return;
	}

	Tmpl8::vec2 position;
	Tmpl8::vec2 scale;

	physics->GetPosition(position);
	physics->GetScale(scale);

	m_Radius = scale.x / 2;
	m_Center->x = (position.x + scale.x / 2.0f);
	m_Center->y = (position.y + scale.y / 2.0f);
}

float CircularCollider::GetRadius() {
	return m_Radius;
}
void CircularCollider::GetCenter(Tmpl8::vec2& out) {
	out.x = m_Center->x;
	out.y = m_Center->y;
}

void AABBCollider::GetRect(Rect& out) {
	out.x = m_Rect->x;
	out.y = m_Rect->y;
	out.dx = m_Rect->dx;
	out.dy = m_Rect->dy;
}

bool AABBCollider::ColideWith(AABBCollider& collider) {
	return false;

}
bool AABBCollider::ColideWith(CircularCollider& collider) {
	return false;

}

/*
* The circular collision algorithm is taken from here: 
https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
and : 
https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-resolution
*/

bool CircularCollider::ColideWith(AABBCollider& collider) {
	ColliderInfo colliderInfo;
	collider.GetColliderInfo(colliderInfo);

	auto aabbPhysics = 
		colliderInfo.physics.lock();

	if (aabbPhysics == nullptr) {
		return false;
	}

	Tmpl8::vec2 aabbPosition;
	Tmpl8::vec2 aabbScale;

	aabbPhysics->GetPosition(aabbPosition);
	aabbPhysics->GetScale(aabbScale);

	auto aabbHalfScale = Tmpl8::vec2
	{ 
		(aabbScale.x) / 2.0f, 
		(aabbScale.y) / 2.0f 
	};

	auto aabbCenter = Tmpl8::vec2
	{
		aabbPosition.x + aabbHalfScale.x,
		aabbPosition.y + aabbHalfScale.y
	};

	auto center = *m_Center.get();
	auto distance = center - aabbCenter;

	Tmpl8::vec2 clamped;

	clamped.x = Tmpl8::Clamp<float>(
		distance.x, 
		-aabbHalfScale.x, 
		aabbHalfScale.x);

	clamped.y = Tmpl8::Clamp<float>(
		distance.y,
		-aabbHalfScale.y,
		aabbHalfScale.y);


	auto closest = aabbCenter + clamped;
	auto distancea = closest - center;

	auto len = sqrt(pow(distancea.x, 2) + pow(distancea.y, 2));
	

	if (len >= m_Radius) {
		return false;
	}

	ColliderInfo info;
	GetColliderInfo(info);

	auto physics = info.physics.lock();
	if (physics == nullptr) {
		return false;
	}

	Tmpl8::vec2 compass[] = {
		Tmpl8::vec2(0.0f, 1.0f),
		Tmpl8::vec2(1.0f, 0.0f),
		Tmpl8::vec2(0.0f, -1.0f),
		Tmpl8::vec2(-1.0f, 0.0f)
	};

	auto normalized = distancea;
	normalized.normalize();

	Direction direction = NONE;

	float max = 0.0f;
	int c = 0;

	for (auto side : compass) {
		float res = normalized.dot(side);
		if (res > max) {

			max = res;
			direction = (Direction)c;
		}

		c++;
	}

	if (physics->UseGravity()) {

		if (direction == UP || direction == DOWN) {
			float penetration = m_Radius - std::abs(distancea.y);

			if (direction == UP) {
				physics->AddPosition(Tmpl8::vec2(
					0.0f,
					-penetration));
			}
			else {
				physics->AddPosition(Tmpl8::vec2(
					0.0f,
					penetration));
			}
		}
		else {
			float penetration = m_Radius - std::abs(distancea.x);

			if (direction == RIGHT) {
				physics->AddPosition(Tmpl8::vec2(
					-penetration,
					0.0f));
			}
			else {
				physics->AddPosition(Tmpl8::vec2(
					penetration,
					0.0f));
			}
		}

		auto collisitionInfo = CollisionInfo{ direction };

		if (info.callback != nullptr) {
			info.callback(
				*this,
				collider,
				collisitionInfo,
				info.p);
		}

		if (colliderInfo.callback != nullptr) {
			colliderInfo.callback(
				collider,
				*this,
				collisitionInfo,
				colliderInfo.p);
		}
	}


	return true;


}
bool CircularCollider::ColideWith(CircularCollider& collider) {
	return false;

}