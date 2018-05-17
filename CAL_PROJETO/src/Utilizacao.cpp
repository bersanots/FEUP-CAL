#include "Utilizacao.h"

////////////////
// UTILIZACAO //
////////////////

Utilizacao::Utilizacao(){
	this->useTime = 0;
}

Utilizacao::Utilizacao(unsigned int numHours, Data d, string pp) {
	this->useTime = numHours;
	this->data=d;
	this->pontoPartilha = pp;
}


// METODOS GET //

Data Utilizacao::getData()const {
	return data;
}

unsigned int Utilizacao::getUseTime() const {
	return useTime;
}

string Utilizacao::getPPName() const{
	return pontoPartilha;
}

double Utilizacao::getPrice() const {
	return useTime*4;
}


// METODOS SET //

void Utilizacao::setData(Data d) {
	this->data = d;
}

void Utilizacao::setUseTime(unsigned int time) {
	this->useTime = time;
}

void Utilizacao::setPPName(string name){
	this->pontoPartilha = name;
}


// OTHERS //

void Utilizacao::displayUtilizacao() const{

	cout << "Numero de horas: " << useTime << endl;
	cout << "Data (DD/MM/AAAA): " << data << endl;
	cout << "Ponto de Partilha: ECO_RIDES_" << pontoPartilha << endl;

	return;
}


////////////
/// DATA ///
////////////

Data::Data(){ dia=0; mes=0; ano=0;}

Data::Data(unsigned int dia,unsigned int mes,unsigned int ano){
	this->dia=dia;
	this->mes=mes;
	this->ano=ano;
}


// METODOS GET //

unsigned int Data::getDia() const { return dia; }

unsigned int Data::getMes() const { return mes; }

unsigned int Data::getAno() const { return ano; }


// METODOS SET //

void Data::setDia(unsigned int d){
	this->dia=d;
}

void Data::setMes(unsigned int m){
	this->mes=m;
}

void Data::setAno(unsigned int a){
	this->ano=a;
}
