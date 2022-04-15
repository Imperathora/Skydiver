#pragma once
#include <iostream>
#include "SDL.h"



template <class T>
class GenericInteractables
{
public:

	bool m_collision;

	void Respawn(int _backgroundWidth, int _interactableWidth, int _backgroundHeight, int const _size, T _type[])
	{
		for (int i = 0; i < _size; i++)
		{
			if (_type[i].y <= 0)
			{
				_type[i].x = rand() % (((_backgroundWidth - _interactableWidth) - 0) + 1) + 0;
				_type[i].y = _backgroundHeight + 20;
			}
			if (_type[i].x > _backgroundWidth)
			{
				_type[i].x = rand() % (((_backgroundWidth - _interactableWidth) - 0) + 1) + 0;
				_type[i].y = _backgroundHeight + 20;
			}
		}
	}

	void Initialize(int _backgroundWidth, int _interactableWidth, int _interactableHeight, float _playerPosY, int const _size, T _type[])
	{

		for (int i = 0; i < _size; i++)
		{
			_type[i] = { rand() % (((_backgroundWidth - _interactableWidth) - 0) + 1) + 0,rand() % ((0 - (int)_playerPosY + _interactableHeight) + 1) + (int)_playerPosY + _interactableHeight , _interactableWidth ,_interactableHeight };
		}
	}

	void InteractablesScrollSpeed(unsigned int _currentTimeCollectableScroll, unsigned int _lastTimeCollectableScroll, int const _size, float _deltaTime, T _type[], int _speed)
	{
		if (_currentTimeCollectableScroll > _lastTimeCollectableScroll + 5) {

			_lastTimeCollectableScroll = _currentTimeCollectableScroll;
			for (int i = 0; i < _size; i++)
			{
				_type[i].y -= _deltaTime * _speed;
			}
		}
	}

	void Collision(int const _size, T _type[], T _player)
	{
		bool a;
		for (int i = 0; i < _size; i++)
		{

			a = CollisionDetection(_type[i],_player);
			if (a == true)
			{
				_type[i].x = 3000;
				m_collision = true;
			}
			a = false;
		}
	}

	bool CollisionDetection(T rect1, T rect2)
	{
		if (rect2.x - 5 < rect1.x + rect1.w && rect2.x - 5 + rect2.w - 5 > rect1.x&& rect2.y - 5 + rect2.h - 5 > rect1.y&& rect2.y - 5 < rect1.y + rect1.h)
		{
			return true;
		}
		return false;
	}
};

