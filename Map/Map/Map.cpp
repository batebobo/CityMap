#include "Map.h"

void Map::test() { 
	processFile();
	map.print();
	cout << map.areAdjacent("TimesSquare", "8th46th");
	cout << map.areAdjacent("TimesSquare", "8th45th");


	/// Path test
	/*list<string> path;
	path.push_back("TimesSquare");
	path.push_back("8th46th");
	path.push_back("8th45th");
	map.isPath(path);*/

	///Closed streets test
	//vector<Edge> closedStreets = findClosedStreets();
	//for(auto i = closedStreets.begin(); i != closedStreets.end(); i++) { 
	//	cout << "closed street : " << (*i).from << " to: " << (*i).to << endl;
	//}
}

string Map::getNodeName(string input) { 
	int pos = 0;
	string output = "";
	while(input[pos] != ' ') {
		output += input[pos];
		pos++;
	}
	return output;
}

void Map::readFile() { 
	fstream f;
	string line;
	f.open("map.txt", ios::in);
	while( getline(f, line)) { 
		rawMapData.push_back(line);
	}
	f.close();
}

void Map::processFile() { 
	readFile();
	list<Node> nodes;
	if(rawMapData.empty()) return;
	for(auto i = rawMapData.begin(); i != rawMapData.end(); i++) { 
		string currentHeadNode = getNodeName((*i));
		Node node(currentHeadNode);
		for(int j = currentHeadNode.size() + 1; j < (*i).size(); j++) { 
			string currentNeighbour = getNodeName((*i).substr(j, (*i).size() - j));
			j += currentNeighbour.size();
			int currentDistance = atoi(((*i).substr(j, (*i).size() - j)).c_str());
			j += to_string(currentDistance).size() + 1;

			Neighbour neighbour(currentNeighbour, currentDistance);
			node.neighbours.push_back(neighbour);
		}
		nodes.push_back(node);
	}
	map = LGraph<string>(nodes);
}

vector<Edge> Map::findClosedStreets() { 
	vector<Edge> output;
	list<Node> nodes = map.getAdjList();
	for(auto i = nodes.begin(); i != nodes.end(); i++) { 
		string from = (*i).value;
		for(auto j = (*i).neighbours.begin(); j != (*i).neighbours.end(); j++) { 
			if(!hasNeighbours((*j).value)) { 
				Edge current(from, (*j).value);
				output.push_back(current);
			}
		}
	}
	
	return output;
}

bool Map::nodeExists(string name) { 
	list<Node> nodes = map.getAdjList();
	for(auto i = nodes.begin(); i != nodes.end(); i++) { 
		if((*i).value == name) return true;
	}
	return false;
}

Node Map::getNodeByName(string name) {
	list<Node> nodes = map.getAdjList();
	for(auto i = nodes.begin(); i != nodes.end(); i++) { 
		if((*i).value == name) return (*i);
	}
}

bool Map::hasNeighbours(string name) { 
	return nodeExists(name) && getNodeByName(name).neighbours.size() > 0;
}

Map::Map(void)
{
}


Map::~Map(void)
{
}
