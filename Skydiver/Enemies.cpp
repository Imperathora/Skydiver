#include "Enemies.h"
#include "GameManager.h"

Enemies::Enemies(GameManager* _gameManager) :
	m_gameManager(_gameManager),
	m_enemiesNumber(4),
	m_enemiesHeight(40),
	m_enemiesWidth(40),
	m_enemyRect(),
	m_enemies(),
	m_enemiesSpeed(1)
{}

Enemies::Enemies() :
	m_enemiesNumber(4),
	m_enemiesHeight(40),
	m_enemiesWidth(40),
	m_enemyRect(),
	m_enemies(),
	m_enemiesSpeed(1)
{}

Enemies::~Enemies()
{}

void Enemies::InitializeEnemies(float _playerPosY)
{
	m_enemies.Initialize(m_gameManager->GetBackgroundWidth(), m_enemiesWidth, m_enemiesHeight, _playerPosY, m_enemiesNumber, m_enemyRect);
}

void Enemies::RespawnEnemies()
{
	m_enemies.Respawn(m_gameManager->GetBackgroundWidth(), m_enemiesWidth, m_gameManager->GetBackgroundHeight(), m_enemiesNumber, m_enemyRect);
}

void Enemies::ScrollEnemies(unsigned int _currentTimeEnemyScroll, unsigned int _lastTimeEnemyScroll, float _deltaTime)
{
	m_enemies.InteractablesScrollSpeed(_currentTimeEnemyScroll, _lastTimeEnemyScroll, m_enemiesNumber, _deltaTime, m_enemyRect, m_enemiesSpeed);
}

bool Enemies::EnemiesCollision(SDL_Rect _player)
{
	m_enemies.Collision(m_enemiesNumber, m_enemyRect, _player);
	if (m_enemies.m_collision)
	{
		m_enemies.m_collision = false;
		return true;
	}
	return false;
}
