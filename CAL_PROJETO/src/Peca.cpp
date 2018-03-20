#include "Peca.h"


/**
 * Construtor da classe Peca
 * @param lastPurchasePrice  preco da ultima compra
 * @param pieceType tipo de peca
 * @param supplier nome do fornecedor
 */
Peca::Peca(unsigned int lastPurchasePrice, string pieceType, string supplier) {
	this->lastPurchasePrice = lastPurchasePrice;
	this->pieceType = pieceType;
	this->supplier = supplier;
}

/////////////////
// METODOS GET //
/////////////////

/**
 * @return Retorna o preco da ultima compra.
 */
unsigned int Peca::getLastPurchasePrice() const {
	return lastPurchasePrice;
}

/**
 * @return Retorna o tipo de peca.
 */
string Peca::getPieceType() const {
	return pieceType;
}

/**
 * @return Retorna o nome do fornecedor.
 */
string Peca::getSupplier() const {
	return supplier;
}

/////////////////
// METODOS SET //
/////////////////

/**
 * Atualiza o preco da ultima compra
 * @param lastPurchasePrice novo preco da ultima compra
 */
void Peca::setLastPurchasePrice(unsigned int lastPurchasePrice) {
	this->lastPurchasePrice = lastPurchasePrice;
}

////////////
// OTHERS //
////////////

/**
 * Overload do operador < para comparacao de 2 pecas.
 * Uma peca e menor que outra se o tipo de peca e menor alfabeticamente.
 * Em caso de igualdade, e menor aquela que tem menor preco de ultima compra.
 * @param pt1 peca com quem vai ser comparada
 * @return Retorna true se a condicao se verificar e false caso contrario.
 */
bool Peca::operator< (const Peca &pt1) const {
	if(this->pieceType < pt1.getPieceType())
		return true;
	else if(this->pieceType == pt1.getPieceType())
	{
		if(this->lastPurchasePrice <= pt1.getLastPurchasePrice())
			return true;
	}
	return false;
}

/**
 * Overload do operador == para comparacao de 2 pecas.
 * Uma peca e igual a outra se tiverem o mesmo tipo e o mesmo fornecedor.
 * @param ps1 peca com quem vai ser comparada
 * @return Retorna true se a condicao se verificar e false caso contrario.
 */
bool Peca::operator==(const Peca &ps1) const {
	if((this->pieceType == ps1.getPieceType()) && (this->supplier == ps1.getSupplier()))
		return true;

	return false;
}
