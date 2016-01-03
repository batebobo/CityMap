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
	Node getNodeByName(list<Node>, string);
	bool nodeExists(list<Node>, string);
	bool hasNeighbours(string);
	int getNumberOfNodes();
	void readFile();
	void processFile();
public:
	void test();
	vector<Edge> findClosedStreets();
	bool isReachable(string, string);
	bool allNodesReachable(string);
	bool hasCycle(string);
	int findShortestPath(string, string);
	Map(void);
	~Map(void);
};

