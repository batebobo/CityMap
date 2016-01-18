#include <iostream>
#include <fstream>
#include "Graph.h"
#include "LGraph.h"
#include "Map.h"
using namespace std;

void test() { 
	cout << "Enter the realm of testing" << endl;
	cin.get();
}

void enableInteractiveMode(Map a, string crossroad) {
	list<string> closedCrossroads;
	cout << "YEY" << endl;
	string currentCrossroad = crossroad;
	while (true) {
		string command;
		cin >> command;
		
		if (command == "location") { 
			cout << currentCrossroad << endl;
			continue;
		}
		if (command == "change") { 
			string newLocation;
			cin >> newLocation;
			// Checks
			currentCrossroad = newLocation;
			continue;
		}
		if (command == "neighbours") { 
			Node currentNode;
			currentNode = a.getNodeByName(a.getAdjList(), currentCrossroad);

			for(auto it = currentNode.neighbours.begin(); it != currentNode.neighbours.end(); it++) { 
				cout << (*it).value << endl;
			}
			continue;
		}
		if (command == "move") { 
			string to;
			cin >> to;

			if (a.findShortestPath(currentCrossroad, to, closedCrossroads) != -1) { 
				currentCrossroad = to;
			}
			continue;
		}
		if (command == "close") { 
			string what;
			cin >> what;

			// Check if node
			closedCrossroads.push_back(what);
			continue;
		}

		if (command == "open") { 
			string what;
			cin >> what;

			closedCrossroads.remove(what);
			continue;
		}
		if (command == "closed") { 
			for(auto it = closedCrossroads.begin(); it != closedCrossroads.end(); it++) { 
				cout << (*it) << endl;
			}
			continue;
		}
		if (command == "exit") { 
			return;
		}

		cout << "Command not recognized. Please try again" << endl;
	}
}

int main(int argc, char** argv) {
	cout << "Enter with " << argc  << endl;
	if (argc == 1) {
		test();
		return 0;
	}
	cout << argv[1] << endl;

	if(argc == 4 && !strcmp(argv[1], "-i")) {
		cout << "Interactive" << endl;
		Map a(argv[2]);
		string current = argv[3];

		auto adjList = a.getAdjList();
		if((a.getNodeByName(a.getAdjList(), current)).value == "") { 
			cout << "No such crossroad, terminating!" << endl;
			return 1;
		} else { 
			enableInteractiveMode(a, current);
		}
	}

	cout << "Exit" << endl;

	return 0;
}


