#include "Sistema.h"

/**
 * Construtor padrao da classe PontoPartilha.
 */
PontoPartilha::PontoPartilha(){
	capacidade = 0;
	nome = "";
	Localizacao loc{};
	local = loc;
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
}

/**
 * Remove a bicicleta bike do ponto de partilha.
 * @param name nome da bicicleta que se pretende remover
 */
void PontoPartilha::removeBike(string name) {

	for(unsigned int i = 0; i < bicicletas.size(); i++)
	{
		if(bicicletas.at(i)->getBikeName() == name)
			bicicletas.erase(bicicletas.begin() + i);
	}
}

/**
 * Adiciona a bicicleta bike do ponto de partilha.
 * @param bike apontador de bicicleta que se pretende adicionar
 */
void PontoPartilha::adicionaBike(Bicicleta* bike) {
	bicicletas.push_back(bike);
}

/**
 * Limpa o vetor das bicicletas do ponto de partilha, de modo que o mesmo fica sem bicicletas.
 */
void PontoPartilha::limpaVectorBike(){
	bicicletas.clear();
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
unsigned int PontoPartilha::getCapacidade() const {
	return capacidade;
}


/**
 * @return Retorna as bicicletas do ponto de partilha.
 */
vector<Bicicleta *> PontoPartilha::getBikes() const {
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

void PontoPartilha::setLocal(Localizacao loc) {
	local = loc;
}

void PontoPartilha::setCapacidade(unsigned int cap) {
	capacidade = cap;
}
