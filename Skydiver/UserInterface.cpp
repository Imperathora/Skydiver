#include "UserInterface.h"
#include "GameManager.h"

UserInterface::UserInterface(GameManager* _gameManager) :
	m_gameManager(_gameManager),
	m_fontsize(24),
	m_black({ 0,0,0 }),
	m_fontpath("arial.ttf"),
	m_white({ 255,255,255 }),
	m_gameOverFontsize(30),
	m_collectableTextWidth(0),
	m_collectableTextHeight(0),
	m_textRect(),
	m_textFontTexture(nullptr),
	m_scoreTextSurface(nullptr),
	m_collectableTextRect(),
	m_collectableTextFontTexture(nullptr),
	m_collectableTextSurface(nullptr),
	m_highscoreTextRect(),
	m_highscoreScoreRect(),
	m_highscoreTimeTextFontTexture(nullptr),
	m_highscoreTimeScoreFontTexture(nullptr),
	m_highscoreTextSurface(nullptr),
	m_highscoreScoreSurface(nullptr),
	m_collectableScoreRect(),
	m_colletableScoreSurface(nullptr),
	m_collectableScoreFontTexture(nullptr),
	m_timeTextRect(),
	m_timeSurface(nullptr),
	m_timeFontTexture(nullptr),
	m_highscoreSurface(nullptr),
	m_highscoreTexture(nullptr)
{}


UserInterface::~UserInterface()
{
	delete(m_gameManager);
}

void UserInterface::DestroyUI()
{
	SDL_DestroyTexture(m_textFontTexture);
	SDL_DestroyTexture(m_collectableTextFontTexture);
	SDL_DestroyTexture(m_highscoreTimeTextFontTexture);
	SDL_DestroyTexture(m_highscoreTimeScoreFontTexture);
	SDL_DestroyTexture(m_collectableScoreFontTexture);
	SDL_DestroyTexture(m_timeFontTexture);
	SDL_DestroyTexture(m_highscoreTexture);
}

void UserInterface::DrawUI()
{
	SDL_RenderCopy(m_gameManager->m_renderer, m_textFontTexture, NULL, &m_textRect);
	SDL_RenderCopy(m_gameManager->m_renderer, m_collectableTextFontTexture, NULL, &m_collectableTextRect);
	SDL_RenderCopy(m_gameManager->m_renderer, m_collectableScoreFontTexture, NULL, &m_collectableScoreRect);
	SDL_RenderCopy(m_gameManager->m_renderer, m_timeFontTexture, NULL, &m_timeTextRect);
}

void UserInterface::DrawGameOverUI(SDL_Rect _highscoreRect)
{
	SDL_RenderCopy(m_gameManager->m_renderer, m_highscoreTexture, NULL, &_highscoreRect);
	SDL_RenderCopy(m_gameManager->m_renderer, m_highscoreTimeTextFontTexture, NULL, &m_highscoreTextRect);
	SDL_RenderCopy(m_gameManager->m_renderer, m_highscoreTimeScoreFontTexture, NULL, &m_highscoreScoreRect);
}

void UserInterface::ScoreText()
{
	TTF_Font* m_font = TTF_OpenFont(m_fontpath.c_str(), m_fontsize);
	int m_textPosX = 10;
	int m_textPosY = 20;
	int m_scoreTextWidth = 0;
	int m_scoreTextHeight = 0;
	std::string m_text = "Score: ";
	m_scoreTextSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_black);
	m_textFontTexture = SDL_CreateTextureFromSurface(m_gameManager->m_renderer, m_scoreTextSurface);
	m_scoreTextWidth = m_scoreTextSurface->w;
	m_scoreTextHeight = m_scoreTextSurface->h;
	m_textRect = { m_textPosX, m_textPosY, m_scoreTextWidth, m_scoreTextHeight };
	SDL_FreeSurface(m_scoreTextSurface);
	TTF_CloseFont(m_font);
}

void UserInterface::CollectableText()
{
	TTF_Font* m_font = TTF_OpenFont(m_fontpath.c_str(), m_fontsize);
	int m_collectibleTextPosX = 10;
	int m_collectibleTextPosY = 50;
	std::string m_collectableText = "Collectables: ";
	m_collectableTextSurface = TTF_RenderText_Solid(m_font, m_collectableText.c_str(), m_black);
	m_collectableTextFontTexture = SDL_CreateTextureFromSurface(m_gameManager->m_renderer, m_collectableTextSurface);
	m_collectableTextRect = { m_collectibleTextPosX, m_collectibleTextPosY, m_collectableTextSurface->w, m_collectableTextSurface->h };
	SDL_FreeSurface(m_collectableTextSurface);
	TTF_CloseFont(m_font);
}

void UserInterface::GameOverUI(const int _backgroundHeight, const std::string _timeScore)
{
	TTF_Font* m_font = TTF_OpenFont(m_fontpath.c_str(), m_gameOverFontsize);
	int m_highscoreTextPosX = 200;
	int m_highscoreTextPosY = _backgroundHeight / 2;
	int m_highscoreScorePosX = 500;
	int m_highscoreScorePosY = m_highscoreTextPosY;

	int m_highscoreTextWidth = 0;
	int m_highscoreTextHeight = 0;
	int m_highscoreScoreWidth = 0;
	int m_highscoreScoreHeight = 0;

	m_highscoreSurface = IMG_Load("gameover.png");

	m_highscoreTexture = SDL_CreateTextureFromSurface(m_gameManager->m_renderer, m_highscoreSurface);

	std::string m_highscoreText = "Your Highscore is ";
	m_highscoreTextSurface = TTF_RenderText_Solid(m_font, m_highscoreText.c_str(), m_white);
	m_highscoreScoreSurface = TTF_RenderText_Solid(m_font, _timeScore.c_str(), m_white);

	m_highscoreTimeTextFontTexture = SDL_CreateTextureFromSurface(m_gameManager->m_renderer, m_highscoreTextSurface);
	m_highscoreTimeScoreFontTexture = SDL_CreateTextureFromSurface(m_gameManager->m_renderer, m_highscoreScoreSurface);

	m_highscoreTextWidth = m_highscoreTextSurface->w;
	m_highscoreTextHeight = m_highscoreTextSurface->h;
	m_highscoreScoreWidth = m_highscoreScoreSurface->w;
	m_highscoreScoreHeight = m_highscoreScoreSurface->h;

	m_highscoreTextRect = { m_highscoreTextPosX, m_highscoreTextPosY, m_highscoreTextWidth, m_highscoreTextHeight };
	m_highscoreScoreRect = { m_highscoreScorePosX, m_highscoreScorePosY, m_highscoreScoreWidth, m_highscoreScoreHeight };

	SDL_FreeSurface(m_highscoreSurface);
	SDL_FreeSurface(m_highscoreTextSurface);
	SDL_FreeSurface(m_highscoreScoreSurface);
	TTF_CloseFont(m_font);
}

void UserInterface::CollectablesScoreUI(int _collectableCounter)
{
	TTF_Font* m_font = TTF_OpenFont(m_fontpath.c_str(), m_fontsize);
	int m_collectableScoreWidth = 0;
	int m_collectableScoreHeight = 0;
	int m_collectibleScorePosX = 150;
	int m_collectibleScorePosY = 50;
	std::stringstream m_collectableScore;
	m_collectableScore << _collectableCounter;
	std::string m_collectableScoreNum = m_collectableScore.str().c_str();
	m_colletableScoreSurface = TTF_RenderText_Solid(m_font, m_collectableScoreNum.c_str(), m_black);
	m_collectableScoreFontTexture = SDL_CreateTextureFromSurface(m_gameManager->m_renderer, m_colletableScoreSurface);
	m_collectableScoreWidth = m_colletableScoreSurface->w;
	m_collectableScoreHeight = m_colletableScoreSurface->h;
	m_collectableScoreRect = { m_collectibleScorePosX, m_collectibleScorePosY, m_collectableScoreWidth, m_collectableScoreHeight };
	SDL_FreeSurface(m_colletableScoreSurface);
	TTF_CloseFont(m_font);
}

void UserInterface::TimeScoreUI(int _timer)
{
	TTF_Font* m_font = TTF_OpenFont(m_fontpath.c_str(), m_fontsize);
	int m_timeTextPosX = 100;
	int m_timeTextPosY = 20;
	int m_timeTextWidth = 0;
	int m_timeTextHeight = 0;
	std::stringstream m_timeScore;
	m_timeScore << _timer;
	std::string m_timeText = m_timeScore.str().c_str();
	m_timeSurface = TTF_RenderText_Solid(m_font, m_timeText.c_str(), m_black);
	m_timeFontTexture = SDL_CreateTextureFromSurface(m_gameManager->m_renderer, m_timeSurface);
	m_timeTextWidth = m_timeSurface->w;
	m_timeTextHeight = m_timeSurface->h;
	m_timeTextRect = { m_timeTextPosX, m_timeTextPosY, m_timeTextWidth, m_timeTextHeight };
	SDL_FreeSurface(m_timeSurface);
	TTF_CloseFont(m_font);
}
