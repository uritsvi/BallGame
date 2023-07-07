#include "Camera.h"
#include "Object.h"

#include <iostream>

Camera::Camera() {
	m_Position = std::make_shared<Tmpl8::vec2>(0.0f, 0.0f);
}

void Camera::Draw(
	Tmpl8::Surface& target,
	Level& const level) {

	auto objects = level.GetObjects();
	for (auto object : objects) {
		object->Draw(
			target, 
			*m_Position.get());
	}


}

void Camera::AddPositionOffset(Tmpl8::vec2 offset) {
	m_Position->x = offset.x;
	m_Position->y = offset.y;


}