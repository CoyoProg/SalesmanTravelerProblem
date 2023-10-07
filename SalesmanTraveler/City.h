#pragma once
#include <map>
#include <iostream>

class City
{
public:
	City(const std::string& nameP) : cityName(nameP) {}

	std::string cityName;

	void connectCityTo(City* otherCityP, int distanceP);
	int distanceFrom(City* otherCityP);

private:
	std::map<City*, int> connectedCities;
};

