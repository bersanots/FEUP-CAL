#include "Sistema.h"


/////////////////
// METODOS ADD //
/////////////////

/**
 * Apresenta os passos necessarios para criacao de um novo ponto de partilha, pedindo para introduzir
 * o nome, a localizacao e a capacidade, por fim, adiciona-o ao sistema.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::addPontoPartilha() {

	cout << "Adiciona Ponto de Partilha:" << endl << endl;

	string nome{},locname{};
	unsigned int value{};
	string option{};
	bool cond{false};

	cin.ignore(1000,'\n');

	while(1)
	{
		try {
			cout << "Nome do Ponto de Partilha: " ;
			getline(cin,nome);
			if(valid_word(nome) == false)
				throw OpcaoInvalida<string>(nome);


			for(unsigned int i = 0; i < pontosPartilha.size(); i++)
			{
				if(pontosPartilha.at(i)->getNome() == nome)
					cond = true;
			}

			if(cond == true)
				throw OpcaoInvalida<string>(nome);

			break;
		}
		catch (OpcaoInvalida<string> &op) {
			if(cond == true)
				cout << "Ja existe esse nome (" << op.opcao << ") ! Tente novamente." << endl;
			else
				cout << "Nome invalido (" << op.opcao << ") ! Tente novamente." << endl;
			cond = false;
			cin.clear();
		}
	}

	Localizacao spot{};
	bool newcord{true};

	cout << endl << "Localizacao: " << endl << endl;

	double coordX{}, coordY{};

	do
	{
		newcord = true;
		cout << "Indique as coordenadas GPS:" << endl;

		while(1)
		{
			try{
				cout << endl << "Coordenada X [-90 , 90]: ";
				cin >> option;
				cin.ignore(1000,'\n');
				if(valid_number_double(option) == false)
					throw OpcaoInvalida<string>(option);

				coordX = stod(option);

				if((coordX > 90) || (coordX < -90))
					throw OpcaoInvalida<double>(coordX);

				break;
			}
			catch (OpcaoInvalida<string> &op){

				cout << "Coordenada invalida (" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
			catch (OpcaoInvalida<double> &op){

				cout << "Fora de alcance (" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
		};

		while(1)
		{
			try{
				cout << endl << "Coordenada Y [-180 , 180]: ";
				cin >> option;
				cin.ignore(1000,'\n');
				if(valid_number_double(option) == false)
					throw OpcaoInvalida<string>(option);

				coordY = stod(option);

				if((coordY < -180) || (coordY > 180))
					throw OpcaoInvalida<double>(coordY);

				break;
			}
			catch (OpcaoInvalida<string> &op){

				cout << "Coordenada invalida(" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
			catch (OpcaoInvalida<double> &op){

				cout << "Fora de alcance (" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
		};


		for(unsigned int i = 0; i < pontosPartilha.size(); i++)
		{
			Localizacao loc = pontosPartilha.at(i)->getLocal();

			if((loc.getX() == coordX) && (loc.getY() == coordY))
			{
				newcord = false;
				cout << "Essas coordenadas ja pertencem a localizacao: " << loc.getNome() << endl << endl;
				break;
			}
		}

	}while(newcord == false);

	spot.setNome(locname);
	spot.setX(coordX);
	spot.setY(coordY);


	while(1)
	{
		try{
			cout << endl << "Capacidade [20,30]: ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if((value < 20) || (value > 30))
				throw OpcaoInvalida<string>(option);

			break;
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Capacidade invalida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	};

	addPontoPartilha(new PontoPartilha{spot,value,nome});

	for(unsigned int i = 0; i < 5; i++)
	{
		pontosPartilha.at(pontosPartilha.size() - 1)->adicionaBike(new Bicicleta{""});
	}


	cout << endl << "Novo ponto de partilha adicionado ao sistema" << endl << endl;

	return;
}

/**
 * Adiciona um utente ao sistema, pedindo ao utente que introduza os seus dados necessarios
 * para o registo (nome e localizacao).
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::addNewUtente() {

	mensagemInicial();

	cout << "Regista novo utente:" << endl << endl;

	string nome{};
	string option{};
	double coordX{}, coordY{};

	while(1)
	{
		try {
			cout << "Nome: " ;
			getline(cin,nome);
			if(valid_word(nome) == false)
				throw OpcaoInvalida<string>(nome);
			break;
		}
		catch (OpcaoInvalida<string> &op) {
			cout << "Nome invalido(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	}


	cout << endl << "Localizacao: " << endl << endl;

	cout << "Indique as coordenadas GPS:" << endl;

	while(1)
	{
		try{
			cout << endl << "Coordenada X [-90 , 90]: ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number_double(option) == false)
				throw OpcaoInvalida<string>(option);

			coordX = stod(option);

			if((coordX > 90) || (coordX < -90))
				throw OpcaoInvalida<double>(coordX);

			break;
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Coordenada invalida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
		catch (OpcaoInvalida<double> &op){

			cout << "Fora de alcance (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	};

	while(1)
	{
		try{
			cout << endl << "Coordenada Y [-180 , 180]: ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number_double(option) == false)
				throw OpcaoInvalida<string>(option);

			coordY = stod(option);

			if((coordY > 180) || (coordY < -180))
				throw OpcaoInvalida<double>(coordY);

			break;
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Coordenada invalida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
		catch (OpcaoInvalida<double> &op){

			cout << "Fora de alcance (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	};

	Localizacao spot{};

	for(unsigned int i = 0; i < pontosPartilha.size(); i++)
	{
		Localizacao loc = pontosPartilha.at(i)->getLocal();

		if((loc.getX() == coordX) && (loc.getY() == coordY))
		{
			spot.setNome(loc.getNome());
			break;
		}
	}

	spot.setX(coordX);
	spot.setY(coordY);

	Utente* u12 = new Utente{nome, spot};

	addNewUtente(u12);

	cout << endl << "Utente #" << u12->getId() << " registado com sucesso." << endl << endl;

	system("pause");
	system("cls");
	return;
}

/**
 * Pede o nome do ponto de partilha onde vai adicionar a bicicleta.
 * Cria uma bicicleta e adiciona-a ao ponto de partilha.
 * Se a capaciadade do ponto de partilha estiver no maximo e apresentada uma mensagem.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::adicionaBike() {

	cout << "Adiciona bicicleta: " << endl << endl;

	cout << "Pontos de Partilha:" << endl << endl;
	cout << setw (20) << left << "Nome" << setw (22) << "Local" << setw (13) << "GPS";
	cout << setw (10) << "Capacidade" << endl;

	for (unsigned int i=0 ; i<pontosPartilha.size() ; i++){
		cout << setw(10) << pontosPartilha.at(i)->getNome();
		cout << '(' << setw(9) << pontosPartilha.at(i)->getLocal().getX();
		cout << "," << setw(9) << pontosPartilha.at(i)->getLocal().getY() << setw(5) << ')';
		cout << pontosPartilha.at(i)->getCapacidade();
		cout << endl;
	}

	cout << endl;

	string nomePP{};
	string bikeName{""};
	int indexPP{-1};

	cin.ignore(1000,'\n');

	//Verifica ponto de partilha ao qual quer adicionar
	while(1)
	{
		try {
			cout << "Nome do Ponto de Partilha: " ;
			getline(cin,nomePP);

			if(valid_word(nomePP) == false)
				throw OpcaoInvalida<string>(nomePP);

			for(unsigned int i = 0; i < pontosPartilha.size(); i++)
			{
				if(pontosPartilha.at(i)->getNome() == nomePP)
					indexPP = i;
			}

			if(indexPP == -1)
				throw OpcaoInvalida<string>(nomePP);
			cout << endl;

			break;
		}
		catch (OpcaoInvalida<string> &op) {
			cout << "Ponto de partilha inexistente(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	}


	if(pontosPartilha.at(indexPP)->getCapacidade() == pontosPartilha.at(indexPP)->getBikes().size())
	{
		cout << "A capacidade deste ponto de partilha ja foi alcancada ! Tente adicionar a outro ponto de partilha." << endl << endl;

		return;
	}


	pontosPartilha.at(indexPP)->adicionaBike(new Bicicleta{});

	cout << endl << "Bicicleta adicionada com sucesso !" << endl << endl;

	return;
}

/**
 * Adiciona um utente ao sistema.
 * @param u1 apontador para o utente a adicionar
 */
void Sistema::addNewUtente(Utente* u1){
	utentes.push_back(u1);
}

/** Adiciona um ponto de partilha ao sistema.
 * @param p apontador para o ponto de partilha a adicionar
 */
void Sistema::addPontoPartilha(PontoPartilha* p){
	pontosPartilha.push_back(p);
}

////////////////////
// METODOS REMOVE //
////////////////////

/**
 * Pede o nome do ponto de partilha que se quer remover e remove do sistema o ponto de partilha com esse nome.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::removePonto() {

	cout << "Remove Ponto de Partilha:" << endl << endl;

	cout << "Pontos de Partilha:" << endl << endl;
	cout << setw (20) << left << "Nome" << setw (22) << "Local" << setw (13) << "GPS";
	cout << setw (10) << "Capacidade" << endl;

	for (unsigned int i=0 ; i<pontosPartilha.size() ; i++){
		cout << setw(10) << pontosPartilha.at(i)->getNome();
		cout << '(' << setw(9) << pontosPartilha.at(i)->getLocal().getX();
		cout << "," << setw(9) << pontosPartilha.at(i)->getLocal().getY() << setw(5) << ')';

		cout << pontosPartilha.at(i)->getCapacidade();

		cout << endl;
	}

	cout << endl;


	string nomePP{};
	int indexPP{-1};

	if(pontosPartilha.size() == 0)
	{
		cout << "Neste momento nao existem pontos de partilha !" << endl << endl;

		return;
	}

	cin.ignore(1000,'\n');

	//Verifica ponto de partilha que quer remover
	while(1)
	{
		try {
			cout << "Nome do Ponto de Partilha: " ;
			getline(cin,nomePP);
			if(valid_word(nomePP) == false)
				throw OpcaoInvalida<string>(nomePP);

			for(unsigned int i = 0; i < pontosPartilha.size(); i++)
			{
				if(pontosPartilha.at(i)->getNome() == nomePP)
					indexPP = i;
			}

			if(indexPP == -1)
				throw OpcaoInvalida<string>(nomePP);

			cout << endl;
			break;
		}
		catch (OpcaoInvalida<string> &op) {
			cout << "Ponto de partilha inexistente(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	}

	pontosPartilha.erase(pontosPartilha.begin() + indexPP);

	cout << "Ponto de partilha removido com sucesso !" << endl << endl;

	return;
}

/**
 * Apresenta a informacao de todos os utentes registados (nome, id e localizacao) e pede para
 * introduzir o id do utente que se pretende remover e remove-o do sistema
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::removeUtente() {

	cout << "Remove utente " << endl << endl;

	if(utentes.size() == 0)
	{
		cout << "Neste momento nao existem utentes !" << endl << endl;

		return;
	}

	displayUtentes();

	string id{};
	int idUT{};
	int indexUT{-1};

	cin.ignore(1000,'\n');

	//Verifica o nome do utente que quer remover
	while(1)
	{
		try {
			cout << "ID do Utente: " ;
			cin >> id;
			cin.ignore(1000,'\n');

			if(valid_number(id) == false)
				throw OpcaoInvalida<string>(id);

			idUT = stoi(id);

			for(unsigned int i = 0; i < utentes.size(); i++)
			{
				if(utentes.at(i)->getId() == idUT)
					indexUT = i;
			}

			if(indexUT == -1)
				throw OpcaoInvalida<int>(idUT);

			break;
		}
		catch (OpcaoInvalida<int> &op){

			cout << "ID invalido (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();

		}
		catch (OpcaoInvalida<string> &op){

			cout << "ID invalido (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	}

	utentes.erase(utentes.begin() + indexUT);

	//Caso seja o ultimo utente do sistema
	if((unsigned int)indexUT == utentes.size())
	{

		Utente::setLastId();

		cout << endl << "Utente removido com sucesso !" << endl << endl;

		return;
	}

	for(unsigned int i = indexUT; i < utentes.size(); i++)
	{
		utentes.at(i)->setIDBackward();
	}

	Utente::setLastId();

	cout << endl << "Utente removido com sucesso !" << endl << endl;

	return;
}

/**
 * Pede o nome da bicicleta que se pretende remover e remove do sistema a bicicleta com esse nome.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::removeBike() {

	cout << "Remove bicicleta " << endl << endl;

	string nomePP{};
	bool cond{false};
	int indexPP{-1};

	cin.ignore(1000,'\n');

	//Verifica se o nome da bicicleta a remover existe
	while(1)
	{
		try {
			cout << "Nome da Bicicleta: " ;
			getline(cin,nomePP);

			if(valid_bike(nomePP) == false)
				throw OpcaoInvalida<string>(nomePP);

			for(unsigned int i = 0; i < pontosPartilha.size(); i++)
			{
				for(unsigned int k = 0; k < pontosPartilha.at(i)->getBikes().size(); k++)
				{
					if(pontosPartilha.at(i)->getBikes().at(k)->getBikeName() == nomePP)
					{
						indexPP = i;
						cond = true;
					}
				}
			}

			if(cond == false)
				throw OpcaoInvalida<string>(nomePP);

			break;
		}
		catch (OpcaoInvalida<string> &op) {
			cout << "Bicicleta inexistente(" << op.opcao << ") ! Tente novamente." << endl;
			cond = false;
			cin.clear();
		}
	}

	pontosPartilha.at(indexPP)->removeBike(nomePP);

	cout << endl << "Bicicleta removida com sucesso !" << endl << endl;

	return;

}


/////////////////
// METODOS GET //
/////////////////

/**
 * Imprime no ecra toda a informacao referente ao sistema, nome da empresa, pontos de partilha
 * (incluindo nome, localizacao (coordenadas) e quantidade de bicicletas),
 * utentes (incluindo nome, id e coordenadas GPS), tabela de precos por hora e mensalidades
 * e por fim, os fundadores.
 */
void Sistema::getInfo() const {

	cout << "Informacoes:" << endl << endl;

	cout << "Nome da empresa: ECO RIDES" << endl << endl;
	cout << "Numero total de pontos de Partilha: " << pontosPartilha.size() << endl << endl;
	cout << "Pontos de Partilha:" << endl << endl;
	cout << setw (20) << left << "Nome" << setw (22) << "Local" << setw (13) << "GPS";
	cout << setw (10) << "Urbana" << setw (18) << "Urbana Simples" <<
			setw (9) << "Corrida" << setw(10) << "Infantil" << "Capacidade" << endl;

	for (unsigned int i=0 ; i<pontosPartilha.size() ; i++){
		cout << setw(10) << pontosPartilha.at(i)->getNome();
		cout << setw(23) << pontosPartilha.at(i)->getLocal().getNome();
		cout << '(' << setw(9) << pontosPartilha.at(i)->getLocal().getX();
		cout << "," << setw(9) << pontosPartilha.at(i)->getLocal().getY() << setw(5) << ')';

		cout << pontosPartilha.at(i)->getCapacidade();

		cout << endl;
	}

	cout << endl;

	cout << "Numero total de utentes registados: " << utentes.size() << endl << endl;

	displayUtentes();

	cout << endl;

	cout << "Tabela de Precos:" << endl << endl;

	cout << setw(20) << left << "Preco por hora: 4eur" << endl;

	return;
}

/**
 * Retorna o vetor de apontadores para os utentes registados no sistema.
 * @return Retorna um vetor de utentes.
 */
vector<Utente* > Sistema::getUtentes() const{
	return utentes;
}

/**
 * Retorna o vetor de apontadores para os pontos de partilha existentes no sistema.
 * @return Retorna um vetor de pontos de partilha.
 */
vector<PontoPartilha* > Sistema::getPontosPartilha() const {
	return pontosPartilha;
}

/**
 * Retorna um vector com os indices dos pontos de partilha organizados por ordem crescente
 * de distancia ao utente com indice = index.
 * @param index indice do utente
 * @return Retorna um vetor com os indices dos pontos de partilha.
 */
vector<int> Sistema::getOrderedPP(int index) const {

	//Retorna um vector com os indices dos pontos de partilha organizados por ordem crescente de distancia ao utente com indice = index
	vector<double> distancias{};
	vector<int> indices{};

	for(unsigned int i = 0; i < pontosPartilha.size(); i++)
	{
		distancias.push_back(utentes.at(index)->getLocalizacao().distancia(pontosPartilha.at(i)->getLocal()));
	}

	//Ordena o vetor por ordem crescente de distancia
	sort(distancias.begin(),distancias.end());

	for(unsigned int i = 0; i < distancias.size(); i++)
	{
		for(unsigned int k = 0; k < pontosPartilha.size(); k++)
		{
			if(distancias.at(i) == utentes.at(index)->getLocalizacao().distancia(pontosPartilha.at(k)->getLocal()))
			{
				indices.push_back(k);
			}
		}
	}
	return indices;
}

/**
 * Verifica se existe o utente com numero de identificacao igual ao parametro identificacao no sistema.
 * @param identificacao numero de identificacao de um utente
 * @return Retorna o indice do utente no vetor de utentes do sistema se este existir e -1 caso contrario.
 */
int Sistema::getUtenteIndex(int identificacao) const {

	for(unsigned int i = 0; i < utentes.size() ; i++)
	{
		if(utentes.at(i)->getId() == identificacao)
			return i;
	}

	return -1;
}


////////////
// OTHERS //
////////////

/**
 *  Ordena o vetor utentes por ordem crescente de ID
 */
bool sortById(Utente* u1, Utente* u2)
{
	if(u1->getId() < u2->getId())
		return true;

	return false;
}

/**
 * Apresenta os passos e pede ao utente que preencha os campos apresentados
 * de modo a obter a necessaria para o aluger de uma bicicleta (bicicleta,
 * numero de horas e data). Chama o metodo da classe utente alugaBicicleta e o metodo
 * classe pontoPartilha removeBike para remover a bicicleta do ponto de partilha e atribui-la
 * ao utente. O aluguer e feito no ponto de partilha mais proximo do utente.
 * Caso o utente seja Regular e apresentado o total a pagar pelo aluguer.
 * No final, chama o metodo Sistem_Manager para gerir as bicicletas.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 * @param index indice do utente no vetor de utentes do sistema
 */
void Sistema::alugaBike(int index) {
}

/**
 * Apresenta a informacao do aluger e chama-se o metodo da classe utente removeBicicleta
 * e o metodo adicionaBike da classe pontoPartilha para remover a bicicleta do utente e
 * coloca-la no ponto de partilha.
 * A devolucao e feita no ponto de partilha mais proximo do utente.
 * No final, chama a funcao Sistem_Manager para gerir as bicicletas.
 * @param index indice do utente no vetor de utentes do sistema
 */
void Sistema::devolveBike(int index) {}


/**
 * Verifica se existe excesso (<=8) ou defice (>=2) de bicicletas nos pontos de partilha,
 * caso se verifique as bicicletas sao distribuidas pelos pontos de partilha uniformemente.
 * @param index indice do ponto de partilha em que ocorreu o ultimo movimento (aluguer ou devolucao)
 */
void Sistema::system_Manager(unsigned int index, string bikeName) {

	unsigned int tamanho = pontosPartilha.at(index)->getBikes().size();
	vector<int> indicesSup5{}, indicesInf5{};

	//Guarda os indices dos pontos de partilha nos vetores indicesSup5 e indicesInf5
	for(unsigned int i = 0; i < pontosPartilha.size(); i++)
	{
		if(i != index)
		{
			if(pontosPartilha.at(i)->getBikes().size() > 5)
				indicesSup5.push_back(i);
			else if(pontosPartilha.at(i)->getBikes().size() < 5)
				indicesInf5.push_back(i);
		}

	}

	//Ordena os vectores por ordem crescente
	sort(indicesSup5.begin(), indicesSup5.end());
	sort(indicesInf5.begin(), indicesInf5.end());

	//Necessita de receber bicicletas
	if(tamanho <= 2)
	{
		//Distribui bicicletas
		for(int k = indicesSup5.size() - 1; k >= 0; k--)
		{
			while(pontosPartilha.at(indicesSup5.at(k))->getBikes().size() > 5)
			{
				if(pontosPartilha.at(index)->getBikes().size() == 5)
					break;

				Bicicleta* bike = pontosPartilha.at(indicesSup5.at(k))->getBikes().at(0);

				pontosPartilha.at(index)->adicionaBike(bike);
				pontosPartilha.at(indicesSup5.at(k))->removeBike(bike->getBikeName());
			}

			if(pontosPartilha.at(index)->getBikes().size() == 5)
				break;
		}
	}
	else if(tamanho >= 8)	//Necessita de fornecer bicicletas
	{
		//Distribui bicicletas
		for(unsigned int k = 0; k < indicesInf5.size(); k++)
		{
			while(pontosPartilha.at(indicesInf5.at(k))->getBikes().size() < 5)
			{
				if(pontosPartilha.at(index)->getBikes().size() == 5)
					break;

				Bicicleta* bike = pontosPartilha.at(index)->getBikes().at(0);

				pontosPartilha.at(indicesInf5.at(k))->adicionaBike(bike);
				pontosPartilha.at(index)->removeBike(bike->getBikeName());
			}

			if(pontosPartilha.at(index)->getBikes().size() == 5)
				break;
		}
	}

	return;
}

/**
 * Imprime por ordem crescente de distancia do utente, os pontos de partilha (nome e nome da localizacao).
 * @param index indice do utente no vetor de utentes do sistema
 */
void Sistema::displayNearestPP(int index) const {


}

/**
 * Imprime no ecra a informacao dos utentes (nome, id e coordenadas da localizacao).
 */
void Sistema::displayUtentes() const {

	cout << left << setw(15) << "   Nome" << setw(6) << " ID" << setw (40) << " GPS" << endl;

	for (unsigned int i=0 ; i	< utentes.size() ; i++)
	{
		cout << "-> " << setw(13) << utentes.at(i)->getNome();
		cout << setw(10) << utentes.at(i)->getId();
		cout << '(' << setw(9) << utentes.at(i)->getLocalizacao().getX();
		cout << "," << setw(9) << utentes.at(i)->getLocalizacao().getY() << setw(5) << ')' << endl;
	}

	cout << endl;

}

