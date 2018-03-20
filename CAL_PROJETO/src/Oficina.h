#pragma once

#include "Includes.h"
#include "Bicicleta.h"
#include "BST.h"
#include "Peca.h"

class Oficina {
	BST<Peca> pieces;					/**< Arvore binaria de pesquisa de pecas da oficina. */
	vector<Bicicleta *> brokenBikes;	/**< Vetor de apontadores de bicicletas que aguardam reparacao. */
public:
	Oficina() : pieces(Peca(0,"","")) {}	/**< Construtor padrao da classe Oficina */

	//Métodos Get
	vector<Bicicleta *> getBrokenBikes() const;

	//Métodos Set
	void setBrokenBikes(vector<Bicicleta *> newBrokenBikes);

	//Métodos Add
	void addBrokenBike(Bicicleta * bike);
	void addPiece();

	//Métodos Remove
	void removePieceBST();
	void removePieceBike(int index, string piece);

	//Métodos Display
	void displayBSTInfo();
	void displayBrokenBikeInfo();
	void displayPieceLowestPrice();
	void displaySupliersInfo();

	//Others
	void buyPiece();

	//Friend functions
	friend ostream & operator <<(ostream & o, const Oficina & u);
	friend istream & operator >>(istream & i, Oficina & u);
};

/**
 * Overload do operador de insercao usado para escrever os objetos do tipo Oficina nos ficheiros,
 * de modo a guardar a informacao do sistema.
 */
inline ostream& operator <<(ostream & o, const Oficina & u)
{
	BSTItrIn<Peca> it(u.pieces);

	while(!it.isAtEnd()) {
		o << '-' << it.retrieve() << endl;
		it.advance();
	}

	o << u.brokenBikes.size() << endl;
	Bicicleta* b;

	for (unsigned int k = 0 ; k< u.brokenBikes.size() ; k++) {
		b = u.brokenBikes.at(k);
		vector<string> avarias = b->getAvarias();

		o << b->getBikeName() << ',' << avarias.size() << ',';

		for (unsigned int j = 0 ; j< avarias.size() ; j++) {
			o << avarias.at(j) << ',' ;
		}

		o << endl;
	}

	return o;
}

/**
 * Overload do operador de extracao usado para recolher dos ficheiros os objetos do tipo Oficina,
 * de modo a recriar o sistema da ultima execucao.
 */
inline istream& operator >>(istream & i, Oficina & u) {
	char b1, b2;
	unsigned int broken, avarias;

	b1 = i.peek();

	while (b1 == '-') {
		Peca p(0,"","");
		i >> b2 >> p;
		u.pieces.insert(p);
		b1 = i.peek();
	}

	i >> broken; i.ignore(100 , '\n');

	for (unsigned int k = 0 ; k< broken ; k++) {
		string b;
		Bicicleta* bike;
		getline(i, b,',');

		if(b.at(0) == 'u') {
			if(b.at(1) == 's') {
				bike = new UrbanaSimples(b);
			}
			else
				bike = new Urbana(b);
		}
		else if(b.at(0) == 'c')
			bike = new Corrida(b);
		else
			bike = new Infantil(b);

		i >> avarias >> b2;

		for (unsigned int j = 0 ; j< avarias ; j++) {
			string av;
			getline(i, av, ',');
			bike->addAvarias(av);
		}
		u.addBrokenBike(bike);
		i.ignore(100 , '\n');
	}

	return i;
}
