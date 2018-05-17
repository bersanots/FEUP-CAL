#include "Sistema.h"

PontoPartilha::PontoPartilha() : Node(){
	this->altitude = 0;
	this->capacidade = 0;
	this->preco = 0;
	this->nome = "";
}

PontoPartilha::PontoPartilha(int id, double lon, double lat, double alt, unsigned int storage,string name) : Node(id,lon,lat) {
	this->altitude = alt;
	this->capacidade = storage;
	this->preco = 10/alt;
	this->nome = name;
}

Bicicleta* PontoPartilha::removeBike() {
	Bicicleta* b = bicicletas.at(0);
	bicicletas.erase(bicicletas.begin());
	return b;
}

void PontoPartilha::adicionaBike(Bicicleta* bike) {
	bicicletas.push_back(bike);
}

void PontoPartilha::limpaVectorBike(){
	bicicletas.clear();
}

bool PontoPartilha::isFull() const{
	return capacidade==bicicletas.size();
}

/////////////////
// METODOS GET //
/////////////////

string PontoPartilha::getNome() const {
	return nome;
}

Localizacao PontoPartilha::getLocal() const {
	return coords;
}

double PontoPartilha::getAltitude() const{
	return altitude;
}

unsigned int PontoPartilha::getCapacidade() const {
	return capacidade;
}

vector<Bicicleta *> PontoPartilha::getBikes() const {
	return bicicletas;
}

double PontoPartilha::getPrice() {
	if(3/altitude < 1)
		return 2 * (3/ altitude);
	return 3/ altitude;

}

/////////////////
// METODOS SET //
/////////////////

void PontoPartilha::setNome(string name) {
	this->nome = name;
}

void PontoPartilha::setAltitude(double alt) {
	altitude = alt;
}

void PontoPartilha::setCapacidade(unsigned int cap) {
	this->capacidade = cap;
}
