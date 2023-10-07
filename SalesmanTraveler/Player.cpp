#include "Player.h"
#include "PathfindingComponent.h"
#include <iostream>
#include "Game.h"
#include "City.h"

Player::Player(Game* myGameInstanceP)
{
	pathfinding = new PathfindingComponent();
    gameInstance = myGameInstanceP;
}

Player::~Player()
{
}

void Player::FindPath()
{
    std::vector<City*> cities = gameInstance->getAllCities();
    int matrixSize = cities.size();

    int** cityMatrix = new int* [matrixSize];
    for (int i = 0; i < matrixSize; ++i)
    {
        cityMatrix[i] = new int[matrixSize];

        for (int j = 0; j < matrixSize; ++j)
        {
            cityMatrix[i][j] = cities[i]->distanceFrom(cities[j]);
        }
    }

    int choice = 0;
    bool validInput = false;

    std::cout << "Choose from which city you want to start: (Between 0 & 4)\n";

    while (!validInput)
    {
        if (std::cin >> choice && choice >= 0 && choice <= 4)
        {
            validInput = true;
        }
        else
        {
            // Input is not an integer, clear error flags and ignore invalid input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer between 0 and 4." << std::endl;
        }
    }

    // Clear Console
    std::cout << "\x1B[2J\x1B[H"; 

    auto finalPath = pathfinding->FindNearestPath(cityMatrix, choice, matrixSize);
    std::cout << std::endl;
}
