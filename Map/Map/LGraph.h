#pragma once
#include "Graph.h"
#include <string>
using namespace std;

class LGraph : public Graph
{
protected:
	list<Node> adjList;
public:
	LGraph(list<Node> _adjList = list<Node>()) : adjList(_adjList) { }

	bool areAdjacent(string first, string second) const { 
		for (auto i = adjList.begin(); i != adjList.end(); i++) {
			if ((*i).value == first) {
				for (auto j = (*i).neighbours.begin(); j != (*i).neighbours.end(); j++) {
					if ((*j).value == second) return true;
				}
			}
		}
		return false;
	}

	list<Node> getAdjList() const { return adjList; }

	size_t getNumberOfNodes() const { return adjList.size(); }

	void print() const { 
		for(auto i = adjList.begin(); i != adjList.end(); i++) {
			if((*i).neighbours.empty()) { cout << "Node " << (*i).value << " has no successors" << endl; }
			else {
				cout << "Node " << (*i).value << " is adjacent to " << endl;
				for(auto j = (*i).neighbours.begin(); j != (*i).neighbours.end(); j++) { 
					cout << "    " << (*j).value << endl;
				}
			}
		}
	}

	~LGraph()
	{
	}
};

