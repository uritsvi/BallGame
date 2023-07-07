#include <SDL_timer.h>
#include <SDL.h>

#include <string>

#include "game.h"
#include "Constants.h"
#include "ColiderManager.h"

#include "Ball.h"
#include "TexturesLoader.h"

#include "surface.h"
#include "FinishScreen.h"

namespace Tmpl8
{
	Tmpl8::vec2& const BallStartPosition = Tmpl8::vec2(250.0f, 1005-250.0f);
	Tmpl8::vec2& const BallStartScale = Tmpl8::vec2(25.0f, 25.0f);

	Tmpl8::vec2& const FinishSpotPosition = Tmpl8::vec2(20 * 75.0f, 1005);
	Tmpl8::vec2& const FinishSpotScale = Tmpl8::vec2(75.0f, 75.0f);

	std::string m_FinishScreenText = "Good Job";

	const int LevelHeight = 70;
	const int LevelWidth = 70;

	const int FirstFloorHeight = 14;
	const int FirstFloorWidth = LevelWidth / 2;

	const int LavaBlocksBetweenBricksFistFloor = 8;

	const int BricksHeightFirstFloor = 2;

	const int FirstFloorToWallBrickHight = FirstFloorHeight;
	const int FirstFloorToWallBrickWidth = 2;
	const int FirstFloorToWallOffset = 2;

	const int WallToSecondFloorHeight = LevelHeight / 2;
	const int WallToSecondFloorStartY = 0;
	const int WallToSecondFloorStartX = 
		FirstFloorWidth + 
		FirstFloorToWallOffset + 
		FirstFloorToWallBrickWidth + 8;

	const int UnderFirstFloorY = FirstFloorHeight + 10;
	const int UnderFirstFloorX = WallToSecondFloorStartX - 1;

	const int SecondFloorHeight = 
		WallToSecondFloorHeight - 1;

	const int SecondFloorWidth = 4;

	const int WallToSecondFloorLavalWidth = 2;

	const int SecondFloorStaresOffsetX = 2;
	const int SecondFloorStaresOffsetY = 2;

	const int NumOfStares = 3;

	const int FloorAffterStaresWidth = 3;

	void OnDamage(
		DamageEntiy& entity, 
		void* p) {

		auto instance = reinterpret_cast<Game*>(p);
		instance->GameOnDamage(entity, p);
	}

	void OnFinish(
		LevelIndex& index, 
		void* p) {

		auto instance = reinterpret_cast<Game*>(p);
		instance->GameOnFinish(index, p);
	}


	std::shared_ptr<DamageEntiy> Game::CreateLava(Tmpl8::vec2 position) {
		auto entity =
			std::make_shared<DamageEntiy>(
				position,
				Tmpl8::vec2(
					Constants::DefaultBlockWidthHeight, 
					Constants::DefaultBlockWidthHeight),
				2,
				OnDamage,
				this);

		return entity;
	}

	std::shared_ptr<SolidEntity> Game::CreateBrick(Tmpl8::vec2 position) {
		auto entity = 
			std::make_shared<SolidEntity>(
				position, 
				Tmpl8::vec2(
					Constants::DefaultBlockWidthHeight, 
					Constants::DefaultBlockWidthHeight),
				0);

		return entity;
	}

	void Game::GameOnDamage(
		DamageEntiy& entity,
		void* p) {

		m_Level->Reset();
	}

	void Game::GameOnFinish(
		LevelIndex& index,
		void* p) {

		m_Finish = true;
		m_Running = false;
		m_FinishScreen->SetVisible(true);
	}

	void Game::Restart() {
		m_Finish = false;
		m_Running = true;
		m_Level->Reset();
		m_FinishScreen->SetVisible(false);
	}

	void Game::Init()
	{

		m_Running = true;
		auto textures = std::list<TextureInfo>();
		
		textures.push_back(TextureInfo(Assets::StoneBrick,0, false));
		textures.push_back(TextureInfo(Assets::BallPngPath,1, false));
		textures.push_back(TextureInfo(Assets::EdgeLavaTile,2, true, 2, 500));
		textures.push_back(TextureInfo(Assets::FinishLineTile,3, false));

		TexturesLoader::GetInstance().Load(textures);

		m_Ball = std::make_shared<Ball>(
			1,
			BallStartPosition,
			BallStartScale
			);

		m_Level = std::make_shared<Level>(m_Ball);
		m_Camera = std::make_shared<Camera>();

		m_Level->AddObject(m_Ball);

		for (int i = 0; i < LevelHeight; i++) {
			m_Level->AddObject(CreateBrick(Tmpl8::vec2(0, i * Constants::DefaultBlockWidthHeight
			)));
		}
		for (int i = 1; i < LevelWidth; i++) {
			m_Level->AddObject(CreateLava(Tmpl8::vec2(
				i * Constants::DefaultBlockWidthHeight, 
				((LevelHeight - 2) * Constants::DefaultBlockWidthHeight)
			)));

			m_Level->AddObject(CreateBrick(Tmpl8::vec2(
				i * Constants::DefaultBlockWidthHeight,
				0.0f
			)));


			m_Level->AddObject(CreateBrick(Tmpl8::vec2(
				i * Constants::DefaultBlockWidthHeight,
				((LevelHeight - 1) * Constants::DefaultBlockWidthHeight)
			)));
		}
		for (int i = 0; i < FirstFloorWidth; i++) {
			m_Level->AddObject(CreateBrick(Tmpl8::vec2(
				i * Constants::DefaultBlockWidthHeight,
				FirstFloorHeight * Constants::DefaultBlockWidthHeight
			)));
		
		}
		for (int i = 0; i < UnderFirstFloorX; i++) {
			m_Level->AddObject(CreateBrick(Tmpl8::vec2(
				i * Constants::DefaultBlockWidthHeight,
				UnderFirstFloorY * Constants::DefaultBlockWidthHeight
			)));
			m_Level->AddObject(CreateLava(Tmpl8::vec2(
				i * Constants::DefaultBlockWidthHeight,
				(UnderFirstFloorY - 1) * Constants::DefaultBlockWidthHeight
			)));
		}
		for (int i = 1; i <  FirstFloorWidth; i += LavaBlocksBetweenBricksFistFloor) {
			
			for (int j = 0; (j < LavaBlocksBetweenBricksFistFloor) && (i + j) < FirstFloorWidth; j++) {
				m_Level->AddObject(CreateLava(Tmpl8::vec2(
					(i + j) * Constants::DefaultBlockWidthHeight,
					(FirstFloorHeight - 1) * Constants::DefaultBlockWidthHeight
				)));
			}

			for (int j = 0; (j < BricksHeightFirstFloor) && (i + BricksHeightFirstFloor) < FirstFloorWidth; j++) {
				m_Level->AddObject(CreateBrick(Tmpl8::vec2(
					(i + 2) * Constants::DefaultBlockWidthHeight,
					(-j + FirstFloorHeight - 1) * Constants::DefaultBlockWidthHeight
				)));
			}
		}
		for (int i = 0; i < FirstFloorToWallBrickWidth; i++) {
			m_Level->AddObject(CreateBrick(Tmpl8::vec2(
				(i + FirstFloorWidth + FirstFloorToWallOffset) * Constants::DefaultBlockWidthHeight,
				FirstFloorToWallBrickHight * Constants::DefaultBlockWidthHeight
			)));
		}
		for (int i = 0; i < WallToSecondFloorHeight; i++) {
			m_Level->AddObject(CreateBrick(Tmpl8::vec2(
				WallToSecondFloorStartX * Constants::DefaultBlockWidthHeight,
				 (i + WallToSecondFloorStartY) * Constants::DefaultBlockWidthHeight
			)));
		}
		for (int i = 0; i < WallToSecondFloorLavalWidth; i++) {
			m_Level->AddObject(CreateLava(Tmpl8::vec2(
				(WallToSecondFloorStartX - i - 1) * Constants::DefaultBlockWidthHeight,
				SecondFloorHeight * Constants::DefaultBlockWidthHeight
			)));
		}
		for (int i = 0; i < SecondFloorWidth; i++) {
			m_Level->AddObject(CreateBrick(Tmpl8::vec2(
				(WallToSecondFloorStartX - 
					i - 
					WallToSecondFloorLavalWidth - 
					1) * Constants::DefaultBlockWidthHeight,
					SecondFloorHeight * Constants::DefaultBlockWidthHeight
			)));
		}

		int x = 
			(WallToSecondFloorStartX - 
			SecondFloorWidth - 
			WallToSecondFloorLavalWidth - 
			SecondFloorStaresOffsetX);

		int y = SecondFloorHeight;

		for (int i = 0; i < NumOfStares; i++) {
			m_Level->AddObject(CreateBrick(Tmpl8::vec2(
				x * Constants::DefaultBlockWidthHeight, 
				y * Constants::DefaultBlockWidthHeight
			)));

			x -= SecondFloorStaresOffsetX;
			y -= SecondFloorStaresOffsetY;
		}


		for (int i = 0; i < FloorAffterStaresWidth; i++) {
			m_Level->AddObject(CreateBrick(Tmpl8::vec2(
				--x * Constants::DefaultBlockWidthHeight,
				y * Constants::DefaultBlockWidthHeight
			)));
		}
		auto finishSpotPosition = Tmpl8::vec2(
			--x * Constants::DefaultBlockWidthHeight,
			y * Constants::DefaultBlockWidthHeight
		);

		m_FinishSpot = std::make_shared<FinishSpot>(
			m_Level,
			OnFinish,
			this,
			finishSpotPosition,
			FinishSpotScale,
			3);

		m_Level->AddObject(m_FinishSpot);

		m_FinishScreen = std::make_shared<FinishScreen>(
			m_Level,
			std::string(m_FinishScreenText));

		m_HowToPlayMenu = std::make_shared<HowToPlayMenu>();

		m_Level->AddObject(m_FinishScreen);
		m_Level->AddObject(m_HowToPlayMenu);

 
		SDL_AddTimer(
			Constants::PhysicsTickInterval, 
			[](Uint32 interval, void* p)
			{
				Game* game = reinterpret_cast<Game*>(p);
				game->PhysicsTick();

				return interval;
			}, 
			this);
	}
	
	void Game::Shutdown()
	{
		m_Running = false;
		SDL_Quit();
	}

	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);

		auto camera = *m_Camera.get();
		m_Ball->Tick(camera);

		m_Camera->Draw(
			*screen, 
			*m_Level.get());
	}

	void Game::PhysicsTick() {
		if (!m_Running) {
			return;
		}

		for (auto scanCode : m_KeysDown) {

			if (scanCode == SDL_SCANCODE_SPACE) {
				m_Ball->Jump();
			}
		}
		m_KeysDown.clear();
		
		const Uint8* keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_D]) {
			m_Ball->MoveRight();
		}
		if (keys[SDL_SCANCODE_A]) {
			m_Ball->MoveLeft();
		}

		m_Ball->PhysicsTick();

		ColiderManager::GetInstance().Tick();
	}

	void Game::KeyDown(int key) {
		if (key == SDL_SCANCODE_R) {
			Restart();
			return;
		}
		if (key == SDL_SCANCODE_H) {
			
			if (!m_Finish) {
				m_Running = !m_Running;
				m_HowToPlayMenu->FlipIsVisible();
			}
		}

		m_KeysDown.push_back((SDL_Scancode)key);
	}

};

