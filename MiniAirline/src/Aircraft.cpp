#include "Aircraft.h"


Aircraft::Aircraft(Type type, const TextureHolder& textures) :
	m_Type(type), 
	m_Sprite(textures.get(Textures::ID::Airplane))
{
	sf::FloatRect bounds = m_Sprite.getLocalBounds();
	m_Sprite.setOrigin(bounds.getCenter());
	m_Sprite.setScale({ 0.2f,0.2f });
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite, states);
}

unsigned int Aircraft::getCategory() const
{
	return Category::Aircraft;
}

bool Aircraft::isSelected(sf::Vector2f mousePos)
{
	//return m_Sprite.getGlobalBounds().contains(mousePos);
	return  (getWorldPosition() - mousePos ).length() < 50;
	//return true;
}



