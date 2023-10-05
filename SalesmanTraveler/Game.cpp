#include "Game.h"
#include "Player.h"
#include "City.h"

int ROAD_CROSS = 1;
int ROAD_DIAGONAL = 2;
int ROAD_NORMAL = 3;

Game::Game()
{
}

void Game::load()
{
	/** We Create 5 Cities */
	City* city1 = new City("City A");
	City* city2 = new City("City B");
	City* city3 = new City("City C");
	City* city4 = new City("City D");
	City* city5 = new City("City E");

	cities.push_back(city1);
	cities.push_back(city2);
	cities.push_back(city3);
	cities.push_back(city4);
	cities.push_back(city5);

	/** And then connect them with Roads */
	ConnectCities(city1, city2, ROAD_DIAGONAL);
	ConnectCities(city1, city3, ROAD_DIAGONAL);
	ConnectCities(city2, city3, ROAD_NORMAL);
	ConnectCities(city2, city4, ROAD_NORMAL);
	ConnectCities(city2, city5, ROAD_CROSS);
	ConnectCities(city3, city4, ROAD_CROSS);
	ConnectCities(city3, city5, ROAD_NORMAL);
	ConnectCities(city4, city5, ROAD_NORMAL);

	Player* player = new Player(this);
}

void Game::ConnectCities(City* cityA, City* cityB, int distanceP)
{
	cityA->connectCityTo(cityB, distanceP);
	cityB->connectCityTo(cityA, distanceP);
}
