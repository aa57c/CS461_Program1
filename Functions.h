#pragma once
#include <iostream>
#include <map>
#include <queue>
#include "City.h"

using namespace std;
double CalculateEuclideanDistance(pair<double, double> coord1, pair<double, double> coord2);
double getDistance(Cities city1, Cities city2);
vector<string> split(string& l, char del);
void best_first_search(string start, string end, map<string, Cities> graph);
void readInCoordinates(string file, map<string, Cities>& data);
void readInAdjacencies(string file, map<string, Cities>& data);
void addingSymmetricAdjacencies(map<string, Cities>& data);


