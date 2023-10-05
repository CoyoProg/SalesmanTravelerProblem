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
    /** Initialize nearest Path */
    finalPath = new int[numberOfCity];
    finalPath[0] = startingPointP;

    /** Initialize all the city to not visited */
    isVisited = new bool[numberOfCity];
    for (int i = 0; i < numberOfCity; ++i)
    {
        isVisited[i] = false;
    }

    /** Initialize Current Path */
    int* currentPath = new int [numberOfCity + 1];

    // Calculate initial lower bound for the root node
    // using the formula 1/2 * (sum of first min +
    // second min) for all edges.
    // Also initialize the curr_path and visited array
    int currentBound = 0;
    memset(currentPath, -1, sizeof(currentPath));

    // Compute initial bound
    for (int i = 0; i < numberOfCity; i++)
    {
        currentBound += (FirstMinimumEdgeCost(i) + SecondMinimumEdgeCost(i));
    }

    // Rounding off the lower bound to an integer
    currentBound = (currentBound & 1) ? currentBound / 2 + 1 : currentBound / 2;

    // We start at vertex 1 so the first vertex
    // in curr_path[] is 0
    isVisited[startingPointP] = true;
    currentPath[0] = startingPointP;

    // Call to TSPRec for curr_weight equal to
    // 0 and level 1
    BranchAndBound( currentBound, 0, 1, currentPath);
}

void PathfindingComponent::BranchAndBound(int currentBoundP, int currentWeightP, int currentLevelP, int* currentPathP)
{

    /** If CurrentLevel == numberOfCity then we covered all the nodes */
    if (currentLevelP == numberOfCity)
    {
        /** check if there is an edge from last vertex in path back to the first vertex */
        if (cityMatrix[currentPathP[currentLevelP - 1]][currentPathP[0]] != 0)
        {
            /** currentCost has the total weight of the solution we got */
            int currentCost = currentWeightP + cityMatrix[currentPathP[currentLevelP - 1]][currentPathP[0]];

            /** Update finalCost and finalPath if currentCost is better. */
            if (currentCost < finalCost)
            {
                CopyResultToFinal(currentPathP);
                finalCost = currentCost;
            }
        }
        return;
    }

    /** for any other level iterate for all vertices to build the search space tree recursively */
    for (int i = 0; i < numberOfCity; i++)
    {
        /** Chech if the node isn't == 0 and not visited yet */
        if (cityMatrix[currentPathP[currentLevelP - 1]][i] != 0 && isVisited[i] == false)
        {
            int temp = currentBoundP;
            currentWeightP += cityMatrix[currentPathP[currentLevelP - 1]][i];

            // different computation of curr_bound for level 2 from the other levels
            if (currentLevelP == 1)
                currentBoundP -= ((FirstMinimumEdgeCost(currentPathP[currentLevelP - 1]) + FirstMinimumEdgeCost(i)) / 2);
            else
                currentBoundP -= ((SecondMinimumEdgeCost(currentPathP[currentLevelP - 1]) + FirstMinimumEdgeCost(i)) / 2);

            // curr_bound + curr_weight is the actual lower bound
            // for the node that we have arrived on
            // If current lower bound < final_res, we need to explore
            // the node further
            if (currentBoundP + currentWeightP < finalCost)
            {
                currentPathP[currentLevelP] = i;
                isVisited[i] = true;

                // call TSPRec for the next level
                BranchAndBound(currentBoundP, currentWeightP, currentLevelP + 1, currentPathP);
            }

            // Else we have to prune the node by resetting
            // all changes to curr_weight and curr_bound
            currentWeightP -= cityMatrix[currentPathP[currentLevelP - 1]][i];
            currentBoundP = temp;

            // Also reset the visited array
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
