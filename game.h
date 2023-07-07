#pragma once

#include <SDL.h>

#include <memory>
#include <list>

#include "Level.h"
#include "Camera.h"
#include "Ball.h"
#include "DamageEntiy.h"
#include "TileEntity.h"
#include "SolidEntity.h"
#include "FinishSpot.h"
#include "FinishScreen.h"
#include "HowToPlayMenu.h"

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp(int key) {}
	void KeyDown(int key);
	void PhysicsTick();
	void GameOnDamage(
		DamageEntiy& entity,
		void* p);
	void GameOnFinish(
		LevelIndex& index, 
		void* p);
	void Restart();

private:
	std::shared_ptr<DamageEntiy> CreateLava(Tmpl8::vec2 position);
	std::shared_ptr<SolidEntity> CreateBrick(Tmpl8::vec2 position);
private:
	Surface* screen;
	
	std::shared_ptr<Ball> m_Ball;
	std::shared_ptr<Level> m_Level;
	std::shared_ptr<Camera> m_Camera;
	std::shared_ptr<FinishSpot> m_FinishSpot;
	std::shared_ptr<FinishScreen> m_FinishScreen;
	std::shared_ptr<HowToPlayMenu> m_HowToPlayMenu;

	std::list<SDL_Scancode> m_KeysDown;

	bool m_Running;
	bool m_Finish;

};

}; // namespace Tmpl8