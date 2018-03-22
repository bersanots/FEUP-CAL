#include "Sistema.h"

/**
 * Construtor padrao da classe PontoPartilha.
 */
PontoPartilha::PontoPartilha(){
	capacidade = 0;
	vector<Bicicleta *> v1,v2,v3,v4;
	bicicletas.push_back(v1);
	bicicletas.push_back(v2);
	bicicletas.push_back(v3);
	bicicletas.push_back(v4);
}

/**
 * Construtor da classe PontoPartilha.
 * @param name nome do ponto de partilha
 * @param spot localizacao do ponto de partilha
 * @param storage capacidade do ponto de partilha
 */
PontoPartilha::PontoPartilha(Localizacao spot,unsigned int storage,string name) {
	local = spot;
	capacidade = storage;
	nome = name;
	vector<Bicicleta *> v1,v2,v3,v4;
	bicicletas.push_back(v1);
	bicicletas.push_back(v2);
	bicicletas.push_back(v3);
	bicicletas.push_back(v4);
}

/**
 * Remove a bicicleta bike do ponto de partilha.
 * @param name nome da bicicleta que se pretende remover
 */
void PontoPartilha::removeBike(string name) {

	vector<Bicicleta *> bikes;
	int indicator;

	if(name.at(0) == 'u')
	{
		if(name.at(1) == 's')
			indicator = 1;
		else
			indicator = 0;
	}
	else if(name.at(0) == 'c')
		indicator = 2;
	else
		indicator = 3;

	for(unsigned int i = 0; i < bicicletas.at(indicator).size(); i++)
	{
		if(bicicletas.at(indicator).at(i)->getBikeName() == name)
			bicicletas.at(indicator).erase(bicicletas.at(indicator).begin() + i);
	}
}

/**
 * Adiciona a bicicleta bike do ponto de partilha.
 * @param bike apontador de bicicleta que se pretende adicionar
 */
void PontoPartilha::adicionaBike(Bicicleta* bike) {

	int indicator;
	string name = bike->getBikeName();

	if(name.at(0) == 'u')
	{
		if(name.at(1) == 's')
			indicator = 1;
		else
			indicator = 0;
	}
	else if(name.at(0) == 'c')
		indicator = 2;
	else
		indicator = 3;

	bicicletas.at(indicator).push_back(bike);

	return;
}

/**
 * Limpa o vetor das bicicletas do ponto de partilha, de modo que o mesmo fica sem bicicletas.
 */
void PontoPartilha::limpaVectorBike(){
	bicicletas.at(0).clear();
	bicicletas.at(1).clear();
	bicicletas.at(2).clear();
	bicicletas.at(3).clear();
}


/////////////////
// METODOS GET //
/////////////////

/**
 * @return Retorna o nome do ponto de partilha.
 */
string PontoPartilha::getNome() const {
	return nome;
}

/**
 * @return Retorna a localizacao do ponto de partilha.
 */
Localizacao PontoPartilha::getLocal() const {
	return local;
}

/**
 * @return Retorna a capacidade do ponto de partilha.
 */
int PontoPartilha::getCapacidade() const {
	return capacidade;
}

/**
 * Retorna um vetor com a quantidade de cada tipo de bicicletas existentes no ponto de partilha.
 * O vetor e composto pelos 4 elementos segintes:
 *  (1) quantidade de bicicletas do tipo "Urbana",
 *  (2) quantidade de bicicletas do tipo "Urbana Simples",
 *  (3) quantidade de bicicletas do tipo "Corrida",
 *  (4) quantidade de bicicletas do tipo "Infantil".
 * @return Retorna vetor de inteiros.
 */
vector<int> PontoPartilha::getNumberOfBikes() const {

	vector<int> number_bikes;

	for(unsigned int i = 0; i < bicicletas.size(); i++){
		number_bikes.push_back(bicicletas.at(i).size());
	}

	return number_bikes;
}

/**
 * @return Retorna um vetor com os tipos de bicicletas existentes no ponto de partilha.
 */
vector <string> PontoPartilha::getBikeTypes() {
	vector <string> bikeTypes;

	if(bicicletas.at(0).size() != 0)
		bikeTypes.push_back("Urbana");

	if(bicicletas.at(1).size() != 0)
		bikeTypes.push_back("Urbana Simples");

	if(bicicletas.at(2).size() != 0)
		bikeTypes.push_back("Corrida");

	if(bicicletas.at(3).size() != 0)
		bikeTypes.push_back("Infantil");

	return bikeTypes;
}

/**
 * @return Retorna as bicicletas do ponto de partilha.
 */
vector <vector<Bicicleta *> > PontoPartilha::getBikes() const {
	return bicicletas;
}

/////////////////
// METODOS SET //
/////////////////

/**
 * Altera o nome do ponto de partilha.
 * @param name novo nome
 */
void PontoPartilha::setNome(string name) {
	nome = name;
}
