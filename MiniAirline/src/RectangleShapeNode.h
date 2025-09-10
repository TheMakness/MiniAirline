#pragma once
#include "SceneNode.h"

class RectangleShapeNode : public SceneNode
{
public :
	RectangleShapeNode();
	RectangleShapeNode(sf::Vector2f size, sf::Vector2f position);
	RectangleShapeNode(sf::Vector2f size, sf::Vector2f position, sf::Angle angle);
	RectangleShapeNode(sf::Vector2f size);
	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	void setFillColor(sf::Color color);
	void setRotation(sf::Angle angle);
	

protected:
	sf::RectangleShape m_Shape;

protected:
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
};

