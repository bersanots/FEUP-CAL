#include "Includes.h"

template<class T>
class OpcaoInvalida {
public:
	T opcao;
	/**
	 *  Responsavel por tratar erros de input do utilizador, podendo estes ser de diferentes tipos.
	 */
	OpcaoInvalida(T op) { opcao = op;}
};


template<class T>
class AberturaFalhada {
	T ficheiro;
public:
	/**
	 * Contrutor da classe AberturaFalhada.
	 */
	AberturaFalhada(T file) { ficheiro = file;}
	/**
	 * Metodo get do nome do ficheiro cuja abertura falhou.
	 * @return nome do ficheiro
	 */
	T getFicheiro() const {return ficheiro;}
};
