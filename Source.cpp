//CS 461 - Program 1
//Ashna Ali

//Outside sources used for reference:
//https://www.geeksforgeeks.org/best-first-search-informed-search/
//https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/?ref=gcse
//Textbook: Artificial Intelligence in the 21st Century Second Edition
//by Stephen Lucci and Danny Kopec (ISBN: 9781942270003)

#include <iostream>
#include <cmath>
#include <sstream>
#include <fstream>
#include <map>
#include <queue>
#include "City.h"
#include "Functions.h"

using namespace std;

//calculate distance
double CalculateEuclideanDistance(pair<double, double> coord1, pair<double, double> coord2) {
	return sqrt(pow((coord2.first - coord1.first), 2) + pow((coord2.second - coord1.second), 2));
}

//return distance
double getDistance(Cities city1, Cities city2) {

	return CalculateEuclideanDistance(city1.getCoordinates(), city2.getCoordinates());
	

}
//split function to use the with lines of adjacency file
vector<string> split(string& l, char del) {
	vector<string> tokens;
	string token;
	istringstream tokenStream(l);
	while (getline(tokenStream, token, del)) {
		if (token.size() > 0) {
			tokens.push_back(token);
		}
	}
	return tokens;
}

//best first search algorithm, takes start location, end location, and the data structure
//data structure is supposed to simulate an undirected graph
void best_first_search(string start, string end, map<string, Cities> graph) {
	//nodes to add to priority queue (min heap)
	struct node {
		string name;
		double cost;

		node(string name, double cost)
			: name(name), cost(cost) {

		}
	};
	// this is an structure which implements the
	// operator overloading, to compare the cost of each node added to the priority queue 
	// (min heap)
	struct CompareCost {
		bool operator()(node const& n1, node const& n2)
		{
			// return "true" if "n1" is ordered
			// before "n2", for example:
			return n1.cost > n2.cost;
		}
	};
	//priority queue (using MIN HEAP)
	priority_queue<node, vector<node>, CompareCost> pq;
	//data structure to loop through adjacencies
	vector<pair<string, double>> neighbors;

	//total distance traveled
	double total_cost = 0;
	//start node has 0 cost
	pq.push(node(start, 0));
	//set the start node to visited
	graph[start].setVisited();
	
	//looping through priority queue until empty
	while (!pq.empty()) {
		//save top node (lowest cost)
		node p = pq.top();
		//display node with lowest cost
		cout << p.name << "-> " << "Dist: " << p.cost << endl;
		//increment total distance
		total_cost += p.cost;
		//pop off top node of queue (lowest distance city)
		pq.pop();
		//check if reached end node
		if (p.name == end) {
			break;
		}

		//find the neighbors of node p that are not visited, put them in queue
		neighbors = graph[p.name].getAdjancies();
		for (int i = 0; i < neighbors.size(); i++) {
			if (!graph[neighbors.at(i).first].hasVisited()) {
				graph[neighbors.at(i).first].setVisited();
				pq.push(node(neighbors.at(i).first, neighbors.at(i).second));
			}
		}
	}
	cout << endl;
	//print out the total distance traveled
	cout << "Total Distance Traveled: " << total_cost << endl;

}
//function for reading in coordinates
void readInCoordinates(string file,  map<string, Cities>& data) {
	ifstream filestream;
	//filestream variables
	double coord1 = 0.0;
	double coord2 = 0.0;
	string cityName;
	//open file and check if file is valid and present
	filestream.open(file);
	while (filestream.good()) {
		filestream >> cityName >> coord1 >> coord2;
		//make sure the line in the file is not empty
		if (cityName.size() > 0) {
			//initialize empty object to put into data structure
			Cities city;
			//set coordinates in object
			city.setCoordinates(coord1, coord2);
			//push object into datastructure with cityName as the key
			data.insert(make_pair(cityName, city));

		}

	}
	//close file
	filestream.close();



}
//function for reading in adjacencies
void readInAdjacencies(string file, map<string, Cities>& data) {
	ifstream filestream;
	string line;
	vector<string> cities;
	double d = 0.0;
	map<string, Cities>::iterator it;

	filestream.open(file);
	while (filestream.good()) {
		getline(filestream, line);
		if (line.size() > 0) {
			cities = split(line, ' ');
			if (cities.size() > 0) {
				for (it = data.begin(); it != data.end(); it++) {
					if (cities.at(0) == it->first) {
						for (int i = 1; i < cities.size(); i++) {
							d = getDistance(data[cities.at(0)], data[cities.at(i)]);
							it->second.setAdjancies(cities.at(i), d);
						}

					}
				}

			}


		}
	}
	filestream.close();


}
//function for adding symmetric adjacencies
void addingSymmetricAdjacencies(map<string, Cities>& data) {
	map<string, Cities>::iterator it1;
	map<string, Cities>::iterator it2;
	for (it1 = data.begin(); it1 != data.end(); it1++) {
		string city1 = it1->first;
		//cout << "Checking city1: " << city1 << endl;
		for (it2 = data.begin(); it2 != data.end(); it2++) {
			string city2 = it2->first;
			//cout << "city2: " << city2 << endl;
			if (city2 != city1) {
				//cout << "city2 adj: " << it2->second.getAdjancies().size() << endl;
				for (int i = 0; i < it2->second.getAdjancies().size(); i++) {
					if (city1 == it2->second.getAdjancies().at(i).first) {
						it1->second.setAdjancies(city2, it2->second.getAdjancies().at(i).second);
					}
				}
			}
		}


	}

}




int main() {
	//filesteam variable
	ifstream fileIn;
	string cityName1;
	string cityName2;
	char user_input_var = ' ';


	//data structure to keep information from files (using map) and iterator
	map<string, Cities> data;
	map<string, Cities>::iterator it;


	//read in coordinates file
	readInCoordinates("coordinates.txt", data);
	

	//Read in adjacency file
	readInAdjacencies("Adjacencies.txt", data);
	
	//book example for testing
	/*
	data["BC"].setAdjancies("BQE", 3.7);
	data["BC"].setAdjancies("WB", 17.6);
	data["BQE"].setAdjancies("BB", 2.2);
	data["BQE"].setAdjancies("MD", 14.6);
	data["WB"].setAdjancies("MD", 6.0);
	data["WB"].setAdjancies("PP", 2.0);
	data["WB"].setAdjancies("MD1", 4.9);
	data["MD"].setAdjancies("YS", 2.2);
	data["MD1"].setAdjancies("YS", 1.5);
	data["MD1"].setAdjancies("MD2", 2.0);
	data["MD2"].setAdjancies("PP", 5.0);
	data["BB"].setAdjancies("MD", 8.5);
	*/

	//adding symmetric adjacencies
	addingSymmetricAdjacencies(data);


	//print out map for testing
	/*
	cout << "***************DATA MAP******************" << endl;
	//check if data is read in correctly
	for (it = data.begin(); it != data.end(); it++) {
		cout << it->first << " : ";
		it->second.printCoordinates();
		it->second.printAdjancies();
	}
	*/

	while (user_input_var != 'n'){
		cout << "====== BEST FIRST SEARCH GPS ======" << endl;
		cout << "Enter the name of your start location..." << endl;
		cin >> cityName1;
		cout << "Enter the name of your end location..." << endl;
		cin >> cityName2;
		if (data.count(cityName1) == 0 || data.count(cityName2) == 0) {
			cout << "Sorry, one or more of the cities you entered does not exist in our database. Please try again..." << endl;
			cout << endl;
		}
		else {
			cout << "====== BEST ROUTE ======" << endl;
			best_first_search(cityName1, cityName2, data);

		}
		cout << "Would you like to enter another route?" << endl;
		cin >> user_input_var;
		
	}


	return 0;

}