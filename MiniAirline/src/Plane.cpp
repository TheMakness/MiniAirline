#include "Plane.h"

Plane::Plane(sf::Vector2f pos, sf::Vector2f vel)
	: m_Position(pos),
	m_Velocity(vel),
	m_Color(sf::Color::Blue)
{
	m_Texture = new sf::Texture;
	

	if (!m_Texture->loadFromFile("media/textures/plane.png"))
	{
		std::cout << "Texture loading error" << std::endl;
	}

	m_Sprite = new sf::Sprite(*m_Texture);
	m_Sprite->setTexture(*m_Texture);

	m_Sprite->setPosition(m_Position);
	m_Sprite->setColor(m_Color);
	m_Sprite->setScale({0.2,0.2});
}

Plane::~Plane()
{
	delete m_Texture;
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


