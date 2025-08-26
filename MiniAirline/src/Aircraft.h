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
#include "Arrow.h"


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
	virtual unsigned int getCategory() const override;
	bool isSelected();
	void setDesiredVelocity(sf::Vector2f destination);
	void updateArrow(sf::Vector2f targetPosition);
	bool isAtMousePos(sf::Vector2f mousePos);
	void select();
	void unselect();
	void setMousePos(sf::Vector2f mousePos);


private:
	virtual void updateCurrent(sf::Time deltaTime) override;
	virtual void lerpVelocity(sf::Time deltaTime);
	
private:
	Type m_Type;
	sf::Sprite m_Sprite;
	std::string m_Callsign;
	sf::Color m_Color;
	TextureHolder m_Textures;

	sf::Vector2f m_DesiredVelocity;
	sf::Vector2f m_CurrentMousePos;

	Category::Type m_CurrentCategory = Category::Aircraft;

	Arrow m_Arrow;
	sf::CircleShape m_Circle;

	float m_RotationSpeed = .5f;

	bool b_Selected = false;
};
