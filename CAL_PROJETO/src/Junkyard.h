#pragma once

#include "Includes.h"
#include "Bicicleta.h"

struct bikeHash
{
	/**
	 * Funcao dispersao para tabela de abates
	 */
	int operator() (const Bicicleta & bic) const{
		int v {0};
		for ( unsigned int i=0; i< bic.getBikeName().size(); i++ )
			v = 37*v + bic.getBikeName().at(i);
		return v;
	}

	/**
	 * Operador de igualdade para a tabela de abates
	 */
	bool operator() (const Bicicleta & b1, const Bicicleta & b2) const {
		return b1.getBikeName() == b2.getBikeName();
	}
};

typedef unordered_set<Bicicleta, bikeHash, bikeHash> tabHAbates;
