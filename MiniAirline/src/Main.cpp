#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{

	try 
	{
		Game::getInstance()->run();
	}
    catch (std::exception& e)
    {
    printf("\nEXCEPTION: %s", e.what());
    }
} 