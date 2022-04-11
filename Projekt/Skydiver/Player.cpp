#include "Player.h"
#include "GameManager.h"


Player::Player() :
	m_playerPosX(),
	m_playerPosY(),
	m_playerRect(),
	m_healthNumber(3),
	m_healthWidth(40),
	m_healthHeight(40),
	m_playerHealth(0)
{}

Player::Player(GameManager* _gameManager) :
	m_gameManager(_gameManager),
	m_playerPosX(),
	m_playerPosY(),
	m_playerRect(),
	m_healthNumber(3),
	m_healthWidth(40),
	m_healthHeight(40),
	m_playerHealth(0)
{}

Player::~Player()
{
	delete(m_gameManager);
}

void Player::LoadPlayer(const int _backgroundWidth, const int _backgroundHeight)
{
	m_playerPosX = float(_backgroundWidth) / 2;
	m_playerPosY = float(_backgroundHeight) / 2;
}

void Player::InitializeValues()
{
	m_playerHealth = 0;
}

void Player::UpdatePlayerPosition()
{
	m_playerRect = { int(m_playerPosX), int(m_playerPosY),50,65 };
}

void Player::InitializeHealth()
{
	for (int i = 0; i < m_healthNumber; i++)
	{
		m_healthRect[i] = { m_gameManager->GetBackgroundWidth() - 50 * (i + 1), 50 ,m_healthWidth,m_healthHeight };
	}
}

