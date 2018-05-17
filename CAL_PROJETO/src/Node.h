#pragma once
#include <iostream>
#include <vector>
#include "Localizacao.h"
#include "Includes.h"

using namespace std;

class Node {
protected:
	int id;
	Localizacao coords;

public:
	Node();
	~Node();
	Node(int id, double lon, double lat);
	int getID() const;
	double getLongitude() const;
	double getLatitude() const;
	double distanceTo(const Node & n2) const;
	void setID(int id);
	void setLocation(Localizacao loc);
	void operator=(const Node & n2);
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
	int id{};

	i >> id >> b1 >> loc >> b2;

	n.setID(id);
	n.setLocation(loc);

	return i;
}
