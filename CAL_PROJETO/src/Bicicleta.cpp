#include "Bicicleta.h"


//////////////////////
// CLASSE BICICLETA //
//////////////////////

/**
 * Construtor padrao da classe Bicicleta.
 */
Bicicleta::Bicicleta(){};

/**
 * Construtor da classe Bicicleta.
 * @param name nome da bicicleta
 */
Bicicleta::Bicicleta(string name) {
	bikeName = name;
}


// METODOS GET //

/**
 * @return Retorna o nome da bicicleta.
 */
string Bicicleta::getBikeName() const {
	return bikeName;
}




