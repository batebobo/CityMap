#include "Map.h"
#include <map>
#include <stack>

string Map::getNodeName(string input) {
	int pos = 0;
	string output = "";
	while(input[pos] != ' ') {
		output += input[pos];
		pos++;
	}
	return output;
}

vector<string> Map::extractFromFile(string fileName) { 
	fstream f;
	string line;
	vector<string> output;
	f.open(fileName, ios::in);
	while( getline(f, line)) { 
		output.push_back(line);
	}
	f.close();

	return output;
}

Map::Map(string fileName) {
	vector<string> fileContents = extractFromFile(fileName);
	list<Node> nodes;
	if(fileContents.empty()) return;
	for(auto i = fileContents.begin(); i != fileContents.end(); i++) { 
		string currentHeadNode = getNodeName((*i));
		Node node(currentHeadNode);
		for(size_t j = currentHeadNode.size() + 1; j < (*i).size(); j++) { 
			string currentNeighbour = getNodeName((*i).substr(j, (*i).size() - j));
			j += currentNeighbour.size();
			int currentDistance = atoi(((*i).substr(j, (*i).size() - j)).c_str());
			j += to_string(currentDistance).size() + 1;

			node.neighbours.push_back(Neighbour(currentNeighbour, currentDistance));
		}
		nodes.push_back(node);
	}

	adjList = nodes;
}

vector<Edge> Map::findClosedStreets() { 
	vector<Edge> output;
	for(auto i = adjList.begin(); i != adjList.end(); i++) { 
		for(auto j = (*i).neighbours.begin(); j != (*i).neighbours.end(); j++) { 
			if(!hasNeighbours((*j).value)) { 
				output.push_back(Edge((*i).value, (*j).value));
			}
		}
	}
	
	return output;
}

bool Map::nodeExistsIn(list<Node> nodes, string name) { 
	for(auto i = nodes.begin(); i != nodes.end(); i++) { 
		if((*i).value == name) return true;
	}
	return false;
}

Node Map::getNodeByName(list<Node> nodes, string name) {
	for(auto i = nodes.begin(); i != nodes.end(); i++) { 
		if((*i).value == name) return (*i);
	}
	Node a;
	return a;
}

bool Map::hasNeighbours(string name) {
	return nodeExistsIn(adjList, name) && getNodeByName(adjList, name).neighbours.size() > 0;
}

bool Map::isReachable(string from, string to, list<string> closedCrossroads ) { 
	typedef std::map<string,bool> boolMap;
	std::map<string,bool> closed;
	
	boolMap visited;
	for(auto i = adjList.begin(); i != adjList.end(); i++) { 
		visited[(*i).value] = false;
		closed[(*i).value] = false;
	}

	for(auto i = closedCrossroads.begin(); i != closedCrossroads.end(); i++) { 
		if (nodeExistsIn(adjList, (*i))) { 
			closed[(*i)] = true;
		}
	}

	list<string> queue;
	visited[from] = true;
	queue.push_back(from);

	while(!queue.empty()) { 
		string front = queue.front();
		queue.pop_front();

		if(areAdjacent(front, to)) return true;
		if (nodeExistsIn(adjList, front)) { 
			Node current = getNodeByName(adjList, front);
			for(auto i = current.neighbours.begin(); i != current.neighbours.end(); i++) { 
				if(nodeExistsIn(adjList, (*i).value) && !visited[(*i).value] && !closed[(*i).value]) { 
					visited[(*i).value] = true;
					queue.push_back((*i).value);
				}
			}
		}
	}

	return false;
}

bool Map::allNodesReachable(string from) { 
	for(auto i = adjList.begin(); i != adjList.end(); i++) { 
		if(!isReachable(from, (*i).value)) return false;
	}

	return true;
}

bool Map::hasCycle(string from) { 
	return isReachable(from, from);
}

int Map::findShortestPath(string from, string to, list<string> closedCrossroads) {
	if(!isReachable(from, to)) return -1;
	cout << "From " << from << " to " << to << endl;
	int infinity = 9999999;
	cout << endl;
	std::map<string, int> dist;
	std::map<string,string> prev;
	std::map<string, bool> visited;
	std::map<string, bool> closed;

	for(auto i = adjList.begin(); i != adjList.end(); i++) { 
		dist[(*i).value] = infinity;
		prev[(*i).value] = "";
		visited[(*i).value] = false;
		closed[(*i).value] = false;
	}

	for(auto i = closedCrossroads.begin(); i != closedCrossroads.end(); i++) { 
		if (nodeExistsIn(adjList, (*i))) { 
			closed[(*i)] = true;
		}
	}

	dist[from] = 0;
	
	while(!adjList.empty()) {
		Node u;
		int min = infinity;
		for(auto i = adjList.begin(); i != adjList.end(); i++) { 
			if(dist[(*i).value] < min && !visited[(*i).value] && !closed[(*i).value]) {
				min = dist[(*i).value];
				u = (*i);
			}
		}

		if(u.value == "") { 
			cout << "No path" << endl;
			return -1;
		} 

		visited[u.value] = true;
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

		for(auto i = u.neighbours.begin(); i != u.neighbours.end(); i++) { 
			if (nodeExistsIn(adjList, (*i).value) && !visited[(*i).value] && !closed[(*i).value]) {
				Node v = getNodeByName(adjList, (*i).value);
				int alt = dist[u.value] + (*i).weight;
				if (alt < dist[v.value]) { 
					dist[v.value] = alt;
					prev[v.value] = u.value;
				}
			} else if (!visited[(*i).value] && !closed[(*i).value]) {
				Node neighbourNode((*i).value);
				dist[neighbourNode.value] = dist[u.value] + (*i).weight;
				prev[neighbourNode.value] = u.value;
				adjList.push_back(neighbourNode);
			} 
		}
	}
	return -1;
}

Map::~Map(void)
{
}
