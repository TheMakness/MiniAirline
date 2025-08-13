#include <SFML\Graphics.hpp>


class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void onKeyPressed(const sf::Event::KeyPressed& keyPressed);
	void onKeyReleased(const sf::Event::KeyReleased& keyReleased);

private:
	sf::RenderWindow m_Window;
	sf::CircleShape m_Player;
	float m_PlayerSpeed;

	bool m_upKeyPressed, m_downKeyPressed, m_leftKeyPressed, m_rightKeyPressed;
};
