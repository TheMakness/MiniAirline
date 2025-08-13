#include "Game.h"

Game::Game()
	: m_Window(sf::VideoMode({ 1920, 1080 }), "SFML Application")
	, m_Player()
	, m_PlayerSpeed(100.f)
	, m_leftKeyPressed(false)
	, m_rightKeyPressed(false)
	, m_upKeyPressed(false)
	, m_downKeyPressed(false)
{
	m_Player.setRadius(40.f);
	sf::Vector2u center = m_Window.getSize();
	center.x /= 2;
	center.y /= 2;
	m_Player.setPosition({(float)center.x,(float)center.y});
	m_Player.setFillColor(sf::Color::Cyan);
}

void Game::run()
{
	sf::Clock clock;
	while (m_Window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		processEvents();
		update(deltaTime);
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
	sf::Vector2f movement(0.f, 0.f);
	if (m_upKeyPressed)
		movement.y -= m_PlayerSpeed;
	if (m_downKeyPressed)
		movement.y += m_PlayerSpeed;
	if (m_leftKeyPressed)
		movement.x -= m_PlayerSpeed;
	if (m_rightKeyPressed)
		movement.x += m_PlayerSpeed;
	m_Player.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
	m_Window.clear();
	m_Window.draw(m_Player);
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


