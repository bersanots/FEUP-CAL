#pragma once

#include "Includes.h"
#include "Localizacao.h"
#include "Bicicleta.h"
#include "Utente.h"

class PontoPartilha {
	Localizacao local;							/**< Localizacao do ponto de partilha. */
	unsigned int capacidade;					/**< Capacidade do ponto de partilha. */
	vector<Bicicleta*> bicicletas;				/**< Bicicletas existentes no ponto de partilha. */
	string nome;								/**< Nome do ponto de partilha. */
public:
	PontoPartilha();	/**< Necessario para o overload do operador de extracao na classe utente.*/
	PontoPartilha(Localizacao spot,unsigned int storage,string name);

	//Metodos Get
	Localizacao getLocal() const;
	string getNome() const;
	unsigned int getCapacidade() const;
	vector<Bicicleta*> getBikes() const;

	//Metodos Set
	void setLocal(Localizacao loc);
	void setNome(string name);
	void setCapacidade(unsigned int cap);

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
	o << p.getNome() << '/' << p.getLocal() << '/' << p.getCapacidade() << '/' << p.getBikes().size();
	return o;
}

/**
 * Overload do operador de extracao usado para recolher dos ficheiros os objetos do tipo PontoPartilha,
 * de modo a recriar o sistema da ultima execucao.
 */

inline istream& operator >>(istream & i, PontoPartilha & p)
{
	string str{};
	Localizacao loc{};
	unsigned int n1{}, n2{};
	char b1{}, b2{};

	Bicicleta * b = new Bicicleta{}; //apontador generico apenas para reservar espaco no vetor

	getline(i,str,'-');
	p.setNome(str);

	i >> loc >> b1 >> n1 >> b2 >> n2;
	p.setLocal(loc);
	p.setCapacidade(n1);

	p.limpaVectorBike();
	for (unsigned int k=0 ; k<n2 ; k++){
		p.adicionaBike(b);
	}

	return i;
}
