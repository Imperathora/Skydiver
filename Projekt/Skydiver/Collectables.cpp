#include "Collectables.h"
#include "GameManager.h"
#include "UserInterface.h"

Collectables::Collectables(GameManager* _gameManager) :
	m_gameManager(_gameManager),
	m_collectableNumber(4),
	m_collectableHeight(40),
	m_collectableWidth(40),
	m_collectableRect(),
	m_collectables(),
	m_collectableSpeed(1),
	m_collectableCounter(0)
{}

Collectables::Collectables() :
	m_collectableNumber(4),
	m_collectableHeight(40),
	m_collectableWidth(40),
	m_collectableRect(),
	m_collectables(),
	m_collectableSpeed(1),
	m_collectableCounter(0)
{}

Collectables::~Collectables()
{
	delete(m_gameManager);
}

void Collectables::InitializeValues() 
{
	m_collectableSpeed = 1;
	m_collectableCounter = 0;
}

void Collectables::InitializeCollectables(float _playerPosY)
{
	m_collectables.Initialize(m_gameManager->GetBackgroundWidth(), m_collectableWidth, m_collectableHeight, _playerPosY, m_collectableNumber, m_collectableRect);
}

void Collectables::RespawnCollectables() 
{
	m_collectables.Respawn(m_gameManager->GetBackgroundWidth(), m_collectableWidth, m_gameManager->GetBackgroundHeight(), m_collectableNumber, m_collectableRect);
}

void Collectables::ScrollCollectables(unsigned int _currentTimeCollectableScroll, unsigned int _lastTimeCollectableScroll, float _deltaTime)
{
	m_collectables.InteractablesScrollSpeed( _currentTimeCollectableScroll,_lastTimeCollectableScroll, m_collectableNumber, _deltaTime, m_collectableRect, m_collectableSpeed);
}

bool Collectables::CollectableCollision(SDL_Rect _player)
{
	m_collectables.Collision(m_collectableNumber, m_collectableRect, _player);
	if (m_collectables.m_collision)
	{
		m_collectableCounter += 1;
		m_collectables.m_collision = false;
		return true;
	}
	return false;
}