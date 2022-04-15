#include "InputManager.h"



InputManager::InputManager(GameManager* _gameManager) :
	m_gameManager(_gameManager),
	m_event()
{}

InputManager::~InputManager()
{}

void InputManager::EventHandler(float deltaTime, int _backgroundWidth, Player* _player)
{
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	SDL_PollEvent(&m_event);

	if (m_event.type == SDL_KEYDOWN)
	{
		if (keystates[SDL_SCANCODE_LEFT] && _player->m_playerPosX > 0)
		{
			_player->m_playerPosX = _player->m_playerPosX - 400.f * deltaTime;

		}
		if (keystates[SDL_SCANCODE_RIGHT] && _player->m_playerPosX < _backgroundWidth - _player->m_playerRect.w)
		{
			_player->m_playerPosX = _player->m_playerPosX + 400.f * deltaTime;
		}
	}
}
