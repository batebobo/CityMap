#pragma once
#include "Graph.h"
#include "EGraph.h"
#include "LGraph.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
class Map
{
private:
	vector<string> rawMapData;
	LGraph<string> map;

	//Helpers
	string getNodeName(string);
	Node getNodeByName(string);
	bool nodeExists(string);
	bool hasNeighbours(string);
	void readFile();
	void processFile();
public:
	void test();
	vector<Edge> findClosedStreets();
	Map(void);
	~Map(void);
};

