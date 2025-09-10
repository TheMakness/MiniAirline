#pragma once

#include <SFML/Graphics.hpp>
#include "RectangleShapeNode.h"

class Runway : public RectangleShapeNode
{
public:
	Runway(sf::Vector2f size, sf::Vector2f position, sf::Angle angle);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool isAtMousePos(sf::Vector2f mousePos);

private:
	sf::CircleShape m_RightPoint;
	sf::CircleShape m_LeftPoint;


};

