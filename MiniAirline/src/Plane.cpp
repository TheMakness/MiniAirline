#include "Plane.h"

Plane::Plane(sf::Vector2f pos, sf::Vector2f vel)
	: m_Position(pos),
	m_Velocity(vel),
	m_Radius(40.f),
	m_Color(sf::Color::Blue),
	m_Company(Company::AirlineA),
	m_Size(PlaneSize::Small),
	m_State(PlaneState::InBound),
	m_Type(PlaneType::Passenger)
{
	m_Shape.setRadius(m_Radius);
	m_Shape.setPosition(m_Position);
	m_Shape.setFillColor(m_Color);
}
