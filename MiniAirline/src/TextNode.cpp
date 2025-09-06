#include "TextNode.h"

TextNode::TextNode(const sf::Font& font, uint8_t size)
	:m_Text(font," ",size)
{
	
}

TextNode::TextNode(std::string text, const sf::Font& font, uint8_t size)
	: m_Text(font,text,size)
{
	
}

void TextNode::setText(const std::string& text)
{
	m_Text.setString(text);
}


void TextNode::setColor(sf::Color color)
{
	m_Text.setFillColor(color);
}

const sf::Text& TextNode::getText() const
{
	return m_Text;
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Text, states);
}
