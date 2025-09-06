#pragma once
#include "SceneNode.h"
class TextNode : public SceneNode
{
    public:
	explicit TextNode(const sf::Font& font, uint8_t size);
    explicit TextNode(std::string text,const sf::Font& font, uint8_t size);
    void setText(const std::string& text);
    void setColor(sf::Color color);
   
    const sf::Text& getText() const;

    private:
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	sf::Text m_Text;

};



