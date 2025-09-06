#include "PlaneDebugData.h"

#include "Game.h"

PlaneDebugData::PlaneDebugData(const Aircraft* aircraft, const sf::Font& font)
	: TextNode(font, 14)
	,m_Plane(aircraft)
{
	setColor(sf::Color::White);
}


void PlaneDebugData::updateCurrent(sf::Time dt)
{
	std::string debugString;
	debugString += "Position: " + std::to_string(m_Plane->getPosition().x) + ", " + std::to_string(m_Plane->getPosition().y) + "\n";
	debugString += "Velocity: " + std::to_string(m_Plane->getVelocity().x) + ", " + std::to_string(m_Plane->getVelocity().y) + "\n";
	debugString += "Heading: " + std::to_string(m_Plane->getRotation().asDegrees()) + "\n";
	debugString += "State: ";
	switch (m_Plane->getCurrentState())
	{
	case Aircraft::State::Spawning:
		debugString += "Spawning\n";
		break;
	case Aircraft::State::TakingOff:
		debugString += "Taking Off\n";
		break;
	case Aircraft::State::Flying:
		debugString += "Flying\n";
		break;
	case Aircraft::State::Landing:
		debugString += "Landing\n";
		break;
	default:
		debugString += "Unknown\n";
		break;
	}
	setText(debugString);
	//Set position above plane
	setPosition(m_Plane->getPosition() + sf::Vector2f(0, -50));

}
