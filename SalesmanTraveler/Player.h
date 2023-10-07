#pragma once

class PathfindingComponent;
class Game;

class Player
{
public:
	Player(Game* myGameInstanceP);
	~Player();

	void FindPath();

private:
	PathfindingComponent* pathfinding;
	Game* gameInstance;
};

