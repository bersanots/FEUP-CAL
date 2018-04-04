#include "Node.h"

Node::Node() {
	this->id = 0;
}

Node::Node(long id, double lon, double lat) {
	this->id = id;
	Localizacao loc(lon,lat);
	this->coords = loc;
}

Node::~Node() {
}

void Node::setID(long id) {
	this->id = id;
}

void Node::setLocation(Localizacao loc){
	this->coords = loc;
}

long Node::getID() const {
	return this->id;
}

double Node::getLongitude() const {
	return this->coords.getX();
}

double Node::getLatitude() const {
	return this->coords.getY();
}

bool Node::operator ==(const Node &n2) const {
	return (id == n2.id);
}
