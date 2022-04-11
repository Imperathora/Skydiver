#pragma once
#include "GenericInteractables.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <SDL_image.h>
#include <iostream>


class GameManager;
class Enemies : public GenericInteractables<SDL_Rect>
{
public:
	Enemies(GameManager* _gameManager);
	~Enemies();
	Enemies();
	SDL_Rect m_enemyRect[4];

	void InitializeEnemies(float _playerPosY);
	void RespawnEnemies();
	void ScrollEnemies(unsigned int _currentTimeEnemyScroll, unsigned int _lastTimeEnemyScroll, float _deltaTime);
	bool EnemiesCollision(SDL_Rect _player);
	GenericInteractables<SDL_Rect> m_enemies;
	int m_enemiesNumber;

private:
	GameManager * m_gameManager;

	int m_enemiesHeight;
	int m_enemiesWidth;
	float m_enemiesSpeed;


};

