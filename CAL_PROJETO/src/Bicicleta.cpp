#include "Bicicleta.h"


//////////////////////
// CLASSE BICICLETA //
//////////////////////

Bicicleta::Bicicleta(){};

Bicicleta::Bicicleta(string name) {
	bikeName = name;
}

// METODOS GET //
string Bicicleta::getBikeName() const {
	return bikeName;
}




