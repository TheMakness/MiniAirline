#include "Player.h"
#include "CommandQueue.h"
#include "Aircraft.h"

#include <map>
#include <string>
#include <algorithm>


struct AircraftMover
{
	AircraftMover(float vx, float vy)
		: velocity(vx, vy)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

struct FindSelectedAircraft
{
	FindSelectedAircraft(Aircraft*& selectedAircraft, sf::Vector2f mousePos)
	:m_SelectedAircraft(selectedAircraft)
	, m_MousePos(mousePos)
	{

	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		if (aircraft.isSelected(m_MousePos))
		{
			m_SelectedAircraft = &aircraft;
		}
	}
	
	Aircraft*& m_SelectedAircraft;
	sf::Vector2f m_MousePos;
  
};

Player::Player()
{
	// Set initial key bindings
	m_KeyBinding[sf::Keyboard::Key::Left] = MoveLeft;
	m_KeyBinding[sf::Keyboard::Key::Right] = MoveRight;
	m_KeyBinding[sf::Keyboard::Key::Up] = MoveUp;
	m_KeyBinding[sf::Keyboard::Key::Down] = MoveDown;
	m_KeyBinding[sf::Keyboard::Key::Add] = ZoomIn;
	m_KeyBinding[sf::Keyboard::Key::Subtract] = ZoomOut;

	// Set initial action bindings
	initializeActions();

	// Assign all categories to player's aircraft
	for(auto& pair : m_ActionBinding)
		pair.second.category = Category::Aircraft;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands, sf::RenderWindow& window, sf::View& view )
{
	if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = m_KeyBinding.find(keyPressed->code);
		if (found->second == ZoomIn)
			view.zoom(.5);
		else if(found->second == ZoomOut)
			view.zoom(2);
		else if (found != m_KeyBinding.end() && !isRealtimeAction(found->second))
				commands.push(m_ActionBinding[found->second]);
		

	}

	if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouseButtonPressed->button == sf::Mouse::Button::Left)
		{
			Command c;
			c.category = Category::Aircraft;
			c.action = derivedAction<Aircraft>(FindSelectedAircraft(m_SelectedAircraft,
			window.mapPixelToCoords(sf::Mouse::getPosition(window))));
			commands.push(c);
		}
	}

	if (const auto* mouseButtonRelease = event.getIf<sf::Event::MouseButtonReleased>())
	{
		if ((mouseButtonRelease->button == sf::Mouse::Button::Left) && m_SelectedAircraft)
		{
			m_SelectedAircraft->SetVelocity(-m_SelectedAircraft->getVelocity());
			m_SelectedAircraft = nullptr;
		}
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	for(auto pair : m_KeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(m_ActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = m_KeyBinding.begin(); itr != m_KeyBinding.end(); )
	{
		if (itr->second == action)
			m_KeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	m_KeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for(auto pair : m_KeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}
	return static_cast<sf::Keyboard::Key>(-1);
}

void Player::initializeActions()
{
	const float playerSpeed = 200.f;
	m_ActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	m_ActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
	m_ActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	m_ActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveDown:
	case MoveUp:
		return true;
	default:
		return false;
	}
}