#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Node {
private:
	int id;
	string name;
	pair<int, int> coords;

public:
	Node();
	~Node();
	Node(int id, int x, int y, string name);
	int getID() const;
	int getX() const;
	int getY() const;
	string getName() const;
	void setID(int ID);
	bool operator==(const Node & n2) const;
};
