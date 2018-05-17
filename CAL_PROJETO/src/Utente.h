#pragma once

#include "Includes.h"
#include "Localizacao.h"
#include "Bicicleta.h"
#include "Utilizacao.h"
#include "PontoPartilha.h"

class Utente {
protected:
	static int lastId;
	int id;
	string nome;
	Localizacao local;
	Bicicleta* bike;
	vector<Utilizacao> historico;
	bool disponivel = true;
public:
	Utente();
	Utente(string nome, Localizacao spot);

	//Metodos Get
	static int getLastId();
	int getId() const;
	string getNome() const;
	Localizacao getLocalizacao() const;
	Bicicleta* getBike() const;
	bool getAvailable() const;
	vector<Utilizacao> getHistorico();

	//Metodos Set
	static void setLastId();
	void setIDBackward();
	void setID(int identificacao);
	void setUtenteLocation(Localizacao spot);
	void setAvailable();
	void setBike(Bicicleta* bike);
	void setHistoric(Utilizacao ut);
	void setNome(string nome);
	void addUse(Utilizacao ut);

	virtual ~Utente() {};

	//Others
	void alugaBicicleta(Bicicleta* b, Utilizacao ut);
	Bicicleta* removeBicicleta();
	void updateLocation(int index);
	void displayHistoric() ;


};


inline ostream& operator <<(ostream & o, Utente u)
{
	o << u.getNome() << ',' << u.getLocalizacao() << ',' ;

	o << u.getHistorico().size() << ',' ;
	for (unsigned int k=0 ; k< u.getHistorico().size() ; k++){
		o << u.getHistorico().at(k) << ';' ;
	}

	return o;
}


inline istream& operator >>(istream & i, Utente & u) {
	char b2{}, b3{}, b4{};
	unsigned int hist{};
	Utilizacao ut{};
	Localizacao loc{};
	string str{}, str2{};

	getline(i,str,',');
	u.setNome(str);
	i >> loc >> b2 >> hist >> b3;
	u.setUtenteLocation(loc);

	for(unsigned int k=0 ; k < hist ; k++){
		i >> ut >> b4;
		u.addUse(ut);
	}

	return i;
}

