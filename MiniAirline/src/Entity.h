#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "SceneNode.h"

class Entity : public SceneNode
{
public:

	void SetVelocity(sf::Vector2f velocity);
	void SetVelocity(float vx, float vy);
	const sf::Vector2f& getVelocity() const;
	virtual void updateCurrent(sf::Time deltaTime) override;
	
protected:
	sf::Vector2f m_Velocity;

};

