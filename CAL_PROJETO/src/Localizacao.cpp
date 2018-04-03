#include "Localizacao.h"

/**
 * Construtor padrao da classe Lcalizacao.
 */
Localizacao::Localizacao(){
	this->x = 0.0;
	this->y = 0.0;
}

/**
 * Construtor da classe Localizacao.
 * @param x coordenada x da localizacao
 * @param y coordenada y da localizacao
 */
Localizacao::Localizacao(double x, double y) {
	this->x = x;
	this->y = y;
}


/////////////////
// METODOS GET //
/////////////////

/**
 * @return Retorna coordenada x da localizacao.
 */
double Localizacao::getX() const{
	return x;
}

/**
 * @return Retorna a coordenada y da localizacao.
 */
double Localizacao::getY() const{
	return y;
}


/////////////////
// METODOS SET //
/////////////////

/**
 * Altera a coordenada x da localizacao.
 * @param x nova coordenada
 */
void Localizacao::setX(double x) {
	this->x = x;
}

/**
 * Altera a coordenada y da localizacao.
 * @param y nova coordenada
 */
void Localizacao::setY(double y) {
	this->y = y;
}

////////////
// OTHERS //
////////////

/**
 * Construtor de copia.
 */
Localizacao & Localizacao::operator =(Localizacao & l) {
	setX(l.x);
	setY(l.y);
	return *this;
}

/**
 * Metodo para calcular a distancia entre duas Localizacoes.
 * @param local localizacao
 */
double Localizacao::distancia(Localizacao local) const{
	return sqrt(pow((local.x - x),2) + pow((local.y - y),2));
}
