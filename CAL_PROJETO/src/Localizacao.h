#pragma once

#include "Includes.h"

class Localizacao {
	double x;
	double y;
public:
	Localizacao();
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

inline ostream& operator <<(ostream & o, const Localizacao & l)
{
	o << l.getX() << '/' <<  l.getY();
	return o;
}

inline istream& operator >>(istream & i, Localizacao & l)
{
	char b1{};
	double x{}, y{};
	i >> x >> b1 >> y;
	l.setX(x);
	l.setY(y);
	return i;
}
