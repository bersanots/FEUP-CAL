#pragma once

#include "Includes.h"
#include "Utilizacao.h"

class Bicicleta {
protected:
	string bikeName; 			/**< Nome da bicicleta, composto pelas iniciais do tipo e um numero (ex: "u5" = bicicleta Urbana numero 5 (existem 4 antes desta)). */
	int price;					/**< Preco referente ao valor de uma mensalidade associada a um tipo de bicicleta. */
	Data abate;					/**< Data em que a bicicleta foi abatida. */
	vector<string> avarias;		/**< Lista de avarias da bicicleta. */
public:
	Bicicleta();				/**< Necessario para o overload do operador de extracao na classe utente.*/
	Bicicleta(string name);
	/**
	 * Destrutor virtual.
	 * */
	virtual ~Bicicleta()  {};

	//Métodos Get
	string getBikeName() const;
	int getPrice() const;
	vector<string> getAvarias() const;
	Data getAbate() const;

	//Métodos Set
	void setAvarias(vector<string> novasAvarias);
	void setAbate(Data dataAbate);

	//Others
	void addAvarias(string avaria);
};

class Urbana : public Bicicleta {
	static int id;				/**< Identificador da proxima bicicleta do tipo urbana */
public :
	Urbana(string bikeName);
	/**
	 * Destrutor da classe Urbana.
	 */
	~Urbana(){};

	//Métodos Get
	static int getID();
};

class UrbanaSimples : public Bicicleta {
	static int id;				/**< Identificador da proxima bicicleta do tipo urbana simples */
public :
	UrbanaSimples(string bikeName);
	/**
	 * Destrutor da classe UrbanaSimples.
	 */
	~UrbanaSimples(){};

	//Métodos Get
	static int getID();
};

class Corrida : public Bicicleta {
	static int id;				/**< Identificador da proxima bicicleta do tipo corrida */
public :
	Corrida(string bikeName);
	/**
	 * Destrutor da classe Corrida.
	 */
	~Corrida(){};

	//Métodos Get
	static int getID();
};

class Infantil : public Bicicleta {
	static int id;				/**< Identificador da proxima bicicleta do tipo infantil */
public :
	Infantil(string bikeName);
	/**
	 * Destrutor da classe Infantil.
	 */
	~Infantil(){};

	//Métodos Get
	static int getID();
};

