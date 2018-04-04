#pragma once
#include <iostream>
#include <vector>
#include "Localizacao.h"
#include "Includes.h"

using namespace std;

class Node {
protected:
	long id;
	Localizacao coords;

public:
	Node();
	~Node();
	Node(long id, double lon, double lat);
	long getID() const;
	double getLongitude() const;
	double getLatitude() const;
	double distanceTo(const Node & n2) const;
	void setID(long ID);
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
	long id{};

	i >> id >> b1 >> loc >> b2;

	n.setID(id);
	n.setLocation(loc);

	return i;
}
