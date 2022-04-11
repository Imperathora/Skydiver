#pragma once
#include "GenericInteractables.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <SDL_image.h>
#include <iostream>
#include "UserInterface.h"


class GameManager;
class Collectables : public GenericInteractables<SDL_Rect> 
{
public:
	Collectables(GameManager* _gameManager);
	~Collectables();
	Collectables();
	SDL_Rect m_collectableRect[4];

	void InitializeCollectables(float _playerPosY);
	void RespawnCollectables() ;
	void ScrollCollectables(unsigned int _currentTimeCollectableScroll, unsigned int _lastTimeCollectableScroll, float _deltaTime);
	bool CollectableCollision(SDL_Rect _player);
	GenericInteractables<SDL_Rect> m_collectables;
	int m_collectableCounter;
	int const m_collectableNumber;
	void InitializeValues() ;


private:
	GameManager * m_gameManager;

	int const m_collectableHeight;
	int const m_collectableWidth;
	float  m_collectableSpeed;

};

