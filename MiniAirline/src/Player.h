#pragma once
#include <SFML/Window/WindowBase.hpp>
#include "CommandQueue.h"
#include <map>
#include "Aircraft.h"
#include "World.h"

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

	void handleEvent(const sf::Event& event, CommandQueue& commands, sf::RenderWindow& window, sf::View& view);
	void handleRealtimeInput(CommandQueue& commands);

	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Action action) const;


private:
	void initializeActions();
	static bool	isRealtimeAction(Action action);


private:
	std::map<sf::Keyboard::Key, Action>		m_KeyBinding;
	std::map<Action, Command>				m_ActionBinding;
	Aircraft*								m_SelectedAircraft;
};
