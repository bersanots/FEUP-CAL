#pragma once

#include "Includes.h"
#include "Localizacao.h"
#include "Bicicleta.h"
#include "Utente.h"

class PontoPartilha {
	Localizacao local;							/**< Localizacao do ponto de partilha. */
	unsigned int capacidade;					/**< Capacidade do ponto de partilha. */
	vector <vector<Bicicleta *> > bicicletas;	/**< Bicicletas existentes no ponto de partilha. */
	string nome;								/**< Nome do ponto de partilha. */
public:
	PontoPartilha();	/**< Necessario para o overload do operador de extracao na classe utente.*/
	PontoPartilha(Localizacao spot,unsigned int storage,string name);

	//Metodos Get
	Localizacao getLocal() const;
	string getNome() const;
	int getCapacidade() const;
	vector<int> getNumberOfBikes() const;
	vector <string> getBikeTypes();
	vector <vector<Bicicleta *> > getBikes() const;

	//Metodos Set
	void setNome(string name);

	//Others
	void limpaVectorBike();
	void removeBike(string name);
	void adicionaBike(Bicicleta* bike);
	friend ostream & operator <<(ostream & o, const PontoPartilha & p);
	friend istream & operator >>(istream & i, PontoPartilha & p);
};

/**
 * Overload do operador de insercao usado para escrever os objetos do tipo PontoPartilha nos ficheiros,
 * de modo a guardar a informacao do sistema.
 */
inline ostream& operator <<(ostream & o, const PontoPartilha & p)
{
	o << p.nome << '/' << p.local << '/' << p.capacidade << '[' << p.bicicletas.at(0).size() << ','
			<< p.bicicletas.at(1).size() << ',' << p.bicicletas.at(2).size() << ',' << p.bicicletas.at(3).size() << ']';
	return o;
}

/**
 * Overload do operador de extracao usado para recolher dos ficheiros os objetos do tipo PontoPartilha,
 * de modo a recriar o sistema da ultima execucao.
 */
/*
inline istream& operator >>(istream & i, PontoPartilha & p)
{
	char b1, b2, b3, b4, b5, b6;
	unsigned int u,uc,c,inf; //4 tipos de bicicletas
	vector<Bicicleta *> v1,v2,v3,v4;
	vector <vector<Bicicleta *> > bikes{v1,v2,v3,v4};

	Bicicleta * b; //apontador generico apenas para reservar espaco no vetor

	getline(i,p.nome,'/');
	i >> p.local >> b1 >> p.capacidade >> b2 >> u >> b3 >> uc >> b4 >> c >> b5 >> inf >> b6;

	for (unsigned int k=0 ; k<u ; k++){
		bikes.at(0).push_back(b);
	}
	for (unsigned int k=0 ; k<uc ; k++){
		bikes.at(1).push_back(b);
	}
	for (unsigned int k=0 ; k<c ; k++){
		bikes.at(2).push_back(b);
	}
	for (unsigned int k=0 ; k<inf ; k++){
		bikes.at(3).push_back(b);
	}

	p.bicicletas=bikes;
	return i;
}*/
