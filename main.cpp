#include"stdafx.h"
#include "Game.h"
#include <time.h>
#include <SFML/Graphics.hpp>

int main()
{
	srand(static_cast<unsigned>(time(0)));
	Game game;
	while (game.getWindow().isOpen())
	{
		
		game.update();
		
		game.render();

	}


	return 0;
}

 