#include <iostream>

#include "ColiderManager.h"
#include "Physics.h"

ColiderManager& ColiderManager::GetInstance() {
	static ColiderManager instance;
	return instance;
}

void ColiderManager::RegisterColider(
	std::shared_ptr<AABBCollider> collider) {

	m_Coliders.push_back(collider);
}

void ColiderManager::RegisterColider(
	std::shared_ptr<CircularCollider> collider) {
	
	m_Coliders.push_back(collider);
}

void ColiderManager::Tick() {
	for (auto collider : m_Coliders) {
		collider->UpdateData();
	}

	for (auto c1 : m_Coliders) {
		for (auto c2 : m_Coliders) {
			c1->AcceptCollider(*c2.get());
		}
	}
}