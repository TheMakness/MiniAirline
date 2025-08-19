#include "Entity.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"



void Entity::SetVelocity(sf::Vector2f velocity)
{
	m_Velocity = velocity;
}

void Entity::SetVelocity(float vx, float vy)
{
	m_Velocity = { vx,vy };
}


const sf::Vector2f& Entity::getVelocity() const
{
	return m_Velocity;
}

void Entity::updateCurrent(sf::Time deltaTime)
{
		move(m_Velocity * deltaTime.asSeconds());
}




