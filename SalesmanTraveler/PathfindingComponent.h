#pragma once
#include<array>

class PathfindingComponent
{
public:
	PathfindingComponent();
	~PathfindingComponent();

	int* FindNearestPath(int** cityMatrixP, int startingPointP, int matrixSizeP);

private:
	void Initialize(int startingPointP);
	void BranchAndBound(int currentBoundP, int currentWeightP, int currentLevelP, int* currentPathP);
	int FirstMinimumEdgeCost(int indexP);
	int SecondMinimumEdgeCost(int indexP);
	void CopyResultToFinal(int* currentPathP);

	int numberOfCity{ 0 };
	int** cityMatrix;
	int finalCost { INT_MAX };
	int* finalPath;
	bool* isVisited;
};

