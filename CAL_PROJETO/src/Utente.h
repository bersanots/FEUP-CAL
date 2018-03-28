#pragma once

#include "Includes.h"
#include "Localizacao.h"
#include "Bicicleta.h"
#include "Utilizacao.h"
#include "PontoPartilha.h"

class Utente {
protected:
	static int lastId;				/**< Numero de Identificacao do ultimo utente registado. */
	int id;							/**< Numero de Identificacao do utente. */
	string nome;					/**< Nome do utente. */
	Localizacao local;				/**< Localizacao atual do utente. */
	Bicicleta* bike;				/**< Bicicleta que o utente esta a usar, caso nao esteja a usar nenhuma, o valor de bike = 0. */
	vector<Utilizacao> historico;	/**< Utilizacoes liquidadas do utente. */
	bool disponivel = true;			/**< Se o utente esta a usar uma bicicleta disponivel = false, caso contrario disponivel = true. */
public:
	Utente();
	explicit Utente(string nome, Localizacao spot);

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

	/**
	 * Destrutor virtual.
	 */
	virtual ~Utente() {};

	//Others
	void alugaBicicleta(Bicicleta* b, Utilizacao ut);
	Bicicleta* removeBicicleta(vector<int> index_distancias);
	void updateLocation(int index);
	void displayHistoric() ;


};
/*

/**
 * Overload do operador de insercao usado para escrever os objetos do tipo Regular nos ficheiros,
 * de modo a guardar a informacao do sistema.

inline ostream& operator <<(ostream & o, const Utente & u)
{
	o << 'R' << ',' <<  u.getNome() << ',' << u.getLocalizacao() << ',' ;

	o << u.getHistorico().size() << ',' ;
	for (unsigned int k=0 ; k< u.getHistorico().size() ; k++){
		o << u.getHistorico().at(k) << ';' ;
	}

	return o;
}

/**
 * Overload do operador de extracao usado para recolher dos ficheiros os objetos do tipo Regular,
 * de modo a recriar o sistema da ultima execucao.

inline istream& operator >>(istream & i, Utente & u) {
	char b2, b3, b4;
	unsigned int hist;
	Utilizacao ut;
	string str, str2;
	getline(i,str,',');
	u.setNome(str);
	i >> u.getLocal() >> b2 >> hist >> b3;
	u.setLocal

	for(unsigned int k=0 ; k < hist ; k++){
		i >> ut >> b4;
		u.getHistorico().push_back(ut);
	}

	return i;
}
*/

