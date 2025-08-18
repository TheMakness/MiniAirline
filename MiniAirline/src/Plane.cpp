#include "Plane.h"

Plane::Plane(sf::Vector2f pos, sf::Vector2f vel)
	: m_Position(pos),
	m_Velocity(vel),
	m_Color(sf::Color::Blue)
{
	textures.load("Airplane", "media/textures/plane.png");
	m_Sprite = new sf::Sprite(textures.get("Airplane"));

	m_Sprite->setPosition(m_Position);
	m_Sprite->setColor(m_Color);
	m_Sprite->setScale({0.2,0.2});
}

Plane::~Plane()
{
	delete m_Sprite;
}

void Plane::move(const sf::Vector2f& offset)
{
	m_Position += offset;
	m_Sprite->move(offset);
}

const sf::Vector2f& Plane::getVelocity()
{
	return m_Velocity;
}

void Plane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_Sprite);
}


