#pragma once
#include <string>
#include <iostream>
#include "Waypoint.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"


class Aircraft : public Entity
{
	
public:
	enum class Type {
		Civilian,
		Military,
	};

public:
	explicit Aircraft(Type type, const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
private:
	Type m_Type;
	sf::Sprite m_Sprite;
	std::string m_Callsign;
	sf::Color m_Color;
	TextureHolder m_Textures;
};
