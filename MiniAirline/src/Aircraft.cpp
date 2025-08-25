#include "Aircraft.h"


Aircraft::Aircraft(Type type, const TextureHolder& textures) :
	m_Type(type),
	m_Sprite(textures.get(Textures::ID::Airplane)),
	m_Arrow({ 0,0 }, { 0,0 })
{
	sf::FloatRect bounds = m_Sprite.getLocalBounds();
	m_Sprite.setOrigin(bounds.getCenter());
	m_Sprite.setScale({ 0.2f,0.2f });
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Arrow, states);
	target.draw(m_Sprite, states);
}

unsigned int Aircraft::getCategory() const
{
	return Category::Aircraft;
}

bool Aircraft::isSelected()
{
	return b_Selected;
}


void Aircraft::setDestination(sf::Vector2f destination)
{
	m_Destination = destination;
}

void Aircraft::updateArrow(sf::Vector2f targetPosition)
{
	if (!b_Selected || (m_CurrentMousePos - getPosition()).length() < 100.f)
		m_Arrow.SetArrowPositionAndRotation(getPosition(), getPosition() + (500.f * m_Velocity.normalized()));
	else
	{
		sf::Vector2f mouseDir = (m_CurrentMousePos - getPosition()).normalized();
		m_Arrow.SetArrowPositionAndRotation(getPosition(), getPosition() + (500.f * mouseDir));
	}
}

bool Aircraft::isAtMousePos(sf::Vector2f mousePos)
{
	return  (getWorldPosition() - mousePos).length() < 50;
}

void Aircraft::select()
{
	b_Selected = true;
	m_CurrentCategory = Category::Selected;
}

void Aircraft::unselect()
{
	b_Selected = false;
	m_CurrentCategory = Category::Aircraft;
}

void Aircraft::setMousePos(sf::Vector2f mousePos)
{
	m_CurrentMousePos = mousePos;
}

void Aircraft::updateCurrent(sf::Time deltaTime)
{
	Entity::updateCurrent(deltaTime);
	updateArrow(m_Velocity);
}





