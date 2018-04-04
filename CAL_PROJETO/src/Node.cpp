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

double Node::distanceTo(const Node & n2) const{
	double lat1r{}, lon1r{}, lat2r{}, lon2r{}, u{}, v{}, earthRadiusKm{6371.0};
	lat1r = this->getLatitude() * M_PI / 180;
	lon1r = this->getLongitude() * M_PI / 180;
	lat2r = n2.getLatitude() * M_PI / 180;
	lon2r = n2.getLongitude() * M_PI / 180;
	u = sin((lat2r - lat1r)/2);
	v = sin((lon2r - lon1r)/2);
	return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

void Node::operator =(const Node &n2) {
	this->id = n2.getID();
	Localizacao loc(n2.getLongitude(),n2.getLatitude());
	this->coords = loc;
}

bool Node::operator ==(const Node &n2) const {
	return (id == n2.id);
}
