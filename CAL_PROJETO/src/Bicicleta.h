#pragma once

#include "Includes.h"

class Bicicleta {
protected:
	string bikeName; 			/**< Nome da bicicleta, composto pelas iniciais do tipo e um numero (ex: "u5" = bicicleta Urbana numero 5 (existem 4 antes desta)). */

public:
	Bicicleta();				/**< Necessario para o overload do operador de extracao na classe utente.*/
	Bicicleta(string name);
	/**
	 * Destrutor virtual.
	 * */
	virtual ~Bicicleta()  {};

	//M�todos Get
	string getBikeName() const;

};

