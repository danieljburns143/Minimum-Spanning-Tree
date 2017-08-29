// Daniel Burns
// Lab 10
// mst.cpp

#include <iostream>
#include <queue>
#include <map>
using namespace std;

/* class Vertex */
class Vertex {
public:
	Vertex(const int& c, const char& n, const char& p) // constructor
		: cost(c), name(n), prev(p) {}
	~Vertex() {} // destructor
	int getCost() const { return cost; } // function to return cost
	char getName() const { return name; } // function to get name
	char getPrev() const { return prev; } // function to get prev
private:
	int cost;
	char name;
	char prev;
};


/* function prototypes */
void inputDistances(map<char, map<char, int>>&, const int&, vector<vector<int>>&); // prototype to read in initial input
bool operator<(const Vertex&, const Vertex&); // prototype to assist with priority queue
void printFrontier(priority_queue<Vertex>); // prototype to print the frontier
void printDistances(const map<char, map<char, int>>&); // prototype to print out the distances
void printMarked(const map<char, char>&); // prototype to print out the marked vertices


/* main function */
int main() {
	int nVertices;
	int count{0};
	while (cin >> nVertices) {
		count++;
		int totalWeight = 0;
		map<char, map<char, int>> distances;
		vector<vector<int>> adjacencyMatrix;
		priority_queue<Vertex> frontier;
		map<char, char> marked;
		inputDistances(distances, nVertices, adjacencyMatrix);
		Vertex v(0, 'A', 'A');
		frontier.push(v);
		while (!frontier.empty()) {
			v = frontier.top();
			frontier.pop();
			if (marked.find(v.getName()) != marked.end()) {
				continue;
			}
			marked[v.getName()] = v.getPrev();
			totalWeight += v.getCost();
			for (auto vertex : distances[v.getName()]) {
				Vertex tempVertex(vertex.second, vertex.first, v.getName());
				frontier.push(tempVertex);
			}
		}
		cout << totalWeight << endl;
		printMarked(marked);
		if (count < 7) { cout << endl; }
	}
}


/* Functions */
// function to read in initial input
void inputDistances(map<char, map<char, int>>& distances, const int& nVertices, vector<vector<int>>& adjacencyMatrix) {
	for (char letter{65}; letter < 65 + nVertices; ++letter) {
		vector<int> tempRow;
		tempRow.resize(nVertices, 0);
		for (char neighbor{65}; neighbor < 65 + nVertices; ++neighbor) {
			int tempInput;
			cin >> tempInput;
			if (tempInput != -1) {
				distances[letter][neighbor] = tempInput;
				tempRow[tempInput - 1] = 1;
			}
		}
		adjacencyMatrix.push_back(tempRow);
	}
}

// overloaded operator< to assist with priority queue
bool operator<(const Vertex& x, const Vertex& y) {
	if (y.getCost() != x.getCost()) {
		return y.getCost() < x.getCost();
	}
	else {
		return y.getName() < x.getName();
	}
}

// function to print the frontier
void printFrontier(priority_queue<Vertex> frontier) {
	cout << "Frontier: {" << endl;
	while (!frontier.empty()) {
		Vertex tempVertex= frontier.top();
		frontier.pop();
		cout << "   (" << tempVertex.getCost() << ", " << tempVertex.getName()
			<< ", " << tempVertex.getPrev() << ")," << endl;
	}
	cout << "}" << endl;
}

// function to print out the distances
void printDistances(const map<char, map<char, int>>& distances) {
	for (auto vertex : distances) {
		cout << vertex.first;
		for (auto neighbor : vertex.second) {
			cout << " " << neighbor.first << "." << neighbor.second;
		}
		cout << endl;
	}
}

// function to print out the marked vertices
void printMarked(const map<char, char>& marked) {
	multimap<char, char> outputMap;
	for (auto vertex : marked) {
		if (vertex.first < vertex.second) {
			outputMap.insert({vertex.first, vertex.second});
		}
		else {
			outputMap.insert({vertex.second, vertex.first});
		}
	}
	for (auto vertex : outputMap) {
		if (vertex.first != 'A' || vertex.second != 'A') {
			cout << vertex.first << vertex.second << endl;
		}
	}
}

// function to print the adjacency matrix
void printMatrix(const vector<vector<int>>& adjacencyMatrix) {
	for (vector<int> tempRow : adjacencyMatrix) {
		for (int num : tempRow) {
			cout << num << " ";
		}
		cout << endl;
	}
}
