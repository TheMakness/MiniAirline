#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{

	try 
	{
		Game game;
		game.run();
	}
    catch (std::exception& e)
    {
    printf("\nEXCEPTION: %s", e.what());
    }
} 