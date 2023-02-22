#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
class Cities {
private:
	vector<pair<string, double>> adjancies;
	pair<double, double> coordinates;
	bool visited = false;

public:
	void setAdjancies(string adj, double adjdist);
	vector<pair<string, double>> getAdjancies();
	void setCoordinates(double coord1, double coord2);
	pair<double, double> getCoordinates();
	void printCoordinates();
	void printAdjancies();
	bool hasVisited();
	void setVisited(bool v = true);

};
