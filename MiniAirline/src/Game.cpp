#include "Game.h"



const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
static Game* s_Instance = nullptr;

Game::Game()
	: m_Window(sf::VideoMode({ 1920, 1080 }), "SFML Application")
	, m_World(m_Window)
	,m_CurrentState(State::Game)
{
	m_Window.setVerticalSyncEnabled(true);
	m_Fonts.loadFont(Font::ID::Vercetti_Regular, "media/fonts/Vercetti-Regular.ttf");
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_Window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processInput();
			UpdateState(TimePerFrame);
		}
		render();
	}
}

Game* Game::getInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new Game();
	}
	return s_Instance;
}


 void Game::UpdateState(sf::Time deltaTime)
 {
	 switch (m_CurrentState)
	 {
	 case State::Game: update(deltaTime);
	 	break;

	 case State::Pause:
	 	break;

	 case State::GameOver:update(deltaTime);
		break;
	 default: ;
	 }
 }

 void Game::SwitchState(State newState)
 {
	 m_CurrentState = newState;
	 OnEnterState(newState);
 }

void Game::OnEnterState(State enterState)
{
	switch (m_CurrentState)
	{
		case State::Game:
			break;
		case State::Pause:
		break;
		case State::GameOver:
			printf("Game Over !");
		break;	
	}
}


 const State Game::getCurrentState() const
 {
	 return m_CurrentState;
 }


 void Game::processInput()
{

	CommandQueue& commands = m_World.getCommandQueue();

	while (const std::optional event = m_Window.pollEvent())
	{
		m_Player.handleEvent(event.value(), commands, m_World);

		if (event->is<sf::Event::Closed>())
			m_Window.close();
	}

	m_Player.handleRealtimeInput(commands, m_World);
}

void Game::update(sf::Time deltaTime)
{
	m_World.update(deltaTime);
}

void Game::render()
{
	m_Window.clear();
	m_World.draw();
	m_Window.display();
}







