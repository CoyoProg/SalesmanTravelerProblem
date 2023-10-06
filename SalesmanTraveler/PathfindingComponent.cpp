#include "PathfindingComponent.h"
#include <vector>
#include <iostream>

PathfindingComponent::PathfindingComponent()
{
}

PathfindingComponent::~PathfindingComponent()
{
    delete[] finalPath;
    delete[] isVisited;
    delete[] cityMatrix;
}

int* PathfindingComponent::FindNearestPath(int** cityMatrixP, int startingPointP, int matrixSizeP)
{
    numberOfCity = matrixSizeP;
    cityMatrix = cityMatrixP;

    Initialize(startingPointP);

    printf("Minimum cost : %d\n", finalCost);
    printf("Path Taken : ");

    for (int i = 0; i <= numberOfCity; i++)
        printf("%d ", finalPath[i]);

    return finalPath;
}

void PathfindingComponent::Initialize(int startingPointP)
{
    finalCost = INT_MAX;

    /** Initialize nearest Path */
    finalPath = new int[numberOfCity];
    finalPath[0] = startingPointP;

    /** Initialize all the city to not visited */
    isVisited = new bool[numberOfCity];
    for (int i = 0; i < numberOfCity; ++i)
    {
        isVisited[i] = false;
    }

    /** Initialize currentBound & currentPath */
    int* currentPath = new int [numberOfCity + 1];              // +1 because we need to comeback to the first node
    int currentBound = 0;
    memset(currentPath, -1, sizeof(currentPath));

    /** Compute initial bound */
    for (int i = 0; i < numberOfCity; i++)
    {
        currentBound += (FirstMinimumEdgeCost(i) + SecondMinimumEdgeCost(i));
    }

    /** Rounding off the lower bound to an integer */
    currentBound = (currentBound & 1) ? currentBound / 2 + 1 : currentBound / 2;

    /** We start at vertex startingPointP so the first vertex in currentPath is startingPoint */
    isVisited[startingPointP] = true;
    currentPath[0] = startingPointP;

    /** Call to BranchAndBound for curr_weight equal to 0 and level 1 */
    BranchAndBound( currentBound, 0, 1, currentPath);

    delete[] currentPath;
}

void PathfindingComponent::BranchAndBound(int currentBoundP, int currentWeightP, int currentLevelP, int* currentPathP)
{
    int lastClosestNode = currentPathP[currentLevelP - 1];
    int startingNode = currentPathP[0];

    /** If CurrentLevel == numberOfCity then we covered all the nodes */
    if (currentLevelP == numberOfCity)
    {
        /** Check if there is an edge from the lastClosestNode back to the starting vertext */
        if (cityMatrix[lastClosestNode][startingNode] != 0)
        {
            /** currentCost has the total weight of the solution we got */
            int currentCost = currentWeightP + cityMatrix[lastClosestNode][startingNode];

            /** Update finalCost and finalPath if currentCost is better. */
            if (currentCost < finalCost)
            {
                CopyResultToFinal(currentPathP);
                finalCost = currentCost;
            }
        }
        return;
    }

    /** for any other level, iterate for all vertices */
    for (int i = 0; i < numberOfCity; i++)
    {
        /** Chech if there is an edge between the LastClosest node & the new vertex i, 
            and if the vertex i hasn't beend visited yet*/
        if (cityMatrix[lastClosestNode][i] != 0 && isVisited[i] == false)
        {
            int temp = currentBoundP;
            currentWeightP += cityMatrix[lastClosestNode][i];

            /** Calculate the minimum cost from lastClosestNode & vertex i */
            if (currentLevelP == 1)
                currentBoundP -= ((FirstMinimumEdgeCost(lastClosestNode) + FirstMinimumEdgeCost(i)) / 2);
            else
                currentBoundP -= ((SecondMinimumEdgeCost(lastClosestNode) + FirstMinimumEdgeCost(i)) / 2);

            /** If currentBound + currentWeight < finalCost, we need to explore the next level */
            if (currentBoundP + currentWeightP < finalCost)
            {
                currentPathP[currentLevelP] = i;
                isVisited[i] = true;

                /** call BranchAndBound for the next level */
                BranchAndBound(currentBoundP, currentWeightP, currentLevelP + 1, currentPathP);
            }

            lastClosestNode = currentPathP[currentLevelP - 1];

            /** Else we have to reset all changes to currentWeight and currentBound */
            currentWeightP -= cityMatrix[lastClosestNode][i];
            currentBoundP = temp;

            /** And reset isVisited to false, only the nodes in currentPath are set to true */
            memset(isVisited, false, sizeof(isVisited));
            for (int i = 0; i <= currentLevelP - 1; i++)
            {
                isVisited[currentPathP[i]] = true;
            }
        }
    }
}

int PathfindingComponent::FirstMinimumEdgeCost(int indexP)
{
    int mininmumCost = INT_MAX;
    
    /** We search for the closest edge with minimum cost */
    for (int i = 0; i < numberOfCity; i++)
    {
        if (cityMatrix[indexP][i] < mininmumCost && indexP != i)
            mininmumCost = cityMatrix[indexP][i];
    }

    return mininmumCost;
}

int PathfindingComponent::SecondMinimumEdgeCost(int indexP)
{
    int first = INT_MAX, second = INT_MAX;

    for (int i = 0; i < numberOfCity; i++)
    {
        if (indexP == i)
            continue;

        if (cityMatrix[indexP][i] <= first)
        {
            second = first;
            first = cityMatrix[indexP][i];
        }
        else if (cityMatrix[indexP][i] <= second && cityMatrix[indexP][i] != first)
        {
            second = cityMatrix[indexP][i];
        }
    }
    return second;
}

void PathfindingComponent::CopyResultToFinal(int* currentPathP)
{
    /** Copy the result into finalPath */
    for (int i = 0; i < numberOfCity; i++)
    {
        finalPath[i] = currentPathP[i];
        finalPath[numberOfCity] = currentPathP[0];
    }
}
