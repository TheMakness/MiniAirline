#pragma once
#include <SFML\Graphics.hpp>
#include "Plane.h"


class Game
{
public:
	Game();
	~Game();
	void run();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void onKeyPressed(const sf::Event::KeyPressed& keyPressed);
	void onKeyReleased(const sf::Event::KeyReleased& keyReleased);

private:
	sf::RenderWindow m_Window;
	std::vector<Plane*> m_Planes;
	float m_PlayerSpeed;

	bool m_upKeyPressed, m_downKeyPressed, m_leftKeyPressed, m_rightKeyPressed;
};
