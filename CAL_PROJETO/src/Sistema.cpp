#include "Sistema.h"

/////////////////
// METODOS ADD //
/////////////////

/**
 * Apresenta os passos necessarios para criacao de um novo ponto de partilha, pedindo para introduzir
 * o nome, a localizacao e a capacidade, por fim, adiciona-o ao sistema.
 * Adiciona 5 bicicletas de cada tipo no ponto de partilha criado.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::addPontoPartilha() {

	cout << "Adiciona Ponto de Partilha:" << endl << endl;

	string nome,locname;
	int value {};
	string option {};
	bool cond {false};

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
				cout << "Já existe esse nome (" << op.opcao << ") ! Tente novamente." << endl;
			else
				cout << "Nome inválido (" << op.opcao << ") ! Tente novamente." << endl;
			cond = false;
			cin.clear();
		}
	}

	Localizacao spot{};
	bool diffloc {true};

	cout << endl << "Localização: " << endl << endl;

	while(1)
	{
		try {
			cout << "Nome da Localização: " ;
			getline(cin , locname);
			if(valid_word(locname) == false)
				throw OpcaoInvalida<string>(nome);

			for(unsigned int i = 0; i < pontosPartilha.size(); i++)
			{
				Localizacao loc = pontosPartilha.at(i)->getLocal();

				if(loc.getNome() == locname){
					diffloc = false;

					spot.setNome(locname);
					spot.setX(loc.getX());
					spot.setY(loc.getY());

					cout << endl << "Coordenada X: " << spot.getX() << endl << endl;
					cout << "Coordenada Y: " << spot.getY() << endl << endl;
					break;
				}
			}
			break;
		}
		catch (OpcaoInvalida<string> &op) {
			cout << "Nome inválido (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	}

	if(diffloc == true)
	{
		bool newcord{true};
		double coordX { }, coordY { };

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

					cout << "Coordenada inválida (" << op.opcao << ") ! Tente novamente." << endl;
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

					cout << "Coordenada inválida(" << op.opcao << ") ! Tente novamente." << endl;
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
					cout << "Essas coordenadas já pertencem à localização: " << loc.getNome() << endl << endl;
					break;
				}
			}

		}while(newcord == false);

		spot.setNome(locname);
		spot.setX(coordX);
		spot.setY(coordY);
	}

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

			cout << "Capacidade inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	};

	addPontoPartilha(new PontoPartilha(spot,value,nome));

	for(unsigned int i = 0; i < 5; i++)
	{
		string u = "u" + to_string(Urbana::getID());
		string us = "us" + to_string(UrbanaSimples::getID());
		string c = "c" + to_string(Corrida::getID());
		string inf = "i" + to_string(Infantil::getID());

		pontosPartilha.at(pontosPartilha.size() - 1)->adicionaBike(new Urbana(u));
		pontosPartilha.at(pontosPartilha.size() - 1)->adicionaBike(new UrbanaSimples(us));
		pontosPartilha.at(pontosPartilha.size() - 1)->adicionaBike(new Corrida(c));
		pontosPartilha.at(pontosPartilha.size() - 1)->adicionaBike(new Infantil(inf));
	}

	cout << endl << "Novo ponto de partilha adicionado ao sistema" << endl << endl;

	return;
}

/**
 * Adiciona um utente ao sistema, pedindo ao utente que introduza os seus dados necessarios
 * para o registo (nome, tipo de utente e localizacao).
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::addNewUtente() {

	mensagemInicial();

	cout << "Regista novo utente:" << endl << endl;

	string nome, tipoUtente;
	int value {};
	string option {};
	double coordX { }, coordY { };

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
			cout << "Nome inválido(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	}
	cout << endl << "Tipo de Utente :"<< endl ;
	cout << "     1 - Regular" << endl;
	cout << "     2 - Sócio" << endl << endl;

	while(1)
	{
		try{
			cout << endl << "Introduza uma opção (1-2): ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);
			if(value < 1 || value > 2)
				throw OpcaoInvalida<int>(value);

			break;
		}
		catch (OpcaoInvalida<int> &op){

			cout << "Opção inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Opção inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	};

	if(value==1)
		tipoUtente = "Regular";
	else
		tipoUtente = "Socio";

	cout << endl << "Localização: " << endl << endl;

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

			cout << "Coordenada inválida(" << op.opcao << ") ! Tente novamente." << endl;
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

			cout << "Coordenada inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
		catch (OpcaoInvalida<double> &op){

			cout << "Fora de alcance (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	};

	Localizacao spot;

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

	Utente* u12;

	if(tipoUtente == "Socio")
		u12 = new Socio(nome, spot);
	else
		u12 = new Regular(nome, spot);

	addNewUtente(u12);

	cout << endl << "Utente #" << u12->getId() << " registado com sucesso." << endl << endl;

	system("pause");
	system("cls");
	return;
}

/**
 * Apresenta os passos necessarios para a criacao de uma nova loja, pedindo para escolher uma
 * localizacao entre as disponiveis, a capacidade e, por fim, adiciona-a ao sistema.
 * Adiciona bicicletas incrementando o stock de cada tipo ate atingir a capacidade.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::addStore() {

	cout << "Adiciona Loja:" << endl;

	string locname;
	int value {};
	string option {};
	vector<Localizacao> locations;
	Localizacao* spot = new Localizacao { };
	unsigned int capacidade {};
	vector<unsigned int> stock(4);

	cin.ignore(1000,'\n');

	cout << endl << "Localização: " << endl << endl;

	//Verifica quais as localizacoes disponiveis para uma loja
	for(unsigned int i = 0; i < pontosPartilha.size(); i++)
	{
		priority_queue<Loja> tmp = stores;
		bool exist {false};

		while(!tmp.empty())
		{
			if((tmp.top().getLocal()->getX() == pontosPartilha.at(i)->getLocal().getX()) &&
					(tmp.top().getLocal()->getY() == pontosPartilha.at(i)->getLocal().getY()))
			{
				exist = true;
			}

			tmp.pop();
		}

		if(exist == false)
			locations.push_back(pontosPartilha.at(i)->getLocal());

	}

	//Faz display das localizacoes disponiveis para uma loja
	cout << "Localizações disponiveis: " << endl;
	for(unsigned int i = 0; i < locations.size(); i++)
		cout << i+1 << " - " << locations.at(i).getNome() << endl;

	//Verifica qual a localizacao da loja
	while(1)
	{
		try {

			cout << endl << "Introduza uma opção (1-" << locations.size() << "): ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value < 1 || value > (int)(locations.size()))
				throw OpcaoInvalida<int>(value);

			break;
		}
		catch (OpcaoInvalida<int> &op){

			cout << "Opção inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Opção inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};

	//Adiciona a nova localização da loja
	spot->setNome(locations.at(value - 1).getNome());
	spot->setX(locations.at(value - 1).getX());
	spot->setY(locations.at(value - 1).getY());

	//Verifica a capacidade total da loja
	while(1)
	{
		try{
			cout << endl << "Capacidade [20,30]: ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			capacidade = stoi(option);

			if((capacidade < 20) || (capacidade > 30))
				throw OpcaoInvalida<string>(option);

			break;
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Capacidade inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	};

	value = capacidade;
	int tmp_index {0};

	while(value != 0)
	{
		stock.at(tmp_index)++;

		if(tmp_index == 3)
			tmp_index = 0;
		else
			tmp_index++;

		value--;
	}

	Loja store(spot,capacidade,stock);
	stores.push(store);

	cout << endl << "Nova loja adicionada em " << spot->getNome() << " com sucesso !" << endl << endl;
}

/**
 * Pede o nome do ponto de partilha onde vai adicionar a bicicleta e o tipo de bicicleta que
 * pretende adicionar. Cria uma bicicleta do tipo pedido e adiciona-a ao ponto de partilha.
 * Se a capaciadade do ponto de partilha estiver no maximo e apresentada uma mensagem.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::adicionaBike() {

	cout << "Adiciona bicicleta: " << endl << endl;

	cout << "Pontos de Partilha:" << endl << endl;
	cout << setw (20) << left << "Nome" << setw (22) << "Local" << setw (13) << "GPS";
	cout << setw (10) << "Urbana" << setw (18) << "Urbana Simples" <<
			setw (9) << "Corrida" << setw(10) << "Infantil" << "Capacidade" << endl;

	for (unsigned int i=0 ; i<pontosPartilha.size() ; i++){
		cout << setw(10) << pontosPartilha.at(i)->getNome();
		cout << setw(23) << pontosPartilha.at(i)->getLocal().getNome();
		cout << '(' << setw(9) << pontosPartilha.at(i)->getLocal().getX();
		cout << "," << setw(9) << pontosPartilha.at(i)->getLocal().getY() << setw(5) << ')';

		vector<int> numtypes = pontosPartilha.at(i)->getNumberOfBikes();

		cout << setw(13) << numtypes.at(0);
		cout << setw(15) << numtypes.at(1);
		cout << setw(9) << numtypes.at(2);
		cout << setw(11) << numtypes.at(3);
		cout << pontosPartilha.at(i)->getCapacidade();

		cout << endl;
	}

	cout << endl;

	string biketype;
	string nomePP;
	string bikeName = "";
	int indexPP {-1};
	int numberbikes {0};

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

	for(unsigned int i = 0; i < pontosPartilha.at(indexPP)->getBikes().size(); i++)
	{
		numberbikes += pontosPartilha.at(indexPP)->getBikes().at(i).size();
	}

	if(pontosPartilha.at(indexPP)->getCapacidade() == numberbikes)
	{
		cout << "A capacidade deste ponto de partilha já foi alcançada ! Tente adicionar a outro ponto de partilha." << endl << endl;

		return;
	}


	//Verifica tipo de bicicleta a adicionar
	while(1)
	{
		try {
			cout << "Tipo de Bicicleta: " ;
			getline(cin,biketype);
			if(valid_word(biketype) == false)
				throw OpcaoInvalida<string>(biketype);

			if(biketype == "Urbana")
				bikeName = "u" + to_string(Urbana::getID());
			else if(biketype == "Urbana Simples")
				bikeName = "us" + to_string(UrbanaSimples::getID());
			else if(biketype == "Corrida")
				bikeName = "c" + to_string(Corrida::getID());
			else if(biketype == "Infantil")
				bikeName = "i" + to_string(Infantil::getID());

			if(bikeName == "")
				throw OpcaoInvalida<string>(biketype);

			break;
		}
		catch (OpcaoInvalida<string> &op) {
			cout << "Tipo inválido(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	}

	Bicicleta* bc;

	if(biketype == "Urbana")
		bc = new Urbana(bikeName);
	else if(biketype == "Urbana Simples")
		bc = new UrbanaSimples(bikeName);
	else if(biketype == "Corrida")
		bc = new Corrida(bikeName);
	else
		bc = new Infantil(bikeName);


	pontosPartilha.at(indexPP)->adicionaBike(bc);

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

/**
 * Adiciona um ponto de partilha ao sistema.
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
	cout << setw (10) << "Urbana" << setw (18) << "Urbana Simples" <<
			setw (9) << "Corrida" << setw(10) << "Infantil" << "Capacidade" << endl;

	for (unsigned int i=0 ; i<pontosPartilha.size() ; i++){
		cout << setw(10) << pontosPartilha.at(i)->getNome();
		cout << setw(23) << pontosPartilha.at(i)->getLocal().getNome();
		cout << '(' << setw(9) << pontosPartilha.at(i)->getLocal().getX();
		cout << "," << setw(9) << pontosPartilha.at(i)->getLocal().getY() << setw(5) << ')';

		vector<int> numtypes = pontosPartilha.at(i)->getNumberOfBikes();

		cout << setw(13) << numtypes.at(0);
		cout << setw(15) << numtypes.at(1);
		cout << setw(9) << numtypes.at(2);
		cout << setw(11) << numtypes.at(3);
		cout << pontosPartilha.at(i)->getCapacidade();

		cout << endl;
	}

	cout << endl;


	string nomePP;
	int indexPP {-1};

	if(pontosPartilha.size() == 0)
	{
		cout << "Neste momento não existem pontos de partilha !" << endl << endl;

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
 * Apresenta a informacao de todos os utentes registados (nome, id, tipo e localizacao) e pede para
 * introduzir o id do utente que se pretende remover e remove-o do sistema
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::removeUtente() {

	cout << "Remove utente " << endl << endl;

	if(utentes.size() == 0)
	{
		cout << "Neste momento não existem utentes !" << endl << endl;

		return;
	}

	displayUtentes();

	string id;
	int idUT {};
	int indexUT {-1};

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

			cout << "ID inválido (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();

		}
		catch (OpcaoInvalida<string> &op){

			cout << "ID inválido (" << op.opcao << ") ! Tente novamente." << endl;
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
 * Pede o tipo e o nome da bicicleta que se pretende remover e remove do sistema a bicicleta com esse nome.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::removeBike() {

	cout << "Remove bicicleta " << endl << endl;

	cout << "Tipos de bicicleta:" << endl << endl;

	cout <<  "-> Urbana   [Name: u(number)]" << endl;
	cout <<  "-> Urbana Simples [Name: us(number)]" << endl;
	cout <<  "-> Corrida  [Name: c(number)]" << endl;
	cout <<  "-> Infantil [Name: i(number)]" << endl << endl;

	string nomePP, biketype;
	bool cond {false};
	int indexPP {-1};
	int indexBB {-1};

	cin.ignore(1000,'\n');

	//Verifica tipo de bicicleta a remover
	while(1)
	{
		try {
			cout << "Tipo de Bicicleta: " ;
			getline(cin,biketype);
			if(valid_word(biketype) == false)
				throw OpcaoInvalida<string>(biketype);

			if(biketype == "Urbana")
				indexBB = 0;
			else if(biketype == "Urbana Simples")
				indexBB = 1;
			else if(biketype == "Corrida")
				indexBB = 2;
			else if(biketype == "Infantil")
				indexBB = 3;

			if(indexBB == -1)
				throw OpcaoInvalida<string>(biketype);

			break;
		}
		catch (OpcaoInvalida<string> &op) {
			cout << "Tipo inválido(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	}

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
				for(unsigned int k = 0; k < pontosPartilha.at(i)->getBikes().at(indexBB).size(); k++)
				{
					if(pontosPartilha.at(i)->getBikes().at(indexBB).at(k)->getBikeName() == nomePP)
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

/**
 * Pede ao utilizador que escolha a loja que pretende remover da lista apresentada e remove-a
 * do sistema.
 * Para cada introducao do utilizador e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::removeStore() {

	cout << "Remove Loja:" << endl << endl;

	if(stores.empty())
	{
		cout << "Neste momento não existem lojas para serem removidas !" << endl << endl;
		return;
	}

	cout << "Lojas disponiveis:" << endl;

	priority_queue<Loja> tmp = stores;
	int tmp_index {1};
	string option,locname;
	int value {};

	//Verifica as lojas disponveis para remocao
	while(!tmp.empty())
	{
		cout << tmp_index << " - Loja em " << tmp.top().getLocal()->getNome() << endl;
		tmp_index++;
		tmp.pop();
	}

	//Verifica qual a loja a ser removida
	while(1)
	{
		try {
			cout << endl << "Introduza uma opção (1-" << (tmp_index - 1) << "): ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value < 1 || value > (tmp_index - 1))
				throw OpcaoInvalida<int>(value);

			break;
		}
		catch (OpcaoInvalida<int> &op){

			cout << "Opção inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Opção inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};

	tmp_index = 1;

	//Remove loja
	while(!stores.empty())
	{
		if(tmp_index != value)
			tmp.push(stores.top());
		else
			locname = stores.top().getLocal()->getNome();

		tmp_index++;
		stores.pop();
	}

	stores = tmp;
	cout << endl << "Loja em " << locname << " removida com sucesso !" << endl << endl;

}

/**
 * Remove as bicicletas ja reparadas da oficina e coloca-as no ponto de partilha com
 * menos bicicletas do seu tipo.
 */
void Sistema::removeFromRepairShop() {

	vector<Bicicleta *> brokenBikes = repairShop.getBrokenBikes();

	for(unsigned int i = 0; i < brokenBikes.size(); i++)
	{
		//Verifica se a bicicleta esta composta
		if(brokenBikes.at(i)->getAvarias().empty())
		{
			int position {0}, indicator{}, min{99};
			string name= brokenBikes.at(i)->getBikeName();
			Bicicleta* bike{ };

			if(name.at(0) == 'c')
			{
				position = 2;
				bike = new Corrida { name };
			}
			else if(name.at(0) == 'i')
			{
				position = 3;
				bike = new Infantil { name };
			}
			else if(name.at(1) == 's')
			{
				position = 1;
				bike = new UrbanaSimples { name };
			}
			else
				bike = new Urbana { name };

			for(unsigned int j = 0; j < pontosPartilha.size(); j++)
			{
				if(pontosPartilha.at(j)->getNumberOfBikes().at(position) < min)
				{
					min = pontosPartilha.at(j)->getNumberOfBikes().at(position);
					indicator = j;
				}
			}

			//Adiciona a bicicleta ao ponto de partilha que possui menor quantidade de bicicletas do seu tipo
			pontosPartilha.at(indicator)->adicionaBike(bike);
			brokenBikes.erase(brokenBikes.begin() + i);
			i--;
		}
	}

	//Atualiza o vetor de bicicletas avariadas
	repairShop.setBrokenBikes(brokenBikes);
}

/**
 * Pede ao utilizador para escolher a bicicleta da lista apresentada.
 * Essa lista contem as bicicletas que ja foram abatidas. O utilizador escolhe e a bicicleta
 * e removida da sucata.
 * Para cada introducao do utilizador e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 */
void Sistema::removeFromJunkyard(){

	tabHAbates::const_iterator it = junkyard.begin();
	string option, bikeName;
	int indicator {1}, value {};
	vector<Bicicleta> bikeNamesAcess;
	bool exist {false};

	if(it == junkyard.end())
	{
		cout << "Neste momento não existem bicicletas que já tenham sido abatidas" << endl << endl;
		return;
	}

	for(it = junkyard.begin(); it != junkyard.end(); it++)
	{
		if(it->getAbate().getAno() != 0){
			exist = true;
			break;
		}
	}

	if(exist == false)
	{
		cout << "Neste momento não existem bicicletas que já tenham sido abatidas" << endl << endl;
		return;
	}

	cout << "Remover bicicleta abatida" << endl << endl;
	cout << "Bicicletas disponiveis para remoção:" << endl;

	for(it = junkyard.begin(); it != junkyard.end(); it++)
	{
		if(it->getAbate().getAno() != 0)
		{
			cout << left << setw(2) << indicator << " -> " << it->getBikeName() << endl;
			bikeNamesAcess.push_back(*it);
			indicator++;
		}

	}

	//Seleciona uma das bicicletas
	while(1)
	{
		try {
			cout << endl << "Bicicleta (1-" << (indicator - 1) << "): ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value < 1 || value > (indicator - 1))
				throw OpcaoInvalida<int>(value);

			bikeName = bikeNamesAcess.at(value - 1).getBikeName();
			break;
		}
		catch (OpcaoInvalida<int> &op){
			cout << "Bicicleta inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		catch (OpcaoInvalida<string> &op){
			cout << "Bicicleta inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};

	for(it = junkyard.begin(); it != junkyard.end(); it++)
	{
		if(it->getBikeName() == bikeName) {
			junkyard.erase(it);
			break;
		}
	}

	cout << endl << "Bicicleta " << bikeName << " removida com sucesso !" << endl << endl;
}

/////////////////
// METODOS GET //
/////////////////

/**
 * Imprime no ecra toda a informacao referente ao sistema, nome da empresa, pontos de partilha
 * (incluindo nome, localizacao (nome e coordenadas) e quantidades de cada tipo de bicicletas),
 * utentes (incluindo nome, id, tipo e coordenadas GPS), tabela de precos por hora e mensalidades
 * e por fim, os fundadores.
 */
void Sistema::getInfo() const {

	cout << "Informações:" << endl << endl;

	cout << "Nome da empresa: ECO RIDES" << endl << endl;
	cout << "Número total de pontos de Partilha: " << pontosPartilha.size() << endl << endl;
	cout << "Pontos de Partilha:" << endl << endl;
	cout << setw (20) << left << "Nome" << setw (22) << "Local" << setw (13) << "GPS";
	cout << setw (10) << "Urbana" << setw (18) << "Urbana Simples" <<
			setw (9) << "Corrida" << setw(10) << "Infantil" << "Capacidade" << endl;

	for (unsigned int i=0 ; i<pontosPartilha.size() ; i++){
		cout << setw(10) << pontosPartilha.at(i)->getNome();
		cout << setw(23) << pontosPartilha.at(i)->getLocal().getNome();
		cout << '(' << setw(9) << pontosPartilha.at(i)->getLocal().getX();
		cout << "," << setw(9) << pontosPartilha.at(i)->getLocal().getY() << setw(5) << ')';

		vector<int> numtypes = pontosPartilha.at(i)->getNumberOfBikes();

		cout << setw(13) << numtypes.at(0);
		cout << setw(15) << numtypes.at(1);
		cout << setw(9) << numtypes.at(2);
		cout << setw(11) << numtypes.at(3);
		cout << pontosPartilha.at(i)->getCapacidade();

		cout << endl;
	}

	cout << endl;

	cout << "Número total de utentes registados: " << utentes.size() << endl << endl;

	displayUtentes();

	cout << endl;

	cout << "Tabela de Preços:" << endl << endl;

	cout << setw(20) << left << "Tipo de bicicleta" << "Preço por hora" << endl;
	cout << setw(26) << "Urbana" << "4€" << endl <<
			setw(26) << "Urbana Simples" << "3€" << endl <<
			setw(26) << "Corrida" << "5€" << endl <<
			setw(26) << "Infantil" << "2€" << endl << endl;

	cout << setw(18) << left << "Mensalidade" << "Acessos" << endl;
	cout << setw(4) << " " << setw(11) << "20€" << "Infantil" << endl;
	cout << setw(4) << " " << setw(11) << "30€" << "Infantil + Urbana Simples" << endl;
	cout << setw(4) << " " << setw(11) << "40€" << "Infantil + Urbana Simples + Urbana" << endl;
	cout << setw(4) << " " << setw(11) << "50€" << "Infantil + Urbana Simples + Urbana + Corrida" << endl << endl;

	cout << "Fundadores: " << endl;
	cout << "  - Rui Guedes" << endl;
	cout << "  - César Pinho" << endl;
	cout << "  - Bernardo Santos" << endl << endl;

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
 * @return Retorna uma referencia da oficina.
 */
Oficina& Sistema::getOficina() {
	return repairShop;
}

/**
 * @return Retorna a fila de prioridade das lojas.
 */
priority_queue<Loja> Sistema::getStores() const {
	return stores;
};

/**
 * @return Retorna a tabela de dispersao com as bicicletas que estao para abate.
 */
tabHAbates Sistema::getJunkyard() const {
	return junkyard;
};

/**
 * Retorna um vector com os indices dos pontos de partilha organizados por ordem crescente
 * de distancia ao utente com indice = index.
 * @param index indice do utente
 * @return Retorna um vetor com os indices dos pontos de partilha.
 */
vector<int> Sistema::getOrderedPP(int index) const {

	//Retorna um vector com os indices dos pontos de partilha organizados por ordem crescente de distancia ao utente com indice = index
	vector<double> distancias;
	vector<int> indices;

	for(unsigned int i = 0; i < pontosPartilha.size(); i++)
	{
		distancias.push_back(utentes.at(index)->getLocalizacao().distancia(pontosPartilha.at(i)->getLocal()));
	}

	//Ordena o vetor por ordem crescente de distância
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

/**
 * @return Retorna a data da ultima utilizacao do sistema.
 */
Data Sistema::getDataAtual() const {
	return dataAtual;
}

/////////////////
// METODOS SET //
/////////////////

/**
 * Altera a data da ultima utilizacao do sistema.
 * @param newData nova data
 */
void Sistema::setDataAtual(Data newData) {
	dataAtual = newData;
}

/**
 * Altera a fila de prioridade das lojas.
 * @param newStores nova fila de lojas
 */
void Sistema::setStores(priority_queue<Loja> newStores) {
	stores = newStores;
}

/**
 * Altera a oficina
 * @param newRShop nova oficina
 */
void Sistema::setOficina(Oficina newRShop) {
	repairShop = newRShop;
}

/**
 * Altera a tabela de dispersao com as bicicletas que estao para abate.
 * @param newJunkyard nova tabela de bicicletas
 */
void Sistema::setJunkyard(tabHAbates newJunkyard){
	junkyard = newJunkyard;
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
 * de modo a obter a informacao necessaria para o aluguer de uma bicicleta (tipo de bicicleta,
 * numero de horas e data). Chama o metodo da classe Utente alugaBicicleta e o metodo da
 * classe PontoPartilha removeBike para remover a bicicleta do ponto de partilha e atribui-la
 * ao utente. O aluguer e feito no ponto de partilha mais proximo do utente.
 * Caso o utente seja Regular e apresentado o total a pagar pelo aluguer.
 * No final, chama o metodo System_Manager para gerir as bicicletas.
 * Para cada introducao do utente e verificado se o mesmo introduziu os dados no formato pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 * @param index indice do utente no vetor de utentes do sistema
 */
void Sistema::alugaBike(int index) {

	vector<int> distancias = getOrderedPP(index);

	if(utentes.at(index)->getAvailable() == false)
	{
		cout << "Não é possível alugar duas bicicletas em simultâneo !"  << endl << endl;

		return;
	}
	else
	{
		cout << "Aluga Bicicleta: " << endl << endl;

		cout << "Preencha os seguintes campos: " << endl << endl;
		string bikeType;
		Data d1;
		int numHours{};
		int value {};
		string option {};

		cout << "Tipos de bicicleta: " << endl;
		cout << "     1 - Urbana" << endl;
		cout << "     2 - Urbana Simples" << endl;
		cout << "     3 - Corrida" << endl;
		cout << "     4 - Infantil" << endl << endl;

		//Executa até obter um tipo de bicicleta válido
		while(1)
		{
			try{
				cout << endl << "Introduza uma opção [1-4]: ";
				cin >> option;
				cin.ignore(1000,'\n');
				if(valid_number(option) == false)
					throw OpcaoInvalida<string>(option);

				value = stoi(option);
				if(value < 1 || value > 4)
					throw OpcaoInvalida<int>(value);

				break;
			}
			catch (OpcaoInvalida<int> &op){

				cout << "Opção inválida (" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
			catch (OpcaoInvalida<string> &op){

				cout << "Opção inválida (" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
		};

		//Verifica o tipo de bicicleta selecionada
		if(value == 1)
			bikeType = "Urbana";
		else if(value == 2)
			bikeType = "Urbana Simples";
		else if(value == 3)
			bikeType = "Corrida";
		else
			bikeType = "Infantil";

		//Executa até obter um número de horas válido
		while(1)
		{
			try{
				cout << endl << "Número de horas [1-24]: ";
				cin >> option;
				cin.ignore(1000,'\n');
				if(valid_number(option) == false)
					throw OpcaoInvalida<string>(option);

				value = stoi(option);
				if(value < 1 || value > 24)
					throw OpcaoInvalida<int>(value);

				numHours = value;
				break;
			}
			catch (OpcaoInvalida<int> &op){

				cout << "Número de horas inválido (" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
			catch (OpcaoInvalida<string> &op){

				cout << "Número de horas inválido (" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
		};

		cout << endl << "Última utilização: " << dataAtual.getDia() << "/" << dataAtual.getMes() << "/" << dataAtual.getAno() << endl;

		//Executa até obter um ano válido
		while(1)
		{
			try{
				cout << endl << "Ano [" << dataAtual.getAno() << " ->]: ";
				cin >> option;
				cin.ignore(1000,'\n');
				if(valid_number(option) == false)
					throw OpcaoInvalida<string>(option);

				value = stoi(option);
				if(value < (int)dataAtual.getAno())
					throw OpcaoInvalida<int>(value);

				d1.setAno(value);
				break;
			}
			catch (OpcaoInvalida<int> &op){

				cout << "Ano inválido (" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
			catch (OpcaoInvalida<string> &op){

				cout << "Ano inválido (" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
		};

		//Executa até obter um mês válido
		while(1)
		{
			try{
				if(dataAtual.getAno() < d1.getAno())
					cout << endl << "Mês [1-12]: ";
				else
					cout << endl << "Mês [" << dataAtual.getMes() << "-12]: ";
				cin >> option;
				cin.ignore(1000,'\n');
				if(valid_number(option) == false)
					throw OpcaoInvalida<string>(option);

				value = stoi(option);

				if(dataAtual.getAno() < d1.getAno())
				{
					if(value < 1 || value > 12)
						throw OpcaoInvalida<int>(value);
				}
				else
				{
					if(value < (int)dataAtual.getMes() || value > 12)
						throw OpcaoInvalida<int>(value);
				}

				d1.setMes(value);
				break;
			}
			catch (OpcaoInvalida<int> &op){

				cout << "Mês inválido (" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
			catch (OpcaoInvalida<string> &op){

				cout << "Mês inválido (" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
		};

		/* Executa até obter um dia válido
		 * Considera que fevereiro tem 28 dias
		 */
		while(1)
		{
			try{
				cout << endl << "Dia: ";
				cin >> option;
				cin.ignore(1000,'\n');
				if(valid_number(option) == false)
					throw OpcaoInvalida<string>(option);

				value = stoi(option);

				if((d1.getMes() == dataAtual.getMes()) && (d1.getAno() == dataAtual.getAno()))
				{
					if(d1.getMes() == 2)
					{
						if(value < (int)dataAtual.getDia() || value > 28)
							throw OpcaoInvalida<int>(value);

						d1.setDia(value);
						break;
					}
					else if((d1.getMes() == 1) ||(d1.getMes() == 3) ||(d1.getMes() == 5) ||
							(d1.getMes() == 7) ||(d1.getMes() == 8) ||(d1.getMes() == 10) ||(d1.getMes() == 12))
					{
						if(value < (int)dataAtual.getDia() || value > 31)
							throw OpcaoInvalida<int>(value);

						d1.setDia(value);
						break;
					}
					else
					{
						if(value < (int)dataAtual.getDia() || value > 30)
							throw OpcaoInvalida<int>(value);

						d1.setDia(value);
						break;
					}
				}
				else
				{
					if(d1.getMes() == 2)
					{
						if(value < 1 || value > 28)
							throw OpcaoInvalida<int>(value);

						d1.setDia(value);
						break;
					}
					else if((d1.getMes() == 1) ||(d1.getMes() == 3) ||(d1.getMes() == 5) ||
							(d1.getMes() == 7) ||(d1.getMes() == 8) ||(d1.getMes() == 10) ||(d1.getMes() == 12))
					{
						if(value < 1 || value > 31)
							throw OpcaoInvalida<int>(value);

						d1.setDia(value);
						break;
					}
					else
					{
						if(value < 1 || value > 30)
							throw OpcaoInvalida<int>(value);

						d1.setDia(value);
						break;
					}
				}

			}
			catch (OpcaoInvalida<int> &op){

				cout << "Dia inválido (" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
			catch (OpcaoInvalida<string> &op){

				cout << "Dia inválido (" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
		};

		//Atualiza a data se necessária
		updateData(d1);

		int idPP {};
		vector<string> bikesType;

		//Verifica se tem o tipo de bicicleta pretendida por ordem de distância
		for (unsigned int i=0 ; i < distancias.size(); i++)
		{
			bikesType = pontosPartilha.at(distancias.at(i))->getBikeTypes();

			idPP = SequentialSearch(bikesType,bikeType);

			if(idPP != -1){
				idPP = distancias.at(i);
				break;
			}
		}

		if(idPP == -1)
		{
			cout << endl << "Neste momento não existe nenhuma bicicleta do tipo " << bikeType << " disponível." << endl << endl;
		}
		else
		{
			Utilizacao p(bikeType, numHours, d1,pontosPartilha.at(idPP)->getNome(),pontosPartilha.at(idPP)->getLocal().getNome());
			double price {0};

			Bicicleta* bike {};

			if(bikeType == "Urbana")
				bike = pontosPartilha.at(idPP)->getBikes().at(0).at(0);
			else if(bikeType == "Urbana Simples")
				bike = pontosPartilha.at(idPP)->getBikes().at(1).at(0);
			else if(bikeType == "Corrida")
				bike = pontosPartilha.at(idPP)->getBikes().at(2).at(0);
			else
				bike = pontosPartilha.at(idPP)->getBikes().at(3).at(0);

			utentes.at(index)->alugaBicicleta(bike,p);

			pontosPartilha.at(idPP)->removeBike(bike->getBikeName());

			if(utentes.at(index)->getTipoUtente() == "Regular")
			{
				price = p.getPrice();
			}

			cout << endl;
			system("cls");

			mensagemInicial();

			cout << "Aluga Bicicleta: " << endl << endl;
			cout << "Resumo do aluguer: " << endl << endl;

			p.displayUtilizacao();

			if(price !=0)
				cout << "Montante: " << price << "€" << endl;

			system_Manager(idPP,bikeType);

			cout << endl << "Bicicleta alugada com sucesso !" << endl << endl;
		}

		return;
	}
}

/**
 * Apresenta a informacao do aluguer e chama o metodo da classe Utente removeBicicleta
 * e o metodo adicionaBike da classe PontoPartilha para remover a bicicleta do utente e
 * coloca-la no ponto de partilha.
 * A devolucao e feita no ponto de partilha mais proximo, nao lotado, do utente.
 * E chamada a funcao generateBikeStatus que decide se a bicicleta fica no ponto de partilha,
 * ou se e enviada para a oficina ou para a sucata.
 * No final, se a bicicleta ficar no ponto de partilha, chama a funcao System_Manager para gerir
 * as bicicletas.
 * @param index indice do utente no vetor de utentes do sistema
 */
void Sistema::devolveBike(int index) {

	if(utentes.at(index)->getAvailable() == true) {
		cout << "Neste momento o utente não tem nenhuma bicicleta para entregar" << endl << endl;
		return;
	}

	int index_pp {-1};
	vector<int> index_distancias = getOrderedPP(index);
	Bicicleta* bike {};

	bike = utentes.at(index)->removeBicicleta();

	cout << "Devolve bicicleta: " << endl << endl;
	cout << "Resumo do último aluguer: " << endl << endl;

	string bikeType;

	//Verifica o tipo de utente e apresenta a respetiva informação
	Utilizacao ut = utentes.at(index)->getLastUse();
	bikeType = ut.getBikeType();
	ut.displayUtilizacao();

	if(utentes.at(index)->getTipoUtente() == "Regular") {
		cout << "Montante: " << ut.getPrice() << "€" << endl;
	}


	if(generateBikeStatus(bike) == true) {
		for(unsigned int i = 0; i < index_distancias.size(); i++) {
			int lotacao {0};

			for(unsigned int k = 0; k < pontosPartilha.at(index_distancias.at(i))->getNumberOfBikes().size(); k++)
			{
				lotacao += pontosPartilha.at(index_distancias.at(i))->getNumberOfBikes().at(k);
			}

			if(pontosPartilha.at(index_distancias.at(i))->getCapacidade() > lotacao) {
				index_pp = index_distancias.at(i);
				pontosPartilha.at(index_distancias.at(i))->adicionaBike(bike);
				break;
			}
		}

		cout << endl << "Bicicleta devolvida com sucesso no ponto de partilha ECO_RIDES_" << pontosPartilha.at(index_pp)->getNome() << " !" << endl << endl;

		system_Manager(index_pp,bikeType);
	}
}

/**
 * Apresenta os passos e pede ao utente que preencha os campos apresentados
 * de modo a obter a informacao necessaria para a compra de bicicletas (tipo de bicicleta,
 * quantidade e data). A compra e feita na loja mais proxima do utente, com stock suficiente.
 * Chama o metodo checkStock da classe Loja para reabastecer o stock da loja se necessario.
 * No final, e apresentado o total a pagar pelo aluguer.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 * @param index indice do utente no vetor de utentes do sistema
 */
void Sistema::compraBike(int index) {

	if(stores.empty())
	{
		cout << "Neste momento não é possivel efetuar nenhuma compra visto ainda não existir nenhuma loja" << endl << endl;
		return;
	}

	cout << "Compra bicicleta" << endl << endl;

	cout << "Selecione o tipo de bicicleta pretendida: " << endl << endl;
	string option, bikeType, locname;
	int quantidade {}, value {}, indicator {};
	Data d1 {};
	bool condition {false};

	cout << "Tipos de bicicleta: " << endl;
	cout << "     1 - Urbana" << endl;
	cout << "     2 - Urbana Simples" << endl;
	cout << "     3 - Corrida" << endl;
	cout << "     4 - Infantil" << endl << endl;

	//Verifica o tipo de bicicleta(s) que pretende comprar
	while(1)
	{
		try{
			cout << endl << "Introduza uma opção [1-4]: ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);
			if(value < 1 || value > 4)
				throw OpcaoInvalida<int>(value);

			break;
		}
		catch (OpcaoInvalida<int> &op){

			cout << "Opção inválida (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Opção inválida (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	};

	//Verifica o tipo de bicicleta selecionada
	if(value == 1)
		bikeType = "Urbana";
	else if(value == 2)
		bikeType = "Urbana Simples";
	else if(value == 3)
		bikeType = "Corrida";
	else
		bikeType = "Infantil";

	//Indicador da posicao do tipo de bicicleta no vetor de inteiros de "loja"
	indicator = value - 1;

	//Verifica o numero de bicicletas que pretende comprar
	while(1)
	{
		try{
			cout << endl << "Quantidade [1-5]: ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			quantidade = stoi(option);
			if(quantidade < 1 || quantidade > 5)
				throw OpcaoInvalida<int>(quantidade);

			break;
		}
		catch (OpcaoInvalida<int> &op){

			cout << "Quantidade inválida (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Quantidade inválida (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	};

	//Percorrer todas as lojas disponiveis e verificar quais possuem stock para a compra
	priority_queue<Loja> tmp = stores;

	while(!tmp.empty())
	{
		if(tmp.top().getStock(indicator) >= (unsigned int)quantidade) {
			if(condition == false)
				condition = true;
		}
		tmp.pop();
	}

	if(condition == false)
	{
		cout << endl << "Neste momento nenhuma das lojas existentes possui stock suficiente para satisfazer a presente compra" << endl << endl;
		return;
	}
	else
		condition = false;

	cout << endl << "Última utilização: " << dataAtual.getDia() << "/" << dataAtual.getMes() << "/" << dataAtual.getAno() << endl << endl;
	cout << "Data de compra:" << endl;

	//Executa até obter um ano válido
	while(1)
	{
		try{
			cout << endl << "Ano [" << dataAtual.getAno() << " ->]: ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);
			if(value < (int)dataAtual.getAno())
				throw OpcaoInvalida<int>(value);

			d1.setAno(value);
			break;
		}
		catch (OpcaoInvalida<int> &op){

			cout << "Ano inválido (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Ano inválido (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	};

	//Executa até obter um mês válido
	while(1)
	{
		try{
			if(dataAtual.getAno() < d1.getAno())
				cout << endl << "Mês [1-12]: ";
			else
				cout << endl << "Mês [" << dataAtual.getMes() << "-12]: ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(dataAtual.getAno() < d1.getAno())
			{
				if(value < 1 || value > 12)
					throw OpcaoInvalida<int>(value);
			}
			else
			{
				if(value < (int)dataAtual.getMes() || value > 12)
					throw OpcaoInvalida<int>(value);
			}

			d1.setMes(value);
			break;
		}
		catch (OpcaoInvalida<int> &op){

			cout << "Mês inválido (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Mês inválido (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	};

	/* Executa até obter um dia válido
	 * Considera que fevereiro tem 28 dias
	 */
	while(1)
	{
		try{
			cout << endl << "Dia: ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if((d1.getMes() == dataAtual.getMes()) && (d1.getAno() == dataAtual.getAno()))
			{
				if(d1.getMes() == 2)
				{
					if(value < (int)dataAtual.getDia() || value > 28)
						throw OpcaoInvalida<int>(value);

					d1.setDia(value);
					break;
				}
				else if((d1.getMes() == 1) ||(d1.getMes() == 3) ||(d1.getMes() == 5) ||
						(d1.getMes() == 7) ||(d1.getMes() == 8) ||(d1.getMes() == 10) ||(d1.getMes() == 12))
				{
					if(value < (int)dataAtual.getDia() || value > 31)
						throw OpcaoInvalida<int>(value);

					d1.setDia(value);
					break;
				}
				else
				{
					if(value < (int)dataAtual.getDia() || value > 30)
						throw OpcaoInvalida<int>(value);

					d1.setDia(value);
					break;
				}
			}
			else
			{
				if(d1.getMes() == 2)
				{
					if(value < 1 || value > 28)
						throw OpcaoInvalida<int>(value);

					d1.setDia(value);
					break;
				}
				else if((d1.getMes() == 1) ||(d1.getMes() == 3) ||(d1.getMes() == 5) ||
						(d1.getMes() == 7) ||(d1.getMes() == 8) ||(d1.getMes() == 10) ||(d1.getMes() == 12))
				{
					if(value < 1 || value > 31)
						throw OpcaoInvalida<int>(value);

					d1.setDia(value);
					break;
				}
				else
				{
					if(value < 1 || value > 30)
						throw OpcaoInvalida<int>(value);

					d1.setDia(value);
					break;
				}
			}
		}
		catch (OpcaoInvalida<int> &op){

			cout << "Dia inválido (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Dia inválido (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	};

	//Atualiza a data se necessária
	updateData(d1);

	//Percorrer todas as lojas disponiveis e verificar quais possuem stock para a compra
	while(!stores.empty())
	{

		if(stores.top().getStock(indicator) >= (unsigned int)quantidade)
		{
			if(condition == false)
			{
				condition = true;
				Loja tmp_store = stores.top();
				tmp_store.setStock(indicator,quantidade);

				//Atribui uma classificao á loja de 0 a 5
				while(1)
				{
					try{
						cout << endl << "Classificação da compra [1-5]: ";
						cin >> option;
						cin.ignore(1000,'\n');
						if(valid_number(option) == false)
							throw OpcaoInvalida<string>(option);

						value = stoi(option);
						if(value < 1 || value > 5)
							throw OpcaoInvalida<int>(value);

						break;
					}
					catch (OpcaoInvalida<int> &op){

						cout << "Classificação inválida (" << op.opcao << ") ! Tente novamente." << endl;
						cin.clear();
					}
					catch (OpcaoInvalida<string> &op){

						cout << "Classificação inválida (" << op.opcao << ") ! Tente novamente." << endl;
						cin.clear();
					}
				};
				locname = tmp_store.getLocal()->getNome();
				tmp_store.setNumberOpinions();
				tmp_store.setReputation((unsigned int)value);

				//Verifica se é necessário reabastecer o stock
				tmp_store.checkStock(indicator);

				tmp.push(tmp_store);
			}
			else
				tmp.push(stores.top());
		}
		else
			tmp.push(stores.top());

		stores.pop();
	}

	//Atualiza a fila de prioridade stores
	stores = tmp;

	Utilizacao use(bikeType,quantidade,d1,"",locname);
	utentes.at(index)->setHistoricoCompras(use);

	system("cls");
	mensagemInicial();
	cout << "Resumo da compra:" << endl << endl;

	cout << "Local: " << locname << endl;
	cout << "Data (DD:MM:AAAA): " << d1.getDia() << "/" << d1.getMes() << "/" << d1.getAno() << endl;
	cout << "Tipo de bicicleta: " << bikeType << endl;
	cout << "Quantidade: " << quantidade << endl;
	cout << "Preço: ";

	if(indicator == 0)
		cout << 150*quantidade << "€" << endl << endl;
	else if(indicator == 1)
		cout << 200*quantidade << "€" << endl << endl;
	else if(indicator == 2)
		cout << 250*quantidade << "€" << endl << endl;
	else
		cout << 100*quantidade << "€" << endl << endl;

	cout << "Bicicleta do tipo " << bikeType << " comprada com sucesso !" << endl << endl;
}

/**
 * Apresenta o tipo de utente atual e pede confirmacao da decisao de mudar de tipo de utente.
 * Se o utente Socio tentar mudar o tipo de utente e ainda tiver pagamentos pendentes e-lhe
 * apresentada uma mensagem e a decisao nao e permitida.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 * @param index indice do utente no vetor de utentes do sistema
 * @return Retorna 0 caso a operacao seja efetuada, caso contrario retorna 1
 */
int Sistema::mudaTipoUT(int index){

	cout << "Muda tipo de utente" << endl << endl;

	string option;
	string tipo = utentes.at(index)->getTipoUtente();

	if(utentes.at(index)->getAvailable() == false)
	{
		cout << "Não é possível mudar o tipo de utente uma vez que a bicicleta alugada ainda não foi devolvida" << endl << endl;
		return 1;
	}

	if(utentes.at(index)->hasPendingPay())
	{
		cout << "Neste momento não é possível mudar o tipo de utente visto que existem pagamentos pendentes" << endl << endl;
		return 1;
	}

	cout << "Neste momento encontra-se definido como: " << tipo << endl << endl;

	while(1)
	{
		try {
			if(tipo == "Regular")
				cout << "Tem a certeza que pretende mudar para Sócio [Y/N]: ";
			else
				cout << "Tem a certeza que pretende mudar para Regular [Y/N]: ";

			cin >> option;
			cin.ignore(1000,'\n');

			if(valid_word(option) == false)
				throw OpcaoInvalida<string>(option);

			if((option == "Y") || (option == "N"))
				break;

			throw OpcaoInvalida<string>(option);
		}
		catch (OpcaoInvalida<string> &op) {
			cout << "Opção inválida (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	}

	if(option == "Y")
	{
		int id = utentes.at(index)->getId();
		string nome = utentes.at(index)->getNome();
		Localizacao local = utentes.at(index)->getLocalizacao();
		vector<Utilizacao> hist = utentes.at(index)->getHistorico();
		Utente* u;

		if(tipo == "Regular")
			u = new Socio(nome,local);
		else
			u = new Regular(nome,local);

		u->setID(id);
		u->setLastId();

		for(unsigned int i=0; i < hist.size() ; i++){
			u->setHistoric(hist.at(i));
		}

		utentes.erase(utentes.begin() + index);
		addNewUtente(u);
		sort(utentes.begin(), utentes.end(), sortById);

		cout << endl << "Mudança efetuada com sucesso. Agora o seu tipo é: ";

		if(tipo == "Regular")
			cout << "Sócio" << endl << endl;
		else
			cout << "Regular" << endl << endl;

	}
	else
	{
		cout << endl << "Mudança cancelada com sucesso " << endl << endl;
		return 1;
	}

	return 0;
}

/**
 * Verifica se existem bicicletas a aguardar abate, se sim, imprime-as no ecra
 * para o utilizador selecionar a que pretende abater, senao e impressa uma
 * mensagem. A bicicleta selecionada e abatida.
 */
void Sistema::abateBike(){

	tabHAbates::const_iterator it = junkyard.begin();
	string option, bikeName;
	int indicator {1}, value {};
	vector<Bicicleta> bikeNamesAcess;
	bool exist {false};

	if(it == junkyard.end())
	{
		cout << "Neste momento não existem bicicletas a aguardar abate" << endl << endl;
		return;
	}

	for(it = junkyard.begin(); it != junkyard.end(); it++)
	{
		if(it->getAbate().getAno() == 0) {
			exist = true;
			break;
		}
	}

	if(exist == false)
	{
		cout << "Neste momento não existem bicicletas a aguardar abate" << endl << endl;
		return;
	}

	cout << "Abate bicicleta" << endl << endl;
	cout << "Bicicletas disponiveis para abate:" << endl;

	for(it = junkyard.begin(); it != junkyard.end(); it++)
	{
		if(it->getAbate().getAno() == 0)
		{
			cout << left << setw(2) << indicator << " -> " << it->getBikeName() << endl;
			bikeNamesAcess.push_back(*it);
			indicator++;
		}
	}

	//Seleciona uma das bicicletas
	while(1)
	{
		try {
			cout << endl << "Bicicleta (1-" << (indicator - 1) << "): ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value < 1 || value > (indicator - 1))
				throw OpcaoInvalida<int>(value);

			bikeName = bikeNamesAcess.at(value - 1).getBikeName();
			break;
		}
		catch (OpcaoInvalida<int> &op){
			cout << "Bicicleta inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		catch (OpcaoInvalida<string> &op){
			cout << "Bicicleta inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};

	for(it = junkyard.begin(); it != junkyard.end(); it++)
	{
		if(it->getBikeName() == bikeName)
		{
			Bicicleta tmp = (*it);
			tmp.setAbate(dataAtual);
			junkyard.erase(it);
			junkyard.insert(tmp);
			break;
		}
	}

	cout << endl << "Bicicleta " << bikeName << " abatida com sucesso !" << endl << endl;
}

///////////////////////////
// MANAGEMENT ALGORITHMS //
///////////////////////////

/**
 * Verifica se existe excesso (<=8) ou defice (>=2) de bicicletas do tipo bikeType nos pontos de partilha,
 * caso se verifique as bicicletas sao distribuidas pelos pontos de partilha uniformemente.
 * @param index indice do ponto de partilha em que ocorreu o ultimo movimento (aluguer ou devolucao)
 * @param bikeType tipo de bicicleta que se pretende verificar
 */
void Sistema::system_Manager(unsigned int index, string bikeType) {

	int value {-1};
	int tamanho{-1};
	vector<int> indicesSup5, indicesInf5;

	if(bikeType == "Urbana")
		value = 0;
	else if(bikeType == "Urbana Simples")
		value = 1;
	else if(bikeType == "Corrida")
		value = 2;
	else
		value = 3;

	tamanho = pontosPartilha.at(index)->getBikes().at(value).size();

	//Guarda os indices dos pontos de partilha nos vetores indicesSup5 e indicesInf5
	for(unsigned int i = 0; i < pontosPartilha.size(); i++)
	{
		if(i != index)
		{
			if(pontosPartilha.at(i)->getBikes().at(value).size() > 5)
				indicesSup5.push_back(i);
			else if(pontosPartilha.at(i)->getBikes().at(value).size() < 5)
				indicesInf5.push_back(i);
		}

	}

	//Ordena os vectores por ordem crescente
	sort(indicesSup5.begin(), indicesSup5.end());
	sort(indicesInf5.begin(), indicesInf5.end());

	//Necessita de receber bicicletas
	if(tamanho <= 2)
	{

		int totalNumberBikes = 0;

		for(unsigned int i = 0; i < pontosPartilha.at(index)->getNumberOfBikes().size(); i++)
			totalNumberBikes += pontosPartilha.at(index)->getNumberOfBikes().at(i);

		//Distribui bicicletas
		for(int k = indicesSup5.size() - 1; k >= 0; k--)
		{
			while(pontosPartilha.at(indicesSup5.at(k))->getBikes().at(value).size() > 5)
			{
				if(pontosPartilha.at(index)->getBikes().at(value).size() == 5)
					break;

				Bicicleta* bike = pontosPartilha.at(indicesSup5.at(k))->getBikes().at(value).at(0);

				if(totalNumberBikes < pontosPartilha.at(index)->getCapacidade())
				{
					pontosPartilha.at(index)->adicionaBike(bike);
					pontosPartilha.at(indicesSup5.at(k))->removeBike(bike->getBikeName());
					totalNumberBikes++;
				}
				else
					break;

			}

			if(pontosPartilha.at(index)->getBikes().at(value).size() == 5)
				break;
		}
	}
	else if(tamanho >= 8)	//Necessita de fornecer bicicletas
	{
		//Distribui bicicletas
		for(unsigned int k = 0; k < indicesInf5.size(); k++)
		{
			int totalNumberBikes = 0;

			for(unsigned int i = 0; i < pontosPartilha.at(indicesInf5.at(k))->getNumberOfBikes().size(); i++)
				totalNumberBikes += pontosPartilha.at(indicesInf5.at(k))->getNumberOfBikes().at(i);

			while(pontosPartilha.at(indicesInf5.at(k))->getBikes().at(value).size() < 5)
			{
				if(pontosPartilha.at(index)->getBikes().at(value).size() == 5)
					break;

				Bicicleta* bike = pontosPartilha.at(index)->getBikes().at(value).at(0);

				if(totalNumberBikes < pontosPartilha.at(indicesInf5.at(k))->getCapacidade())
				{
					pontosPartilha.at(indicesInf5.at(k))->adicionaBike(bike);
					pontosPartilha.at(index)->removeBike(bike->getBikeName());
					totalNumberBikes++;
				}
				else
					break;

			}

			if(pontosPartilha.at(index)->getBikes().at(value).size() == 5)
				break;
		}
	}

	return;
}

/**
 * Gera um numero aleatorio de 1-10.
 * (1-5) -> Devolve no ponto de partilha;
 * (6-8) -> Gera avarias entre 0 e 10  e envia bicicleta para a oficina;
 * (9-10) -> Envia a bicicleta para abate;
 * @param bike apontador da bicicleta que se pretende gerar um estado
 */
bool Sistema::generateBikeStatus(Bicicleta* bike) {

	srand (time(NULL));
	int random_number {};

	random_number = rand() % 10 + 1;

	//1-5 -> Devolve no ponto de partilha  || 6-8 -> Envia bicicleta para a oficina  || 9-10 -> Envia a bicicleta para abate

	if((random_number >= 1) && (random_number <= 5))
		return true;
	else if((random_number >= 6) && (random_number <= 8))
	{
		int value {};
		vector<string> pieces;

		pieces.push_back("Pneu"); pieces.push_back("Corrente"); pieces.push_back("Pedais");
		pieces.push_back("Guiador"); pieces.push_back("Assento"); pieces.push_back("Cremalheira");
		pieces.push_back("Punhos"); pieces.push_back("Travão"); pieces.push_back("Amortecedor");
		pieces.push_back("Roda");

		//Gera numero (X) de peças estragadas de um total de 10
		random_number = rand() % 10 + 1;

		//Seleciona aleatoriamente as X pecas avariadas e adiciona-as as vetor de avarias na biclicleta
		while(random_number != 0)
		{
			srand (time(NULL));
			value = rand() % (pieces.size());
			bike->addAvarias(pieces.at(value));
			pieces.erase(pieces.begin() + value);
			random_number--;
		}

		//Adiciona a bicicleta a oficina
		repairShop.addBrokenBike(bike);
		cout << endl << "Bicicleta devolvida com sucesso na oficina !" << endl << endl;
	}
	else
	{
		//Adiciona a bicicleta para abate
		junkyard.insert(*bike);
		cout << endl << "Bicicleta devolvida com sucesso no ferro-velho !" << endl << endl;
	}

	return false;
}

/**
 * Compara a data com a dataAtual e atualiza-a caso sejam diferentes.
 * @param data nova data
 */
void Sistema::updateData(Data data) {

	if(dataAtual.getAno() == data.getAno())
	{
		if(dataAtual.getMes() == data.getMes())
		{
			if(dataAtual.getDia() == data.getDia())
				return;
		}
	}

	dataAtual = data;

}

/////////////////////
// METODOS DISPLAY //
/////////////////////

/**
 * Imprime por ordem crescente de distancia do utente, os pontos de partilha (designacao do ponto de partilha e nome da localizacao).
 * @param index indice do utente no vetor de utentes do sistema
 */
void Sistema::displayNearestPP(int index) const {

	cout << "Pontos de partilha mais próximos: " << endl << endl;

	vector<int> distancias = getOrderedPP(index);

	cout << "Ordem   Nome" << setw(16) << "Local"<< endl;

	for(unsigned int i = 0; i < distancias.size(); i++)
	{
		string nomePP = pontosPartilha.at(distancias.at(i))->getNome();
		string localName = pontosPartilha.at(distancias.at(i))->getLocal().getNome();

		cout << "  " << setw(5) << left << (i+1) << "ECO_RIDES_" << setw(5) << nomePP;
		cout << localName << endl;
	}

	cout << endl;

	return;
}

/**
 * Imprime no ecra a informacao dos utentes (nome, id, tipo de utente e coordenadas da localizacao).
 */
void Sistema::displayUtentes() const {

	cout << left << setw(15) << "   Nome" << setw(6) << " ID" << setw(27) << " Tipo de utente" << setw (20) << " GPS" << endl;

	for (unsigned int i=0 ; i	< utentes.size() ; i++)
	{
		cout << "-> " << setw(13) << utentes.at(i)->getNome();
		cout << setw(10) << utentes.at(i)->getId();
		cout << setw(14) << utentes.at(i)->getTipoUtente();
		cout << '(' << setw(9) << utentes.at(i)->getLocalizacao().getX();
		cout << "," << setw(9) << utentes.at(i)->getLocalizacao().getY() << setw(5) << ')' << endl;
	}

	cout << endl;

}

/**
 * Apresenta uma lista de todas as lojas existentes e pede para selecionar uma.
 * De seguida e impressa a informacao sobre essa loja: localizacao, reputacao,
 * capacidade e stock.
 */
void Sistema::displayStoreInfo() const {

	if(stores.empty())
	{
		cout << "Neste momento não existe nenhuma loja !" << endl << endl;
		return;
	}

	cout << "Informação sobre uma determinada loja" << endl << endl;

	cout << "Lojas disponiveis:" << endl;

	priority_queue<Loja> tmp = stores;
	int tmp_index {1};
	string option,locname;
	int value {};

	//Verifica as lojas disponveis para remocao
	while(!tmp.empty())
	{
		cout << tmp_index << " - Loja em " << tmp.top().getLocal()->getNome() << endl;
		tmp_index++;
		tmp.pop();
	}

	//Verifica qual a loja selecionada
	while(1)
	{
		try {
			cout << endl << "Introduza uma opção (1-" << (tmp_index - 1) << "): ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value < 1 || value > (tmp_index - 1))
				throw OpcaoInvalida<int>(value);

			break;
		}
		catch (OpcaoInvalida<int> &op){

			cout << "Opção inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Opção inválida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};

	system("cls");
	mensagemInicial();
	cout << "Informação sobre uma determinada loja" << endl << endl;

	tmp_index = 1;
	tmp = stores;

	//Remove loja
	while(!tmp.empty())
	{
		if(tmp_index == value)
		{
			cout << "Local: " << tmp.top().getLocal()->getNome() << endl << endl;
			cout << "GPS: " << "(" << tmp.top().getLocal()->getX() << "," << tmp.top().getLocal()->getY() << ")" << endl << endl;
			cout << "Reputação: " << tmp.top().getReputation() << endl << endl;
			cout << "Capacidade: " << tmp.top().getCapacity();

			cout << endl << endl << "Stock:" << endl << endl;

			cout << setw(22) << left << "Tipo de bicicleta" << "Unidades" << endl;
			cout << setw(26) << "Urbana" << tmp.top().getStock(0) << endl <<
					setw(26) << "Urbana Simples" << tmp.top().getStock(1) << endl <<
					setw(26) << "Corrida" << tmp.top().getStock(2) << endl <<
					setw(26) << "Infantil" << tmp.top().getStock(3) << endl << endl;
		}

		tmp_index++;
		tmp.pop();
	}
	cout << endl;
}

/**
 * Apresenta o top 5 das lojas do sistema.
 * Imprime a informacao das 5 lojas com maior reputacao (imprime a sua localizacao e reputacao).
 */
void Sistema::displayMostRepStores() const {

	priority_queue<Loja> tmp = stores;
	int indicator {1};

	if(stores.size() >= 5)
	{
		cout << "Top 5 - Lojas" << endl << endl;
		cout << setw(5) << "ID" << setw(23) << "Localizacao" << "Reputacao" << endl;
		while(indicator != 6)
		{
			cout << setw(5) << indicator << setw(27) << tmp.top().getLocal()->getNome() << tmp.top().getReputation() << endl;
			indicator++;
			tmp.pop();
		}
	}
	else if(stores.empty())
	{
		cout << "Neste momento não existe nenhuma loja" << endl << endl;
		return;
	}
	else
	{
		cout << "Top " << stores.size() << " - Lojas" << endl << endl;
		cout << setw(5) << "ID" << setw(23) << "Localizacao" << "Reputacao" << endl;
		while(!tmp.empty())
		{
			cout << setw(5) << indicator << setw(27) << tmp.top().getLocal()->getNome() << tmp.top().getReputation() << endl;
			indicator++;
			tmp.pop();
		}

	}

}

/**
 * Apresenta todas as bicicletas que foram envidas para abate.
 * As bicicletas que ja foram abatidas, tem a data de abate, as que ainda
 * aguardam abate tem --/--/----. E impresso o tipo de bicicleta, o nome, a
 * data de abate.
 */
void Sistema::displayJunkyardInfo() const {

	tabHAbates::const_iterator it = junkyard.begin();
	int indicator {1};
	if(it == junkyard.end()) {
		cout << "Neste momento não existem bicicletas enviadas para abate" << endl << endl;
		return;
	}

	cout << "Consultar bicicletas enviadas para abate" << endl << endl;

	cout << "Bicicletas enviadas para abate:" << endl;
	cout << right << "Ordem" << setw(10) << "Tipo" << setw(18) <<  "Nome" << setw(21) << "Data de abate" << endl;

	for(it = junkyard.begin(); it != junkyard.end(); it++){
		cout << "  " << left << setw(9) << indicator;
		cout << setw(18);
		if(it->getBikeName().at(0) == 'c')
			cout << "Corrida";
		else if(it->getBikeName().at(0) == 'i')
			cout << "Infantil";
		else
		{
			if(it->getBikeName().at(1) == 's')
				cout << "Urbana Simples";
			else
				cout << "Urbana";
		}

		cout << setw(14) << it->getBikeName();

		if(it->getAbate().getAno() == 0)
			cout << "--/--/----" << endl;
		else
			cout << it->getAbate() << endl;

		indicator++;
	}
	cout << endl;
}
