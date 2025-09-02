#pragma once
#include <SFML\Graphics.hpp>
#include "Aircraft.h"
#include "World.h"


class Game
{
public:
	Game();
	void run();

private:
	void processInput();
	void update(sf::Time deltaTime);
	void render();

private:
	sf::RenderWindow m_Window;
	World m_World;
	Player m_Player;
};
