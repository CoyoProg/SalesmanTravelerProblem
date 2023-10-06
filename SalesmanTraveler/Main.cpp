// SalesmanTraveler.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Game.h"

int main()
{
	bool playing = true;

	Game::instance().Load();

	while (playing)
	{
		Game::instance().Play();

		// Pause the console on Windows
		system("pause"); 

		// Clear Console
		std::cout << "\x1B[2J\x1B[H";
	}
}

