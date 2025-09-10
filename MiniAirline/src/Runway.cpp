#include "Runway.h"

Runway::Runway(sf::Vector2f size, sf::Vector2f position, sf::Angle angle)
	: RectangleShapeNode(size)
	, m_RightPoint(50)
	, m_LeftPoint(50)
{
	m_RightPoint.setOrigin({ m_RightPoint.getRadius(), m_RightPoint.getRadius() });
	m_LeftPoint.setOrigin({ m_LeftPoint.getRadius(), m_LeftPoint.getRadius() });

	setPosition(position);
	setRotation(angle);

	//Set points positions relative to runway
	m_RightPoint.setPosition({ position.x + size.x, position.y + size.y / 2 });
	m_LeftPoint.setPosition({ position.x , position.y + size.y / 2 });

	// Rotate points around center of runway
	m_RightPoint.setPosition(sf::Transform().rotate(angle, position).transformPoint(m_RightPoint.getPosition()));
	m_LeftPoint.setPosition(sf::Transform().rotate(angle, position).transformPoint(m_LeftPoint.getPosition()));

	//Set points colors
	m_RightPoint.setFillColor(sf::Color::Red);
	m_LeftPoint.setFillColor(sf::Color::Green);

}

void Runway::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	RectangleShapeNode::drawCurrent(target, states);
	target.draw(m_LeftPoint, states);
	target.draw(m_RightPoint, states);
}

bool Runway::isAtMousePos(sf::Vector2f mousePos)
{
	return (m_RightPoint.getGlobalBounds().contains(mousePos) || m_LeftPoint.getGlobalBounds().contains(mousePos));
}
