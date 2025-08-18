#pragma once
#include <string>
#include <iostream>
#include "Waypoint.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include "ResourceHolder.h"

class Plane : public sf::Drawable
{
public:
	Plane(sf::Vector2f pos, sf::Vector2f vel);
	~Plane();
	void move(const sf::Vector2f& offset);
	const sf::Vector2f& getVelocity();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::string m_Name;
	std::string m_Callsign;
	sf::Color m_Color;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Position = sf::Vector2f(50,50);
	ResourceHolder <sf::Texture, std::string> textures;
	sf::Sprite* m_Sprite;
	
	
};
