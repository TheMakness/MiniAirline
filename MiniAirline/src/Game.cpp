#include "Game.h"



const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);


Game::Game()
	: m_Window(sf::VideoMode({ 1920, 1080 }), "SFML Application")
	, m_leftKeyPressed(false)
	, m_rightKeyPressed(false)
	, m_upKeyPressed(false)
	, m_downKeyPressed(false)
	,m_World(m_Window)
{
	m_Window.setVerticalSyncEnabled(true);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_Window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{

	while (const std::optional event = m_Window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_Window.close();
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			onKeyPressed(*keyPressed);
		else if (const auto* keyRelease = event->getIf<sf::Event::KeyReleased>())
			onKeyReleased(*keyRelease);
	}
}

void Game::update(sf::Time deltaTime)
{
	
}

void Game::render()
{
	m_Window.clear();
	m_World.draw();
	m_Window.display();
}

void Game::onKeyPressed(const sf::Event::KeyPressed& keyPressed)
{
		
	switch (keyPressed.scancode)
	{
	case sf::Keyboard::Scancode::Left:
		m_leftKeyPressed = true;
		break;
	case sf::Keyboard::Scancode::Right:
		m_rightKeyPressed = true;
		break;
	case sf::Keyboard::Scancode::Up:
		m_upKeyPressed = true;
		break;
	case sf::Keyboard::Scancode::Down:
		m_downKeyPressed = true;
		break;
	}
}

void Game::onKeyReleased(const sf::Event::KeyReleased& keyReleased)
{
	switch (keyReleased.scancode)
	{
	case sf::Keyboard::Scancode::Left:
		m_leftKeyPressed = false;
		break;
	case sf::Keyboard::Scancode::Right:
		m_rightKeyPressed = false;
		break;
	case sf::Keyboard::Scancode::Up:
		m_upKeyPressed = false;
		break;
	case sf::Keyboard::Scancode::Down:
		m_downKeyPressed = false;
		break;
	}
}


