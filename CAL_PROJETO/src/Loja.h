#pragma once

#include "Includes.h"
#include "Localizacao.h"

class Loja {
	Localizacao* local;				/**< Apontador para a localizacao da loja. */
	unsigned int reputation;		/**< Soma das classificacoes atribuidas a loja. */
	unsigned int numberOpinions;	/**< Quantidade de classificacoes atribuidas a loja. */
	unsigned int capacity;			/**< Capacidade maxima da loja. */
	vector<unsigned int> stock;		/**< Quantidade de bicicletas em stock de cada tipo
										(vetor com 4 elementos => 4 tipos de bicicletas). */
public:
	Loja();
	Loja(Localizacao* spot, unsigned int capacity, vector<unsigned int> stock);

	//Metodos Get
	double getReputation() const;
	unsigned int getNumberOpinions() const;
	unsigned int getCapacity() const;
	unsigned int getStock(unsigned int it) const;
	Localizacao* getLocal() const;

	//Metodos Set
	void setReputation(unsigned int reputation);
	void setNumberOpinions();
	void setCapacity(unsigned int capacity);
	void setStock(int index, int bikes);

	//Others
	bool operator<(const Loja& l1) const;
	void checkStock(int index);

	//Friend functions
	friend ostream & operator <<(ostream & o, const Loja & l);
	friend istream & operator >>(istream & i, Loja & l);
};


/**
 * Overload do operador de insercao usado para escrever os objetos do tipo Loja nos ficheiros,
 * de modo a guardar a informacao do sistema.
 */
inline ostream& operator <<(ostream & o, const Loja & l)
{
	o << (*l.local) << ',' << l.numberOpinions << ',' << l.reputation << ',' << l.capacity << ';' ;

	o << l.stock.size() << ',' ;

	for (unsigned int k = 0 ; k < l.stock.size() ; k++ ) {
		o << l.stock.at(k) << ',';
	}

	return o;
}

/**
 * Overload do operador de extracao usado para recolher dos ficheiros os objetos do tipo Loja,
 * de modo a recriar o sistema da ultima execucao.
 */
inline istream& operator >>(istream & i, Loja & l) {
	char b1;
	unsigned int num_stock , num_bikes;
	Localizacao loc;

	i >> loc >> b1 >> l.numberOpinions >> b1 >> l.reputation >> b1 >> l.capacity >> b1;
	l.local = new Localizacao {loc};

	i >> num_stock >> b1 ;

	for (unsigned int k = 0 ; k < num_stock ; k++ ) {
		i >> num_bikes >> b1;
		l.stock.push_back(num_bikes);
	}

	return i;
}
