#include "Localizacao.h"

/**
 * Construtor padrao da classe Lcalizacao.
 */
Localizacao::Localizacao(){
	this->nome = "";
	this->x = 0.0;
	this->y = 0.0;
}

/**
 * Construtor da classe Localizacao.
 * @param x coordenada x da localizacao
 * @param y coordenada y da localizacao
 */
Localizacao::Localizacao(double x, double y) {
	this->nome = "";
	this->x = x;
	this->y = y;
}

/**
 * Construtor da classe Localizacao.
 * @param nome nome da localizacao
 * @param x coordenada x da localizacao
 * @param y coordenada y da localizacao
 */
Localizacao::Localizacao(string nome, double x, double y){
	this->nome = nome;
	this->x = x;
	this->y = y;
}

/////////////////
// METODOS GET //
/////////////////

/**
 * @return Retorna o nome da localizacao.
 */
string Localizacao::getNome() const{
	return nome;
}

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
 * Altera o nome da localizacao.
 * @param nome novo nome
 */
void Localizacao::setNome(string nome) {
	this->nome = nome;
}

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
	setNome(l.nome);
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
