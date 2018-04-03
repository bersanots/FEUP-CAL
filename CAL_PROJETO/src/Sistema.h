#pragma once

#include "Excecoes.h"
#include "Includes.h"
#include "Utente.h"
#include "PontoPartilha.h"
#include "Localizacao.h"
#include "Grafos.h"
#include "Node.h"
#include "Street.h"

class Sistema {
	vector<PontoPartilha* > pontosPartilha;		/**< Pontos de partilha referentes ao sistema. */
	vector<Utente* > utentes;					/**< Utentes referentes ao sistema. */
	Graph<Node> grafo;
	vector<Node> nos;
	vector<Street> estradas;

public:
	/**
	 *  Construtor padrao da classe Sistema
	 */
	Sistema() {}

	//Metodos add
	void addPontoPartilha();
	void addNewUtente();
	void adicionaBike();
	void addNewUtente(Utente* u1);				/**< Necessario para inclusao direta no sistema dos utente extraidos do ficheiro.*/
	void addPontoPartilha(PontoPartilha* p);	/**< Necessario para inclusao direta no sistema dos pontos de partilha extraidos do ficheiro.*/
	void addNode(Node n);
	void addStreet(Street st);

	//Metodos remove
	void removePonto();
	void removeUtente();
	void removeBike();

	//Metodos Get
	vector<Utente* > getUtentes() const;
	vector<PontoPartilha* > getPontosPartilha() const;
	vector<Node> getNodes() const;
	vector<Street> getStreets() const;
	void getInfo() const;
	vector<int> getOrderedPP(int index) const;
	int getUtenteIndex(int identificacao) const;

	//Others
	void alugaBike(int index);
	void devolveBike(int index);
	void system_Manager(unsigned int index, string bikeType);
	void displayNearestPP(int index) const;
	void displayUtentes() const;
};

/**
 * Procura um valor x num vetor v de elementos comparaveis com os operadores de comparacao.
 * @param v vetor de elementos
 * @param x valor a procurar no vetor
 * @return Retorna o indice da primeira ocorrencia de x em v, se encontrar; senao, retorna -1.
 */
template <class T>
int SequentialSearch(const vector<T> &v, T x)
{
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i] == x)
			return i;// encontrou
	return -1; // nao encontrou
}


