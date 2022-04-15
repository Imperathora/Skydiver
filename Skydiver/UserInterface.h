#pragma once
#include <string>
#include <sstream>
#include "SDL.h"
#include "SDL_ttf.h"
#include <SDL_image.h>

class GameManager;
class UserInterface
{
public:
	UserInterface(GameManager* _gameManager);
	~UserInterface();


	void CollectableText() ;
	void ScoreText();
	void GameOverUI(const int _backgroundHeight, const std::string _timeScore);
	void CollectablesScoreUI(int _collectableCounter) ;
	void TimeScoreUI(int _timer) ;
	void DrawUI();
	void DrawGameOverUI(SDL_Rect _highscoreRect);
	int  m_collectableTextWidth;
	int  m_collectableTextHeight;
	SDL_Rect m_textRect;
	SDL_Texture* m_textFontTexture;
	SDL_Surface* m_scoreTextSurface;

	SDL_Rect m_collectableTextRect;
	SDL_Texture* m_collectableTextFontTexture;
	SDL_Surface* m_collectableTextSurface;

	SDL_Rect m_highscoreTextRect;
	SDL_Rect m_highscoreScoreRect;
	SDL_Texture* m_highscoreTimeTextFontTexture;
	SDL_Texture* m_highscoreTimeScoreFontTexture;
	SDL_Surface* m_highscoreTextSurface;
	SDL_Surface* m_highscoreScoreSurface;


	SDL_Rect m_collectableScoreRect;
	SDL_Surface* m_colletableScoreSurface;
	SDL_Texture* m_collectableScoreFontTexture;

	SDL_Rect m_timeTextRect;
	SDL_Surface* m_timeSurface;
	SDL_Texture* m_timeFontTexture;

	SDL_Surface* m_highscoreSurface;
	SDL_Texture* m_highscoreTexture;
	void DestroyUI();


private:
	GameManager* m_gameManager;
	int m_fontsize;
	int m_gameOverFontsize;
	SDL_Color m_black;
	SDL_Color m_white;
	std::string m_fontpath;

};
