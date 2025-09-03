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


 static Game* s_Instance;

class Game
{


public:
	
	void run();
	static Game* getInstance();

	Game(Game& other) = delete;
	void operator=(const Game&) = delete;

	void UpdateState(sf::Time deltaTime);
	void SwitchState(State newState);
	void OnEnterState(State enterState);

	const State& getCurrentState() const;

public:


protected:
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
	
};
