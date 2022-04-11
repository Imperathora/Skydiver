#include "GameManager.h"

GameManager::GameManager() :
	m_renderer(nullptr),
	m_window(nullptr),
	m_backgroundWidth(800),
	m_backgroundHeight(600),
	UI(this),
	m_backgroundSurface(nullptr),
	m_backgroundTexture(nullptr),
	m_backgroundRect(),
	m_backgroundRect2(),
	m_playerSurface(nullptr),
	m_playerTexture(nullptr),
	deltaTime(),
	m_lastTime(),
	m_startTime(),
	m_currentTime(),
	m_inputManager(this),
	m_player(this),
	m_backgroundScrollingOffset(0),
	m_backgroundScrollSpeed(100.f),
	m_collectableSurface(nullptr),
	m_collectableTexture(nullptr),
	m_healthSurface(nullptr),
	m_healthLostSurface(nullptr),
	m_healthTexture(nullptr),
	m_healthLostTexture(nullptr),
	m_enemySurface(nullptr),
	m_enemyTexture(nullptr),
	m_lastTimeInteractableScroll(0),
	m_currentTimeInteractableScroll(0),
	m_collectableCollison(false),
	m_enemy(this),
	m_healthLost(false),
	m_collectable(this),
	m_timeInSeconds(0),
	m_running(false)

{
	IMG_Init(IMG_INIT_PNG);
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
}

GameManager::~GameManager()
{}

void GameManager::Initialize()
{
	deltaTime = 0;
	m_lastTime = 0;
	m_startTime = 0;
	m_currentTime = 0;
	m_backgroundScrollingOffset = 0;
	m_backgroundScrollSpeed = 100.f;
	m_lastTimeInteractableScroll = 0;
	m_currentTimeInteractableScroll = 0;
	m_timeInSeconds = 0;
	m_player.InitializeValues();
	m_collectable.InitializeValues();
}


void GameManager::SetBackgroundWidth() { _bgWidth = m_backgroundWidth; }

int  GameManager::GetBackgroundWidth() { return _bgWidth; }

void  GameManager::SetBackgroundHeight() { _bgHeight = m_backgroundHeight; }

int  GameManager::GetBackgroundHeight() { return _bgHeight; }

void GameManager::LoadGame()
{
	Destroy();
	m_running = true;
	srand(_getpid() + time_t(NULL));

	if (m_window == NULL && m_renderer == NULL)
	{
		m_window = SDL_CreateWindow("Skydiver", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_backgroundWidth, m_backgroundHeight, 0);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	}
	SetBackgroundWidth();
	SetBackgroundHeight();
	Initialize();
	LoadImages();
	CreateTextures();
	m_player.LoadPlayer(m_backgroundWidth, m_backgroundHeight);
	m_player.InitializeHealth();
	m_enemy.InitializeEnemies(m_player.m_playerPosY);
	m_collectable.InitializeCollectables(m_player.m_playerPosY);
	LoadUI();
	m_startTime = SDL_GetTicks();
}


void GameManager::LoadImages()
{
	m_playerSurface = IMG_Load("player.png");
	m_collectableSurface = IMG_Load("collectable.png");
	m_enemySurface = IMG_Load("enemy.png");
	m_healthSurface = IMG_Load("health.png");
	m_healthLostSurface = IMG_Load("healthlost.png");
	m_backgroundSurface = IMG_Load("clouds.png");
}

void GameManager::CreateTextures()
{
	m_playerTexture = SDL_CreateTextureFromSurface(m_renderer, m_playerSurface);
	m_collectableTexture = SDL_CreateTextureFromSurface(m_renderer, m_collectableSurface);
	m_enemyTexture = SDL_CreateTextureFromSurface(m_renderer, m_enemySurface);
	m_healthTexture = SDL_CreateTextureFromSurface(m_renderer, m_healthSurface);
	m_backgroundTexture = SDL_CreateTextureFromSurface(m_renderer, m_backgroundSurface);
	m_healthLostTexture = SDL_CreateTextureFromSurface(m_renderer, m_healthSurface);

}

void GameManager::LoadUI()
{
	UI.ScoreText();
	UI.CollectableText();
	UI.CollectablesScoreUI(m_collectable.m_collectableCounter);
	UI.TimeScoreUI(m_timeInSeconds);
}

void GameManager::Render()
{
	SDL_RenderCopy(m_renderer, m_backgroundTexture, NULL, &m_backgroundRect);
	SDL_RenderCopy(m_renderer, m_backgroundTexture, NULL, &m_backgroundRect2);

	for (int i = 0; i < m_collectable.m_collectableNumber; i++)
	{
		SDL_RenderCopy(m_renderer, m_collectableTexture, NULL, &m_collectable.m_collectableRect[i]);
	}

	for (int i = 0; i < m_enemy.m_enemiesNumber; i++)
	{
		SDL_RenderCopy(m_renderer, m_enemyTexture, NULL, &m_enemy.m_enemyRect[i]);
	}

	for (int i = 0; i < m_player.m_healthNumber; i++)
	{
		SDL_RenderCopy(m_renderer, m_healthTexture, NULL, &m_player.m_healthRect[i]);
	}

	if (m_healthLost)
	{
		for (int i = 0; i < m_player.m_playerHealth; i++)
		{
			SDL_RenderCopy(m_renderer, m_healthLostTexture, NULL, &m_player.m_healthRect[i]);
		}
	}

	SDL_RenderCopy(m_renderer, m_playerTexture, NULL, &m_player.m_playerRect);
	UI.DrawUI();

}


void GameManager::ChangeColor()
{
	SDL_SetTextureColorMod(m_healthLostTexture, 20, 20, 20);
	m_healthLost = true;
}


float GameManager::CalculateDeltaTime()
{
	m_currentTime = SDL_GetTicks();
	deltaTime = (float(m_currentTime) - float(m_startTime)) / 1000.f;
	m_startTime = m_currentTime;
	return deltaTime;
}

void GameManager::UpdateGame()
{
	CalculateDeltaTime();
	m_inputManager.EventHandler(deltaTime, m_backgroundWidth, &m_player);
	m_player.UpdatePlayerPosition();
	m_collectableCollison = m_collectable.CollectableCollision(m_player.m_playerRect);
	m_enemyCollision = m_enemy.EnemiesCollision(m_player.m_playerRect);
	if (m_collectableCollison)
	{
		UI.CollectablesScoreUI(m_collectable.m_collectableCounter);
	}

	if (m_enemyCollision)
	{
		m_player.m_playerHealth += 1;
		if (m_player.m_playerHealth <= m_player.m_healthNumber)
		{
			ChangeColor();
		}

	}

	m_currentTimeInteractableScroll = SDL_GetTicks();
	BackgroundScrollUpdate();

	if (m_player.m_playerHealth < m_player.m_healthNumber)
	{
		if (m_currentTime > m_lastTime + 1000) {
			m_lastTime = m_currentTime;
			m_timeInSeconds += 1;
			UI.TimeScoreUI(m_timeInSeconds);
		}
	}

	m_collectable.ScrollCollectables(m_currentTimeInteractableScroll, m_lastTimeInteractableScroll, deltaTime);
	m_collectable.RespawnCollectables();

	m_enemy.ScrollEnemies(m_currentTimeInteractableScroll, m_lastTimeInteractableScroll, deltaTime);
	m_enemy.RespawnEnemies();

	if (m_player.m_playerHealth == m_player.m_healthNumber)
	{
		GameOver();
	}

	if (m_player.m_playerHealth < m_player.m_healthNumber)
	{
		Render();
	}

}


void GameManager::BackgroundScrollUpdate()
{
	m_backgroundScrollingOffset -= deltaTime * m_backgroundScrollSpeed;
	m_backgroundRect.x = 0;
	m_backgroundRect.y = (int)m_backgroundScrollingOffset;
	m_backgroundRect.w = m_backgroundWidth;
	m_backgroundRect.h = m_backgroundHeight;

	m_backgroundRect2.x = 0;
	m_backgroundRect2.y = m_backgroundHeight + (int)m_backgroundScrollingOffset;
	m_backgroundRect2.w = m_backgroundWidth;
	m_backgroundRect2.h = m_backgroundHeight;

	if (m_backgroundRect.y <= -m_backgroundHeight)
	{
		m_backgroundScrollingOffset = 0;
		m_backgroundRect.y = 0 + (int)m_backgroundScrollingOffset;
	}
}

void GameManager::Timer(Uint32 interval)
{
	struct Container
	{
		static Uint32 TimerCallback(Uint32 interval, void* param)
		{
			SDL_Event event;
			event.type = SDL_USEREVENT;
			event.user.code = 42;
			SDL_PushEvent(&event);
			return 0;
		}
	};

	SDL_AddTimer(interval, Container::TimerCallback, NULL);

	SDL_Event event;
	while (SDL_WaitEvent(&event))
	{
		if (event.type == SDL_USEREVENT && event.user.code == 42)
			break;
	}
}


void GameManager::Destroy()
{
	SDL_DestroyTexture(m_playerTexture);
	SDL_DestroyTexture(m_backgroundTexture);
	SDL_DestroyTexture(m_collectableTexture);
	SDL_DestroyTexture(m_enemyTexture);
	SDL_DestroyTexture(m_healthTexture);
	SDL_DestroyTexture(m_healthLostTexture);

	SDL_FreeSurface(m_backgroundSurface);
	SDL_FreeSurface(m_playerSurface);
	SDL_FreeSurface(m_collectableSurface);
	SDL_FreeSurface(m_enemySurface);
	SDL_FreeSurface(m_healthSurface);

	UI.DestroyUI();
}

void  GameManager::GameOver()
{
	SDL_Rect m_highscoreRect;
	m_highscoreRect = { 0,0,m_backgroundWidth,m_backgroundHeight };

	int m_gameOverTimer = 0;
	std::string s_time = std::to_string(m_timeInSeconds);
	UI.GameOverUI(m_backgroundHeight, s_time);
	while (m_gameOverTimer <= 3)
	{
		Timer(1000);
		SDL_RenderClear(m_renderer);
		UI.DrawGameOverUI(m_highscoreRect);
		SDL_RenderPresent(m_renderer);

		m_gameOverTimer++;
	}
	LoadGame();
}