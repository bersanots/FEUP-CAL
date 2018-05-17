#pragma once

#include "Includes.h"

class Bicicleta {
protected:
	string bikeName;

public:
	Bicicleta();
	Bicicleta(string name);

	virtual ~Bicicleta()  {};

	//Metodos Get
	string getBikeName() const;

};

