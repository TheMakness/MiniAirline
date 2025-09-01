#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture):
	m_Sprite(texture)
{

}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect):
	m_Sprite(texture, rect)
{

}

const sf::Sprite& SpriteNode::getSprite()
{
	return m_Sprite;
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite, states);
}
