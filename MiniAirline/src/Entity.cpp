#include "Entity.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"


void Entity::AlignToVelocity()
{
	if (!m_Velocity.length() > 0)
		return;
	auto direction = m_Velocity.normalized();
	sf::Angle rotAngle = sf::degrees(atan2(direction.y, direction.x) * (180 / 3.14159265359) + 90);
	setRotation(rotAngle);
}

void Entity::SetVelocity(sf::Vector2f velocity)
{
	m_Velocity = velocity;
}

void Entity::SetVelocity(float vx, float vy)
{
	m_Velocity = { vx,vy };
}

void Entity::accelerate(sf::Vector2f velocity)
{
	m_Velocity += velocity;
}


const sf::Vector2f& Entity::getVelocity() const
{
	return m_Velocity;
}

void Entity::updateCurrent(sf::Time deltaTime)
{
		move(m_Velocity * deltaTime.asSeconds());
}






