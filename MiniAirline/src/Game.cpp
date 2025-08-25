#include "Game.h"



const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);


Game::Game()
	: m_Window(sf::VideoMode({ 1920, 1080 }), "SFML Application")
	, m_leftKeyPressed(false)
	, m_rightKeyPressed(false)
	, m_upKeyPressed(false)
	, m_downKeyPressed(false)
	, m_World(m_Window)
	, m_Player()
{
	m_Window.setVerticalSyncEnabled(true);
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
			update(TimePerFrame);
		}
		render();
	}
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





