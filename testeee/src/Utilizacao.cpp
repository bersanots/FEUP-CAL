#include "Utilizacao.h"

////////////////
// UTILIZACAO //
////////////////

/**
 * Construtor padrao da classe Utilizacao.
 */
Utilizacao::Utilizacao(){
	this->bikeType = " ";
	this->useTime = 0;
}

/**
 * Construtor da classe Utilizacao.
 * @param bikeType tipo de bicicleta usada nesta utilizacao
 * @param numHours numero de horas de uso da bicicleta
 * @param d data da utilizacao
 * @param pp nome do ponto de partilha
 * @param loc nome da localizacao do ponto de partilha
 */
Utilizacao::Utilizacao(string bikeType, unsigned int numHours, Data d, string pp, string loc) {
	this->bikeType = bikeType;
	this->useTime = numHours;
	this->data=d;
	this->pontoPartilha = pp;
	this->localizacao = loc;
}


// METODOS GET //

/**
 * @return Retorna a data da utilizacao.
 */
Data Utilizacao::getData()const {
	return data;
}

/**
 * @return Retorna o numero de horas de uso da utilizacao.
 */
unsigned int Utilizacao::getUseTime() const {
	return useTime;
}

/**
 * @return Retorna o tipo de bicicleta da utilizacao.
 */
string Utilizacao::getBikeType() const {
	return bikeType;
}

/**
 * @return Retorna o total pago pelo utente por esta utilizacao (so para regulares).
 */
double Utilizacao::getPrice() const {

	if(bikeType == "Urbana")
		return useTime*4;
	else if(bikeType == "Urbana Simples")
		return useTime*3;
	else if(bikeType == "Corrida")
		return useTime*5;
	else //bikeType == "Infantil"
		return useTime*2;
}


// OTHERS //

/**
 * Mostra a utilizacao no ecra de modo formatado.
 */
void Utilizacao::displayUtilizacao() const{

	cout << "Tipo de bicicleta: " << bikeType << endl;
	cout << "Número de horas: " << useTime << endl;
	cout << "Data (DD/MM/AAAA): " << data << endl;
	cout << "Ponto de Partilha: ECO_RIDES_" << pontoPartilha << endl;
	cout << "Localização: " << localizacao << endl;

	return;
}


////////////
/// DATA ///
////////////

/**
 * Construtor padrao da classe Data.
 */
Data::Data(){ dia=0; mes=0; ano=0;}

/**
 * Construtor da classe Data.
 * @param dia
 * @param mes
 * @param ano
 */
Data::Data(unsigned int dia,unsigned int mes,unsigned int ano){
	this->dia=dia;
	this->mes=mes;
	this->ano=ano;
}


// METODOS GET //

/**
 * @return Retorna o dia.
 */
unsigned int Data::getDia() const { return dia; }

/**
 * @return Retorna o mes.
 */
unsigned int Data::getMes() const { return mes; }

/**
 * @return Retorna o ano.
 */
unsigned int Data::getAno() const { return ano; }


// METODOS SET //

/**
 * Altera o dia.
 * @param d dia
 */
void Data::setDia(unsigned int d){
	this->dia=d;
}

/**
 * Altera o mes.
 * @param m mes
 */
void Data::setMes(unsigned int m){
	this->mes=m;
}

/**
 * Altera o ano.
 * @param a ano
 */
void Data::setAno(unsigned int a){
	this->ano=a;
}
