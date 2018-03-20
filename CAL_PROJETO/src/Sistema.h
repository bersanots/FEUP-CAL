#pragma once

#include "Excecoes.h"
#include "Includes.h"
#include "Utente.h"
#include "PontoPartilha.h"
#include "Localizacao.h"
#include "Oficina.h"
#include "Loja.h"
#include "Junkyard.h"

class Sistema {
	vector<PontoPartilha* > pontosPartilha;		/**< Pontos de partilha referentes ao sistema. */
	vector<Utente* > utentes;					/**< Utentes referentes ao sistema. */
	Oficina repairShop;							/**< Oficina de reparacao de bicicletas. */
	priority_queue<Loja> stores;				/**< Fila de prioridade de lojas.*/
	tabHAbates junkyard;						/**< Tabela de dispersao de bicicletas abatidas e que aguardam abate. */
	Data dataAtual = globalData;				/**< Data da ultima utilizacao do sistema.*/
public:
	Sistema() {}	/**< Construtor padrao da classe Sistema */

	//Métodos add
	void addPontoPartilha();
	void addNewUtente();
	void adicionaBike();
	void addStore();
	void addNewUtente(Utente* u1);				/**< Necessario para inclusao direta no sistema dos utentes extraidos do ficheiro.*/
	void addPontoPartilha(PontoPartilha* p);	/**< Necessario para inclusao direta no sistema dos pontos de partilha extraidos do ficheiro.*/

	//Métodos remove
	void removePonto();
	void removeUtente();
	void removeBike();
	void removeStore();
	void removeFromRepairShop();
	void removeFromJunkyard();

	//Métodos Get
	vector<Utente* > getUtentes() const;
	vector<PontoPartilha* > getPontosPartilha() const;
	Oficina& getOficina();
	priority_queue<Loja> getStores() const;
	tabHAbates getJunkyard() const;
	void getInfo() const;
	vector<int> getOrderedPP(int index) const;
	int getUtenteIndex(int identificacao) const;
	Data getDataAtual() const;

	//Métodos Set
	void setDataAtual(Data newData);
	void setStores(priority_queue<Loja> newStores);
	void setOficina(Oficina newRShop);
	void setJunkyard(tabHAbates newJunkyard);

	//Métodos display
	void displayNearestPP(int index) const;
	void displayUtentes() const;
	void displayStoreInfo() const;
	void displayMostRepStores() const;
	void displayJunkyardInfo() const;

	//Management algorithms
	void system_Manager(unsigned int index, string bikeType);
	bool generateBikeStatus(Bicicleta* bike);
	void updateData(Data data);

	//Others
	void alugaBike(int index);
	void devolveBike(int index);
	void compraBike(int index);
	int  mudaTipoUT(int index);
	void abateBike();
};

/**
 * Procura um valor x num vetor v de elementos comparaveis com os operadores de comparacao.
 * @param v vetor de elementos
 * @param x valor a procurar no vetor
 * @return Retorna o indice da primeira ocorrencia de x em v, se encontrar; senao, retorna -1.
 */
template <class T>
int SequentialSearch(const vector<T> &v, T x)
{
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i] == x)
			return i;// encontrou
	return -1; // não encontrou
}


