#include <iostream>
#include <string>
#include <vector>
#include "City.h"
using namespace std;




void Cities::setVisited(bool v) {
	this->visited = v;
}

bool Cities::hasVisited() {
	return this->visited;
}
void Cities::setAdjancies(string adj, double adjdist) {
	bool found = false;
	//check for duplicate adjacencies 
	for (int i = 0; i < this->adjancies.size(); i++) {
		if (adj == this->adjancies.at(i).first) {
			found = true;
			//cout << "***skip " << adj << endl;
			break;
		}

	}
	if (!found) {
		pair<string, double> pair;
		pair.first = adj;
		pair.second = adjdist;
		this->adjancies.push_back(pair);
		//cout << "***add " << adj << endl;

	}

}
vector<pair<string, double>>Cities::getAdjancies() {
	return this->adjancies;
}
void Cities::setCoordinates(double coord1, double coord2) {
	this->coordinates.first = coord1;
	this->coordinates.second = coord2;

}
pair<double, double>Cities::getCoordinates() {
	return this->coordinates;

}
void Cities::printCoordinates() {
	cout << this->coordinates.first << " " << this->coordinates.second << endl;
}

void Cities::printAdjancies() {
	if (this->adjancies.size() > 0) {
		cout << "Adjancies:" << endl;
		for (int i = 0; i < this->adjancies.size(); i++) {
			cout << "   " << this->adjancies.at(i).first << ", " << "Distance: " << this->adjancies.at(i).second << endl;
		}

	}

}



