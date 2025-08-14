#include <string>
#include "Waypoint.h"


  
enum PlaneSize
{
   Small,
   Medium,
   Large,
};

enum PlaneType
{
	Passenger,
	Cargo,
	Military,
};

enum PlaneState
{
	InBound,
	OutBound,
	Waiting,
};

enum Company
{
	AirlineA,
	AirlineB,
	AirlineC,
	AirlineD,
};

class Plane
{
public:
	Plane(sf::Vector2f pos, sf::Vector2f vel);

	void setPosition(const sf::Vector2f& pos) { m_Position = pos; m_Shape.setPosition(pos); }
	void move(const sf::Vector2f& offset) { m_Position += offset; m_Shape.move(offset); }
	void setRadius(float radius) { m_Radius = radius; m_Shape.setRadius(radius); }
	void setFillColor(const sf::Color& color) { m_Color = color; m_Shape.setFillColor(color); }
	const sf::CircleShape& getShape() const {return m_Shape;}
	const sf::Vector2f& getVelocity() const { return m_Velocity;}

private:
	std::string m_Name;
	std::string m_Callsign;
	PlaneSize m_Size = PlaneSize::Small;
	Company m_Company = Company::AirlineA;
	PlaneType m_Type = PlaneType::Passenger;
	PlaneState m_State = PlaneState::InBound;
	Waypoint m_Waypoint;
	sf::Color m_Color;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Position;
	float m_Radius;
	sf::CircleShape m_Shape;
};   
    


