#include <SFML/Graphics.hpp>


class Waypoint
{
public:
	Waypoint(sf::Vector2f coords);
	Waypoint();
private:
	sf::Vector2f m_Coordinate;
};
