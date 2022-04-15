#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <SDL_image.h>
#include "UserInterface.h"
#include <iostream>
#include "InputManager.h"
#include "Player.h"
#include "Collectables.h"
#include "GenericInteractables.h"
#include "Enemies.h"

class InputManager;
class Player;
class Collectables;
class Enemies;
class GameManager
{
public:
	GameManager();
	~GameManager();

	void LoadGame();
	void CreateTextures();
	void LoadImages();
	void Render();
	void LoadUI();
	void UpdateGame();
	void ChangeColor();
	float CalculateDeltaTime();
	int GetBackgroundWidth();
	int GetBackgroundHeight();
	void Initialize();

	void BackgroundScrollUpdate();

	SDL_Renderer* m_renderer;
	SDL_Texture* m_playerTexture;
	float deltaTime;
	unsigned int m_lastTime, m_currentTime;
	int m_startTime;
	bool m_healthLost;
	int m_timeInSeconds;
	bool m_running;

private:
	void Timer(Uint32 interval);
	void Destroy();
	void GameOver();
	SDL_Window* m_window;
	bool m_collectableCollison;
	bool m_enemyCollision;
	int _bgWidth;
	int _bgHeight;
	int m_backgroundWidth;
	int m_backgroundHeight;
	float m_backgroundScrollingOffset;
	float m_backgroundScrollSpeed;
	void SetBackgroundWidth();
	void SetBackgroundHeight();
	UserInterface UI;
	InputManager m_inputManager;
	Player m_player;
	Collectables m_collectable;
	Enemies m_enemy;
	SDL_Surface* m_playerSurface;
	SDL_Surface* m_collectableSurface;
	SDL_Texture* m_collectableTexture;

	SDL_Surface* m_healthSurface;
	SDL_Surface* m_healthLostSurface;
	SDL_Texture* m_healthTexture;
	SDL_Texture* m_healthLostTexture;

	SDL_Surface* m_enemySurface;
	SDL_Texture* m_enemyTexture;

	SDL_Surface* m_backgroundSurface;
	SDL_Texture* m_backgroundTexture;

	SDL_Rect m_backgroundRect;
	SDL_Rect m_backgroundRect2;
	unsigned int m_lastTimeInteractableScroll, m_currentTimeInteractableScroll;
};

