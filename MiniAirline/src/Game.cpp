#include "Game.h"

#define getRandom() static_cast <float> (rand()) / static_cast <float> (RAND_MAX)

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);



Game::Game()
	: m_Window(sf::VideoMode({ 1920, 1080 }), "SFML Application")
	, m_PlayerSpeed(100.f)
	, m_leftKeyPressed(false)
	, m_rightKeyPressed(false)
	, m_upKeyPressed(false)
	, m_downKeyPressed(false)
	, m_Planes (* new std::vector<Plane>())
{
	sf::Vector2u screenSize = m_Window.getSize();
	sf::Vector2u center = { screenSize.x/2,screenSize.y/2 };

	m_Planes.reserve(5);

	for (size_t i = 0; i < 5; i++)
	{
		m_Planes.emplace_back(Plane({ getRandom() * screenSize.x,getRandom() * screenSize.y }, { getRandom() * 50, getRandom() * 50 }));
	}


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
	for (size_t i = 0; i < m_Planes.size(); i++)
	{
		m_Planes[i].move(m_Planes[i].getVelocity() * deltaTime.asSeconds());
	}
	
}

void Game::render()
{
	m_Window.clear();
	for (size_t i = 0; i < m_Planes.size(); i++)
	{
		m_Window.draw(m_Planes[i].getShape());
	}
	
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


