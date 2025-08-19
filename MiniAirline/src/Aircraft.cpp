#include "Aircraft.h"



Aircraft::Aircraft(Type type, const TextureHolder& textures) :
	m_Type(type), 
	m_Sprite(textures.get(Textures::ID::Airplane))
{
	sf::FloatRect bounds = m_Sprite.getLocalBounds();
	m_Sprite.setOrigin(bounds.getCenter());
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite, states);
}
