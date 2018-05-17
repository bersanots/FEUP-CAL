#pragma once

#include "Excecoes.h"
#include "Includes.h"
#include "Utente.h"
#include "PontoPartilha.h"
#include "Localizacao.h"
#include "Node.h"
#include "Street.h"
#include "graphviewer.h"
#include "Grafo.h"


class Sistema {
	vector<PontoPartilha* > pontosPartilha;
	vector<Utente* > utentes;
	Graph<int> grafo;
	vector<Node> nos;
	vector<Street> estradas;
	Data dataAtual;

public:
	Sistema() {this->dataAtual = Data(11,4,2018);}

	//Metodos add
	void addNewUtente();
	void addNewUtente(Utente* u1);
	void addPontoPartilha(PontoPartilha* p);
	void addNode(Node n);
	void addStreet(Street st);

	//Metodos remove
	void removeUtente();

	//Metodos Get
	vector<Utente* > getUtentes() const;
	vector<PontoPartilha* > getPontosPartilha() const;
	vector<Node> getNodes() const;
	vector<Street> getStreets() const;
	void getInfo() const;
	vector<int> getOrderedPP(int index) const;
	int getUtenteIndex(int identificacao) const;
	Data getData() const;
	vector<int> path_rentavel(double client);

	//Others
	void criarGrafo();
	void incData();
	Node closestPoint(Localizacao l) const;
	Vertex<int> minDistance(bool modo_devolve) const;
	pair<float, int> bestChoice(bool modo_devolve) const;
	pair<float, int> cheapestPoint(bool modo_devolve) const;
	void alugaBike(int index);
	void devolveBike(int index);
	void system_Manager(unsigned int index, string bikeType);
	void displayUtentes() const;
	vector<pair<float,int>> organizePair(bool modo_devolve) const;
	double getDist(PontoPartilha p) const;
	void pesquisaRuas() const;

};

