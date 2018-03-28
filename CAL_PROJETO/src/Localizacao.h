#pragma once

#include "Includes.h"

class Localizacao {
	string nome;	/**< Nome da localizacao. */
	double x;		/**< Coordenadas x da localizacao. */
	double y;		/**< Coordenadas y da localizacao. */
public:
	Localizacao();		/**< Necessario para o overload do operador de extracao na classe utente.*/
	Localizacao(double x, double y);
	Localizacao(string nome, double x, double y);

	//Metodos Get
	string getNome() const;
	double getX() const;
	double getY() const;

	//Metodos Set
	void setNome(string nome);
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
	o << l.nome << '/' << l.x << '/' <<  l.y;
	return o;
}

/**
 * Overload do operador de extracao usado para recolher dos ficheiros os objetos do tipo Localizacao,
 * de modo a recriar o sistema da ultima execucao.
 */
inline istream& operator >>(istream & i, Localizacao & l)
{
	char b1;
	getline(i,l.nome,'/');
	i >> l.x >> b1 >> l.y;
	return i;
}
