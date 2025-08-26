#pragma once

#include <SFML/Graphics.hpp>



class Utils
{
public:
	static sf::Vector2f lerp(sf::Vector2f source, sf::Vector2f target, float alpha);
	static sf::Vector2f slerp(sf::Vector2f source, sf::Vector2f target, float alpha);
};

