#include "Includes.h"

template<class T>
class OpcaoInvalida {
public:
	T opcao;
	OpcaoInvalida(T op) { opcao = op;}
};


template<class T>
class AberturaFalhada {
	T ficheiro;
public:
	AberturaFalhada(T file) { ficheiro = file;}
	T getFicheiro() const {return ficheiro;}
};
