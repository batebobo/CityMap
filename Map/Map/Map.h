#pragma once
#include "Graph.h"
#include "EGraph.h"
#include "LGraph.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
class Map : public LGraph
{
private:
	//Helpers
	string getNodeName(string);
	bool nodeExistsIn(list<Node>, string);
	bool hasNeighbours(string);
	vector<string> extractFromFile(string);
public:
	Node getNodeByName(list<Node>, string);
	vector<Edge> findClosedStreets();
	bool isReachable(string, string, list<string> = list<string>());
	bool allNodesReachable(string);
	bool hasCycle(string);
	int findShortestPath(string, string, list<string> = list<string>());
	Map(string = "");
	~Map(void);
};

