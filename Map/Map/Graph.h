#pragma once
#include <list>
#include <iostream>
#include<string>

using namespace std;

struct Neighbour { 
	string value;
	int weight;

	Neighbour(string _value = "", int _weight = 0): value(_value), weight(_weight) { }
};

struct Node { 
	string value;
	list<Neighbour> neighbours;
	bool isClosed;

	friend bool operator< (const Node& first, const Node& second) { 
		return first.value.compare(second.value) == 1;
	}

	friend bool operator== (const Node& first, const Node& second) { 
		return first.value == second.value;
	}

	Node(string _value = "", list<Neighbour> _neighbours = list<Neighbour>(), bool _isClosed = false) : value(_value), neighbours(_neighbours), isClosed(_isClosed) { }
};

struct Edge { 
	string from;
	string to;

	Edge(string _from = "", string _to = "") : from(_from), to(_to) { }
};

template <typename T>
class Graph
{
private:
	void printPath(list<string> path) const { 
		for(auto i = path.begin(); i != path.end(); i++) { 
			cout << " -> " << (*i);
		}
	} 
public:
	virtual bool areAdjacent(string, string) const = 0;

	bool isPath(list<string> path) const { 
		for (auto i = path.begin(); i != prev(path.end(), 1); i++) {
			if(!areAdjacent((*i), (*next(i,1)))) { 
				printPath(path);
				cout << " is not a valid path" << endl;
				return false;
			} 
		}
		printPath(path);
		cout << " is a valid path" << endl;
		return true;
	}
	virtual void print() const = 0;

	virtual ~Graph() { }
};

