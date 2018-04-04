#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Grafos.h"
#include "Node.h"

using namespace std;

class Street {
private:
	long id;
	string name;
	vector<Vertex<Node>*> vertices;
	bool twoWays;

public:
	Street();
	~Street();
	Street(long id, string name, vector<Vertex<Node>*> vertices, bool twoWays);
	long getID() const;
	string getName() const;
	vector<Vertex<Node>*> getVertices() const;
	void setID(long id);
	void setName(string name);
	void setTwoWays(bool value);
	void addVertex(Vertex<Node>* no);
	bool isTwoWays() const;
};


inline ostream& operator <<(ostream & o, Street st)
{
	o << st.getID() << ';' << st.getName() << ';' << st.isTwoWays() << ";";
	return o;
}


inline istream& operator >>(istream & i, Street & st) {
	char b{};
	string str{};
	bool val{};
	unsigned long id{};

	i >> id >> b;
	st.setID(id);

	getline(i,str,';');
	st.setName(str);

	i >> val >> b;
	st.setTwoWays(val);

	return i;
}
