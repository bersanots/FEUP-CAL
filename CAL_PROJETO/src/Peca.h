#pragma once

#include "Includes.h"

class Peca {
	unsigned int lastPurchasePrice;		/**< Preco da ultima compra da peca. */
	string pieceType;					/**< Tipo da peca. */
	string supplier;					/**< Nome do fornecedor. */
public:
	Peca(unsigned int lastPurchasePrice, string pieceType, string supplier);

	//Métodos Get
	unsigned int getLastPurchasePrice() const;
	string getPieceType() const;
	string getSupplier() const;

	//Métodos Set
	void setLastPurchasePrice(unsigned int lastPurchasePrice);

	//Others
	bool operator< (const Peca &ps1) const;
	bool operator==(const Peca &ps1) const;

	//Friend functions
	friend ostream & operator <<(ostream & o, const Peca & p);
	friend istream & operator >>(istream & i, Peca & p);
};

/**
 * Overload do operador de insercao usado para escrever os objetos do tipo Peca nos ficheiros,
 * de modo a guardar a informacao do sistema.
 */
inline ostream& operator <<(ostream & o, const Peca & p)
{
	o << p.lastPurchasePrice << ',' << p.pieceType << ',' << p.supplier ;
	return o;
}

/**
 * Overload do operador de extracao usado para recolher dos ficheiros os objetos do tipo Peca,
 * de modo a recriar o sistema da ultima execucao.
 */
inline istream& operator >>(istream & i, Peca & p) {
	char b1;

	i >> p.lastPurchasePrice >> b1;
	getline(i, p.pieceType, ',');
	getline(i, p.supplier, '\n');

	return i;
}
