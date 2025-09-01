#pragma once

#include <SFML/Graphics.hpp>
#include "RectangleShapeNode.h"

class Runway : public RectangleShapeNode
{
public:
	Runway(sf::Vector2f size, sf::Vector2f position, sf::Angle angle);
};

