#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Grafos.h"
#include "Node.h"

using namespace std;

class Street {
private:
	int id;
	string name;
	vector<Vertex<Node>*> vertexs;
	bool twoWays;
	string location;

public:
	Street();
	~Street();
	Street(int id, string name, vector<Vertex<Node>*> vertexs, int way);
	int getID();
	string getName();
	vector<Vertex<Node>*> getVertexs();
	bool isTwoWays();
	string getLocation();
};
