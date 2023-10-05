#include "Player.h"
#include "PathfindingComponent.h"
#include <iostream>
#include "Game.h"
#include "City.h"

Player::Player(Game* myGameInstanceP)
{
	pathfinding = new PathfindingComponent();
    gameInstance = myGameInstanceP;

    FindPath();
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

    auto finalPath = pathfinding->FindNearestPath(cityMatrix, 2, matrixSize);

    //for (int i = 0; i < matrixSize; ++i)
    //{
    //    std::cout << finalPath[i] << " ";
    //}

    std::cout << std::endl;
}
