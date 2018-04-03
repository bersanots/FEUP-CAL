#include "Street.h"

Street::Street() {
}

Street::Street(int id, string name, vector<Vertex<Node>*> vertices, bool twoWays) {
	this->id = id;
	this->name = name;
	this->vertices = vertices;
	this->twoWays = twoWays;
}

Street::~Street() {
}

int Street::getID() const {
	return this->id;
}

string Street::getName() const {
	return this->name;
}

vector<Vertex<Node>*> Street::getVertices() const {
	return this->vertices;
}

void Street::setID(int id){
	this->id = id;
}

void Street::setName(string name){
	this->name = name;
}

void Street::setTwoWays(bool value){
	this->twoWays = value;
}

void Street::addVertex(Vertex<Node>* no){
	vertices.push_back(no);
}

bool Street::isTwoWays() const {
	return this->twoWays;
}
