#pragma once

#include "Includes.h"

class Localizacao {
	double x;		/**< Coordenadas x da localizacao. */
	double y;		/**< Coordenadas y da localizacao. */
public:
	Localizacao();		/**< Necessario para o overload do operador de extracao na classe utente.*/
	Localizacao(double x, double y);

	//Metodos Get
	double getX() const;
	double getY() const;

	//Metodos Set
	void setX(double x);
	void setY(double y);

	//Others
	double distancia(Localizacao local) const;
	Localizacao & operator =(Localizacao & l);
	friend ostream & operator <<(ostream & o, const Localizacao & l);
	friend istream & operator >>(istream & i, Localizacao & l);
};


/**
 * Overload do operador de insercao usado para escrever os objetos do tipo Localizacao nos ficheiros,
 * de modo a guardar a informacao do sistema.
 */
inline ostream& operator <<(ostream & o, const Localizacao & l)
{
	o << l.getX() << '/' <<  l.getY();
	return o;
}

/**
 * Overload do operador de extracao usado para recolher dos ficheiros os objetos do tipo Localizacao,
 * de modo a recriar o sistema da ultima execucao.
 */
inline istream& operator >>(istream & i, Localizacao & l)
{
	char b1{};
	double x{}, y{};
	i >> x >> b1 >> y;
	l.setX(x);
	l.setY(y);
	return i;
}
