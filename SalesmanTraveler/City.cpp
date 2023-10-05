#include "City.h"

void City::connectCityTo(City* otherCityP, int distanceP)
{
    connectedCities[otherCityP] = distanceP;
}

int City::distanceFrom(City* otherCityP)
{
    auto it = connectedCities.find(otherCityP);

    if (it != connectedCities.end())
    {
        return connectedCities[otherCityP];
    }
    else
        return 0;
}
