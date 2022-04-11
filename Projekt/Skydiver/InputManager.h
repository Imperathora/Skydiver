#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Player.h"

class GameManager;
class Player;
class InputManager
{
public :
	InputManager(GameManager* _gameManager);
	~InputManager();
	
	GameManager* m_gameManager;

	void EventHandler(float deltaTime, const int _backgroundWidth, Player* _player);
	SDL_Event m_event;

};

