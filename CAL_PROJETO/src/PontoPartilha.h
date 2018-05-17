#pragma once

#include "Includes.h"
#include "Localizacao.h"
#include "Bicicleta.h"
#include "Utente.h"
#include "Node.h"

class PontoPartilha : public Node{
	double altitude;
	float preco;
	unsigned int capacidade;
	vector<Bicicleta*> bicicletas;
	string nome;
public:
	PontoPartilha();
	PontoPartilha(int id, double lon, double lat, double alt, unsigned int storage,string name);

	//Metodos Get
	Localizacao getLocal() const;
	string getNome() const;
	double getAltitude() const;
	unsigned int getCapacidade() const;
	vector<Bicicleta*> getBikes() const;
	double getPrice();

	//Metodos Set
	void setNome(string name);
	void setCapacidade(unsigned int cap);
	void setAltitude(double alt);

	//Others
	void limpaVectorBike();
	Bicicleta* removeBike();
	void adicionaBike(Bicicleta* bike);
	bool isFull() const;
	friend ostream & operator <<(ostream & o, const PontoPartilha & p);
	friend istream & operator >>(istream & i, PontoPartilha & p);
};

inline ostream& operator <<(ostream & o, const PontoPartilha & p)
{
	o << p.getNome() << '/' << p.getID() << '/' << p.getLocal() << '/' << p.getAltitude() << '/' << p.getCapacidade() << '/' << p.getBikes().size() << '/';
	return o;
}

inline istream& operator >>(istream & i, PontoPartilha & p)
{
	string str;
	Localizacao loc;
	double alt;
	unsigned int n1, n2;
	int id=0;
	char b1=0, b2=0, b3=0, b4=0, b5=0;

	Bicicleta * b = new Bicicleta; //apontador generico apenas para reservar espaco no vetor

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
