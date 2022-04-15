//#include "GenericInteractables.h"
//
//template <class T>
//void GenericInteractables<T>::Respawn(int _backgroundWidth, int _interactableWidth, int _backgroundHeight, int const _size)
//{
//	for (int i = 0; i < _size; i++)
//	{
//		if (elems[i].y <= 0)
//		{
//			elems[i].x = rand() % (((_backgroundWidth - _interactableWidth) - 0) + 1) + 0;
//			elems[i].y = _backgroundHeight + 20;
//		}
//		if (elems[i].x > _backgroundWidth)
//		{
//			elems[i].x = rand() % (((_backgroundWidth - _interactableWidth) - 0) + 1) + 0;
//			elems[i].y = _backgroundHeight + 20;
//		}
//	}
//}
//
//
//template <class T>
//void GenericInteractables<T>::Initialize(int _backgroundWidth, int _interactableWidth, int _interactableHeight, float _playerPosY, int const _size)
//{
//		for (int i = 0; i < _size; i++)
//	{
//		elems[i] = { rand() % (((_backgroundWidth - _interactableWidth) - 0) + 1) + 0,rand() % ((0 - (int)_playerPosY + _interactableHeight) + 1) + (int)_playerPosY + _interactableHeight ,_interactableWidth,_interactableHeight };
//	}
//}
//
////template <class T>
////void GenericInteractables<T>::Collision(SDL_Rect _player, int const _size)
////{
////	bool a;
////		for (int i = 0; i < _size; i++)
////		{
////			a = GameManager.CollisionDetection(elems[i], _player);
////			if (a == true)
////			{
////				elems[i].x = 3000;
////				&m_collision = true;
////				//if (m_enemyCollision)
////				//{
////				//	m_playerHealth += 1;
////				//	if (m_playerHealth <= m_healthNumber)
////				//	{
////				//		ChangeColor();
////				//	}
////				//	m_enemyCollision = false;
////				//}
////			}
////			a = false;
////		}
////}