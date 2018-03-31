#pragma once

#include "Includes.h"

class Data {
protected:
	unsigned int dia, mes, ano;
public:
	Data();		/**< Necessario para o overload do operador de extracao na classe utente.*/
	Data(unsigned int dia,unsigned int mes,unsigned int ano);
	friend ostream & operator<<(ostream & o, const Data & d);
	friend istream & operator>>(istream & i, Data & d);

	//Metodos Get
	unsigned int getDia() const;
	unsigned int getMes() const;
	unsigned int getAno() const;

	//Metodos Set
	void setDia(unsigned int d);
	void setMes(unsigned int m);
	void setAno(unsigned int a);
};

/**
 * Overload do operador de insercao usado para escrever os objetos do tipo Data nos ficheiros,
 * de modo a guardar a informacao do sistema.
 */
inline ostream & operator<< (ostream & o, const Data & d){
	o << d.dia << '/' << d.mes << '/' << d.ano;
	return o;
}

/**
 * Overload do operador de extracao usado para recolher dos ficheiros os objetos do tipo Data,
 * de modo a recriar o sistema da ultima execucao.
 */
inline istream & operator>> (istream & i, Data & d)
{
	char b1{}, b2{};
	return i >> d.dia >> b1 >> d.mes >> b2 >> d.ano;
}


class Utilizacao {
private:
	Data data;				/**< Data da respetiva utilizacao.*/
	unsigned int useTime;	/**< Numero de horas de uso da bicicleta.*/
	string pontoPartilha;	/**< Nome do ponto de partilha onde a bicicleta foi alugada.*/
public:
	Utilizacao();			/**< Necessario para o overload do operador de extracao na classe utente*/
	Utilizacao(unsigned int numHours, Data d, string pp);

	//Metodos Get
	Data getData() const;
	unsigned int getUseTime() const;
	string getPPName() const;
	double getPrice() const;

	//Metodos Set
	void setData(Data d);
	void setUseTime(unsigned int time);
	void setPPName(string name);

	//Others
	void displayUtilizacao() const;
	friend ostream & operator <<(ostream & o, const Utilizacao & u);
	friend istream & operator >>(istream & i, Utilizacao & u);

	friend class Data;
};

/**
 * Overload do operador de insercao usado para escrever os objetos do tipo Utilizacao nos ficheiros,
 * de modo a guardar a informacao do sistema.
 */
inline ostream& operator <<(ostream & o, const Utilizacao & u)
{
	o << u.getPPName() << '-' << u.getUseTime() << '-' <<  u.getData();
	return o;
}

/**
 * Overload do operador de extracao usado para recolher dos ficheiros os objetos do tipo Utilizacao,
 * de modo a recriar o sistema da ultima execucao.
 */
inline istream& operator >>(istream & i, Utilizacao & u) {
	char b1{};
	string str{};
	unsigned int n{};
	Data d{};
	getline(i,str,'-');
	i >> n >> b1 >> d;
	u.setPPName(str);
	u.setUseTime(n);
	u.setData(d);
	return i;
}
