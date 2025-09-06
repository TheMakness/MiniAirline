#pragma once
#include <SFML\Graphics.hpp>
#include "Aircraft.h"
#include "World.h"


class Game;

enum class State
{
	Game,
	Pause,
	GameOver
};

static inline std::string toString(State state) {
	static const std::unordered_map<State, std::string> stateNames{
		{ State::Game, "Game" },
		{ State::Pause, "Pause" },
		{ State::GameOver, "GameOver" }
	};

	if (auto it = stateNames.find(state); it != stateNames.end())
		return it->second;

	return "Unknown";
}


class Game
{


public:
	
	void run();
	static Game* getInstance();

	void UpdateState(sf::Time deltaTime);
	void SwitchState(State newState);
	void OnEnterState(State enterState);

	const State getCurrentState() const;

	
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

private:
	Game();
	

private:
	void processInput();
	void update(sf::Time deltaTime);
	void render();

private:
	sf::RenderWindow m_Window;
	World m_World;
	Player m_Player;
	State m_CurrentState;
	FontHolder m_Fonts;
	
};
