#include "Loja.h"

/**
 * Construtor Padrao da classe Loja
 */
Loja::Loja() {
	local = new Localizacao();
	vector<unsigned int> init;
	stock = init;
	capacity = 0;
	numberOpinions = 0;
	reputation = 0;
}

/**
 * Construtor da classe Loja
 * @param spot apontador para a Localizacao da loja
 * @param capacity capacidade de stock da loja
 * @param stock quantidade de bicicletas de cada tipo (stock[0] = num_Urbanas, stock[1] = num_Urbanas_Simples, stock[2] = num_Corrida, stock[3] = num_Infantis )
 */
Loja::Loja(Localizacao* spot, unsigned int capacity, vector<unsigned int> stock) {
	local = spot;
	this->capacity = capacity;
	this->stock = stock;
	this->numberOpinions = 0;
	this->reputation = 0;
}

/////////////////
// METODOS GET //
/////////////////

/**
 * @return Retorna a classificacao media da loja
 */
double Loja::getReputation() const {

	if(numberOpinions != 0)
		return ((double)reputation/numberOpinions);

	return 0;
}

/**
 * @return Retorna o numero de opinioes que contribuiram para a classificacao media
 */
unsigned int Loja::getNumberOpinions() const {
	return numberOpinions;
}

/**
 * @return Retorna a capacidade de stock da loja
 */
unsigned int Loja::getCapacity() const {
	return capacity;
}

/**
 * @param it indice para o tipo de bicicleta que se pretende consultar (it=0 >> Urbana, it=1 >> UrbanaSimples, it=2 >> Corrida, it=4 >> Infantil).
 * @return Retorna a quantidade em stock de bicicletas do tipo indicado por it.
 */
unsigned int Loja::getStock(unsigned int it) const {
	return stock.at(it);
}

/**
 * @return Retorna o apontador para a Localizacao da loja
 */
Localizacao* Loja::getLocal() const {
	return local;
}

/////////////////
// METODOS SET //
/////////////////

/**
 * Altera a reputacao da loja (reputacao = soma das classificacoes atribuidas a loja)
 * @param reputation nova reputacao
 */
void Loja::setReputation(unsigned int reputation) {
	this->reputation = this->reputation + reputation;
}

/**
 * Incrementa o numero de opinioes da loja
 */
void Loja::setNumberOpinions() {
	numberOpinions++;
}

/**
 * Altera a capacidade da loja
 * @param capacity nova capacidade
 */
void Loja::setCapacity(unsigned int capacity) {
	this->capacity = capacity;
}

/**
 * Altera a quantidade de bicicletas em stock de um determinado tipo, retirando bikes a quantidade existente
 * @param index indice do tipo de bicicleta a alterar a quantidade
 * @param bikes quantidade de bicicletas a retirar
 */
void Loja::setStock(int index, int bikes) {

	this->stock.at(index) = stock.at(index) - bikes;
}

////////////
// OTHERS //
////////////

/**
 * Overload do operador < para comparacao de 2 lojas.
 * Uma loja e menor que outra se a sua classificacao media for menor.
 * @param l1 loja com quem vai ser comparada
 * @return Retorna true se a condicao se verificar e false caso contrario.
 */
bool Loja::operator<(const Loja& l1) const {

	if(this->getReputation() < l1.getReputation())
		return true;

	return false;
}

/**
 * Reabastece o stock da loja caso esta tenha um stock atual de um tipo de bicicleta menor que 2.
 * @param index indice do tipo de bicicleta a verificar o stock
 */
void Loja::checkStock(int index) {

	if(stock.at(index) <= 1)
	{
		stock.at(index) = (int)capacity / 4;

		unsigned int sum { stock.at(0) + stock.at(1) + stock.at(2) + stock.at(3) };

		if(sum < capacity)
			stock.at(index)++;
	}
}
