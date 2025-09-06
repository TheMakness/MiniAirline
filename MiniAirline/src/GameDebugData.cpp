#include "GameDebugData.h"

#include "Game.h"

GameDebugData::GameDebugData(const sf::Font& font)
	: TextNode(font, 20)
{
	setColor(sf::Color::White);
}

void GameDebugData::updateCurrent(sf::Time dt)
{
	std::string debugString;
	debugString += "State: " + toString(Game::getInstance()->getCurrentState()) + "\n";
	setText(debugString);
	//Set position top left corner
	setPosition(sf::Vector2f(10, 10));
}

