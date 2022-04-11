#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <SDL_image.h>


class GameManager;
class Player
{
public:
	Player(GameManager* _gameManager);
	Player();
	~Player();

	void LoadPlayer(const int _backgroundWidth, const int _backgroundHeight);
	void UpdatePlayerPosition();
	void InitializeHealth();
	SDL_Rect m_playerRect;
	float m_playerPosX;
	float m_playerPosY;
	int m_healthNumber;
	SDL_Rect m_healthRect[3];
	int m_playerHealth;
	void InitializeValues();



private:
	GameManager* m_gameManager;
	int const m_healthWidth;
	int const m_healthHeight;

};

