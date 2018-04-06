#pragma once

#include "Includes.h"
#include "Localizacao.h"
#include "Bicicleta.h"
#include "Utente.h"
#include "Node.h"

class PontoPartilha : public Node{
	double altitude;
	float preco;
	unsigned int capacidade;					/**< Capacidade do ponto de partilha. */
	vector<Bicicleta*> bicicletas;				/**< Bicicletas existentes no ponto de partilha. */
	string nome;								/**< Nome do ponto de partilha. */
public:
	PontoPartilha();	/**< Necessario para o overload do operador de extracao na classe utente.*/
	PontoPartilha(long long id, double lon, double lat, double alt, unsigned int storage,string name);

	//Metodos Get
	Localizacao getLocal() const;
	string getNome() const;
	double getAltitude() const;
	unsigned int getCapacidade() const;
	vector<Bicicleta*> getBikes() const;

	//Metodos Set
	void setNome(string name);
	void setCapacidade(unsigned int cap);
	void setAltitude(double alt);

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
	o << p.getNome() << '/' << p.getID() << '/' << p.getLocal() << '/' << p.getAltitude() << '/' << p.getCapacidade() << '/' << p.getBikes().size() << '/';
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
	double alt{};
	unsigned int n1{}, n2{};
	long long id{};
	char b1{}, b2{}, b3{}, b4{}, b5{};

	Bicicleta * b = new Bicicleta{}; //apontador generico apenas para reservar espaco no vetor

	getline(i,str,'/');
	p.setNome(str);

	i >> id >> b1 >> loc >> b2 >> alt >> b3 >> n1 >> b4 >> n2 >> b5;
	p.setID(id);
	p.setLocation(loc);
	p.setAltitude(alt);
	p.setCapacidade(n1);

	p.limpaVectorBike();
	for (unsigned int k=0 ; k<n2 ; k++){
		p.adicionaBike(b);
	}

	return i;
}
