#pragma once
#include "Graph.h"
using namespace std;

class EGraph : public Graph
{
private:
	list<Edge> edges;
public:

	list<Edge> getEdges() const { return edges;}

	EGraph(list<Edge> _edges = list<Edge>()) : edges(_edges) { }

	bool areAdjacent(string first, string second) const { 
		for (auto i = edges.begin(); i != edges.end(); i++) {
			if (((*i).from == first && (*i).to == second) ||
				((*i).from == second && (*i).to == first)) return true;
		}
		return false;
	}

	void print() const { 
		for(auto i = edges.begin(); i != edges.end(); i++) { 
			cout << "(" << (*i).from << " -> " << (*i).to << ")" << endl;
		}
	}

	~EGraph()
	{
	}
};

