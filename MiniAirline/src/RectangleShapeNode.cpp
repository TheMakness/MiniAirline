#include "RectangleShapeNode.h"

RectangleShapeNode::RectangleShapeNode(sf::Vector2f size)
{
	setSize(size);
}

RectangleShapeNode::RectangleShapeNode()
{
}

RectangleShapeNode::RectangleShapeNode(sf::Vector2f size, sf::Vector2f position)
{
	setSize(size);
	setPosition(position);
}

RectangleShapeNode::RectangleShapeNode(sf::Vector2f size, sf::Vector2f position, sf::Angle angle)
{
	setSize(size);
	setPosition(position);
	
}

void RectangleShapeNode::setPosition(sf::Vector2f position)
{
	m_Shape.setPosition(position);
}
void RectangleShapeNode::setSize(sf::Vector2f size)
{
	m_Shape.setSize(size);
}

void RectangleShapeNode::setRotation(sf::Angle angle)
{
	m_Shape.setRotation(angle);
}


void RectangleShapeNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Shape, states);
}

void  RectangleShapeNode::setFillColor(sf::Color color)
{
	m_Shape.setFillColor(color);
}