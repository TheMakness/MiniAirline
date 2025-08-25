#pragma once
#include "World.h"
#include "Aircraft.h"

class World;

class Player
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		ZoomIn,
		ZoomOut,
		ActionCount,
	};


public:
	Player();

	void handleEvent(const sf::Event& event, CommandQueue& commands, World& world);
	void handleRealtimeInput(CommandQueue& commands, World& world);

	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Action action) const;


private:
	void initializeActions();
	static bool	isRealtimeAction(Action action);


private:
	std::map<sf::Keyboard::Key, Action>		m_KeyBinding;
	std::map<Action, Command>				m_ActionBinding;
	Aircraft*								m_SelectedAircraft;
	sf::Vector2f m_PreviousMousePosition;
};
