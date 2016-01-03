#include "Map.h"
#include <map>
#include <stack>

void Map::test() { 
	processFile();
	map.print();
	//cout << map.areAdjacent("TimesSquare", "8th46th");
	//cout << map.areAdjacent("TimesSquare", "8th45th");

	//cout << isReachable("TimesSquare", "8th45th");
	//cout << isReachable("AveOfTheAmericas", "TimesSquare");
	//cout << isReachable("TimesSquare", "AveOfTheAmericas");

	//cout << allNodesReachable("TimesSquare");

	cout << hasCycle("TimesSquare");

	auto nodes = map.getAdjList();
	auto first = nodes.front();
	nodes.pop_front();
	nodes.pop_front();
	nodes.pop_front();
	nodes.pop_front();
	auto second = nodes.front();
	cout << findShortestPath("TimesSquare", "7th47th");


	/// Path test
	/*list<string> path;
	path.push_back("TimesSquare");
	path.push_back("8th46th");
	path.push_back("8th45th");
	map.isPath(path);*/

	//Closed streets test
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

			node.neighbours.push_back(Neighbour(currentNeighbour, currentDistance));
		}
		nodes.push_back(node);
	}
	map = LGraph<string>(nodes);
}

vector<Edge> Map::findClosedStreets() { 
	vector<Edge> output;
	list<Node> nodes = map.getAdjList();
	for(auto i = nodes.begin(); i != nodes.end(); i++) { 
		for(auto j = (*i).neighbours.begin(); j != (*i).neighbours.end(); j++) { 
			if(!hasNeighbours((*j).value)) { 
				output.push_back(Edge((*i).value, (*j).value));
			}
		}
	}
	
	return output;
}

bool Map::nodeExists(list<Node> nodes, string name) { 
	for(auto i = nodes.begin(); i != nodes.end(); i++) { 
		if((*i).value == name) return true;
	}
	return false;
}

Node Map::getNodeByName(list<Node> nodes, string name) {
	for(auto i = nodes.begin(); i != nodes.end(); i++) { 
		if((*i).value == name) return (*i);
	}
}

bool Map::hasNeighbours(string name) {
	auto nodes = map.getAdjList();
	return nodeExists(nodes, name) && getNodeByName(nodes, name).neighbours.size() > 0;
}

int Map::getNumberOfNodes() { 
	return map.getAdjList().size();
}

bool Map::isReachable(string from, string to) { 
	typedef std::map<string,bool> boolMap;

	list<Node> nodes = map.getAdjList();
	boolMap visited;
	for(auto i = nodes.begin(); i != nodes.end(); i++) { 
		visited[(*i).value] = false;
	}

	list<string> queue;
	visited[from] = true;
	queue.push_back(from);

	while(!queue.empty()) { 
		string front = queue.front();
		queue.pop_front();

		if(map.areAdjacent(front, to)) return true;
		if (nodeExists(nodes, front)) { 
			Node current = getNodeByName(nodes, front);
			for(auto i = current.neighbours.begin(); i != current.neighbours.end(); i++) { 
				if(nodeExists(nodes, (*i).value) && !visited[(*i).value]) { 
					visited[(*i).value] = true;
					queue.push_back((*i).value);
				}
			}
		}
	}

	return false;
}

bool Map::allNodesReachable(string from) { 
	list<Node> nodes = map.getAdjList();
	for(auto i = nodes.begin(); i != nodes.end(); i++) { 
		if(!isReachable(from, (*i).value)) return false;
	}

	return true;
}

bool Map::hasCycle(string from) { 
	return isReachable(from, from);
}

int Map::findShortestPath(string from, string to) {
	cout << "From " << from << " to " << to << endl;
	int infinity = 9999999;
	cout << endl;
	list<Node> Q;
	list<Node> nodes = map.getAdjList();
	std::map<string, int> dist;
	std::map<string,string> prev;

	for(auto i = nodes.begin(); i != nodes.end(); i++) { 
		dist[(*i).value] = infinity;
		prev[(*i).value] = "";
		Q.push_back((*i));
	}

	dist[from] = 0;
	
	while(!Q.empty()) {
		Node u;
		int min = infinity;
		for(auto i = Q.begin(); i != Q.end(); i++) { 
			if(dist[(*i).value] < min) { 
				min = dist[(*i).value];
				u = (*i);
			}
		}
		if(u.value == to) {
			int toReturn = dist[u.value];
			stack<string> output;
			while(prev[u.value] != "") { 
				output.push(u.value);
				u = prev[u.value];
			}
			while(!output.empty()) { 
				cout << "From " << output.top() << endl;
				output.pop();
			}
			return toReturn;
		}
		Q.remove(u);

		for(auto i = u.neighbours.begin(); i != u.neighbours.end(); i++) { 
			if (nodeExists(Q, (*i).value)) {
				Node v = getNodeByName(Q, (*i).value);
				int alt = dist[u.value] + (*i).weight;
				if (alt < dist[v.value]) { 
					dist[v.value] = alt;
					prev[v.value] = u.value;
				}
			} else {
				Node neighbourNode((*i).value);
				dist[neighbourNode.value] = dist[u.value] + (*i).weight;
				prev[neighbourNode.value] = u.value;
				Q.push_back(neighbourNode);
			} 
		}
	}
	return 0;
}



Map::Map(void)
{
}


Map::~Map(void)
{
}
