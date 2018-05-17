#include "Localizacao.h"

Localizacao::Localizacao(){
	this->x = 0.0;
	this->y = 0.0;
}

Localizacao::Localizacao(double x, double y) {
	this->x = x;
	this->y = y;
}


/////////////////
// METODOS GET //
/////////////////

double Localizacao::getX() const{
	return x;
}

double Localizacao::getY() const{
	return y;
}


/////////////////
// METODOS SET //
/////////////////

void Localizacao::setX(double x) {
	this->x = x;
}

void Localizacao::setY(double y) {
	this->y = y;
}

////////////
// OTHERS //
////////////

Localizacao & Localizacao::operator =(Localizacao & l) {
	setX(l.x);
	setY(l.y);
	return *this;
}

double Localizacao::distancia(Localizacao local) const{
	return sqrt(pow((local.x - x),2) + pow((local.y - y),2));
}
