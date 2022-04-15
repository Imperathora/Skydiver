#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include "GameManager.h"


int main(int argc, char** argv)
{
	GameManager m_gameManager;
	m_gameManager.LoadGame();


	while (m_gameManager.m_running)
	{
		m_gameManager.UpdateGame();
		SDL_RenderPresent(m_gameManager.m_renderer);
		SDL_RenderClear(m_gameManager.m_renderer);

		

	}

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	return 0;
}