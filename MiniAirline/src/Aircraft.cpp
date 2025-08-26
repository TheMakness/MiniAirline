#include "Aircraft.h"
#include "Utils.h"


Aircraft::Aircraft(Type type, const TextureHolder& textures) :
	m_Type(type),
	m_Sprite(textures.get(Textures::ID::Airplane)),
	m_Arrow({ 0,0 }, { 0,0 })
{
	sf::FloatRect bounds = m_Sprite.getLocalBounds();
	m_Sprite.setOrigin(bounds.getCenter());
	m_Sprite.setScale({ 0.35f,0.35f });

	m_Circle.setRadius(100.f);
	m_Circle.setOutlineThickness(10.f);
	m_Circle.setOutlineColor(sf::Color::Blue);
	m_Circle.setFillColor({ 0,0,0,0 });
	m_Circle.setOrigin(m_Circle.getGeometricCenter());
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Arrow, states);
	target.draw(m_Circle, states);
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


void Aircraft::setDesiredVelocity(sf::Vector2f destination)
{
	m_DesiredVelocity = destination;
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
	return  (getWorldPosition() - mousePos).length() < 100;
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
	AlignToVelocity();
	lerpVelocity(deltaTime);
}

void Aircraft::lerpVelocity(sf::Time deltaTime)
{
	static float alpha = 0;
	static sf::Vector2f startVelocity = m_Velocity;

	if (m_Velocity.normalized().dot(m_DesiredVelocity.normalized()) < .999f)
	{
		m_Velocity = Utils::lerp(m_Velocity,m_DesiredVelocity,alpha += m_RotationSpeed * deltaTime.asSeconds());
	}
	else
	{
		alpha = 0;
		m_Velocity = m_DesiredVelocity;
	}
}







