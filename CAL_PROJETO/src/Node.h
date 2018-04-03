#pragma once
#include <iostream>
#include <vector>
#include "Localizacao.h"

using namespace std;

class Node {
private:
	int id;
	Localizacao coords;

public:
	Node();
	~Node();
	Node(int id, double lon, double lat);
	int getID() const;
	double getLongitude() const;
	double getLatitude() const;
	void setID(int ID);
	void setLocation(Localizacao loc);
	bool operator==(const Node & n2) const;
};


inline ostream& operator <<(ostream & o, Node n)
{
	o << n.getID() << ';' << n.getLongitude() << ';' << n.getLatitude() << ';';
	return o;
}


inline istream& operator >>(istream & i, Node & n) {
	char b1{}, b2{};
	Localizacao loc{};
	unsigned int id{};

	i >> id >> b1 >> loc >> b2;

	n.setID(id);
	n.setLocation(loc);

	return i;
}
