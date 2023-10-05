#pragma once
#include <vector>

class City;
class Roads;

class Game
{
public:
	// This singleton will ensure the existence and unicity of the game instance
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game();
	Game(const Game&) = delete;
	Game& operator = (const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator = (Game&&) = delete;

	void load();

	std::vector<City*>& getAllCities() { return cities; }
	std::vector<Roads*>& getAllRoads() { return roads; }

private:
	void ConnectCities(City* cityA, City* cityB, int dinstanceP);
	std::vector<City*> cities;
	std::vector<Roads*> roads;
};

