#include "Includes.h"
#include "Sistema.h"
#include "GraphViewer.h"
void graphviewer_displayPath(Sistema &ER, double cliente);

void graphviewer_displayPath(Sistema &ER,double cliente)
{
	vector<int> path = ER.path_rentavel(cliente);
	GraphViewer *gv = new GraphViewer { 800, 800, false };
		gv->createWindow(800,800);
		gv->defineEdgeColor("blue");
		gv->defineVertexColor("yellow");
		gv->defineEdgeCurved(false);

		ifstream inFile;

		//Ler o ficheiro nos.txt
		inFile.open("nodes.txt");

		if (!inFile) {
			cerr << "Unable to open file nodes.txt";
			exit(1);   // call system to stop
		}

		std::string   line,line2,line3;

		int idNo=0;
		double X=0;
		double Y=0;
		int idStore=0;
		string a="";
		path={6,5,4,31,3};

		double longmin=INF, latmin=INF, longmax=-INF, latmax=-INF;

		for(auto n : ER.getNodes()){
			if(n.getLongitude()<longmin)
				longmin=n.getLongitude();
			if(n.getLatitude()<latmin)
				latmin=n.getLatitude();
			if(n.getLongitude()>longmax)
				longmax=n.getLongitude();
			if(n.getLatitude()>latmax)
				latmax=n.getLatitude();
		}


		string letra;
		while(std::getline(inFile, line))
		{

			std::stringstream linestream(line);
			std::string         data;

			linestream >> idNo;
			std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
			linestream >> X;
			std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
			linestream >> Y;
			std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).

			X=(X-longmin)/(longmax-longmin)*2000;
			Y=(Y-latmin)/(latmax-latmin)*2000;

			gv->addNode(idNo,Y,X);//-----------------------------------------------------------------------

			ifstream store;
			store.open("pontosPartilha.txt");
			if (!store)
			{
				cerr << "Unable to open file pontosPartilha.txt";
				exit(1);   // call system to stop
			}

			while(std::getline(store, line3))
			{
				std::stringstream linestream3(line3);

				std::getline(linestream3, data, '/');  // read up-to the first ; (discard ;).
				linestream3 >> idStore;
				std::getline(linestream3, data, '/');
				if(idStore==idNo)
				{
					gv->setVertexColor(idNo,"green");
				}
			}
			store.close();
		}

		inFile.close();


		//Ler o ficheiro arestas.txt
		inFile.open("subroads.txt");

		if (!inFile) {
			cerr << "Unable to open file datafile.txt";
			exit(1);   // call system to stop
		}

		int idAresta=0;
		int idStreet=0;
		int idNoOrigem=0;
		int idNoDestino=0;
		string nomeRua="";
		int Direcao;
		double rua=0;

		while(std::getline(inFile, line))
		{
			std::stringstream linestream(line);

			std::string data;

			idAresta++;
			linestream >> rua;

			std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
			linestream >> idNoOrigem;
			std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
			linestream >> idNoDestino;
			ifstream street;
			for(unsigned int i=0; i<path.size();i++)
			{
				if(idNoOrigem==path.at(i))
				{
					for(unsigned int j=0; j< path.size();j++)
						if(idNoDestino==path.at(j))
						//	gv->setEdgeThickness(idAresta,4);
							gv->setEdgeColor(idAresta,"red");
				}
			}
			street.open("roads.txt");
			if (!street) {
				cerr << "Unable to open file datafile.txt";
				exit(1);   // call system to stop
			}
			while(std::getline(street, line2))
			{
				std::stringstream linestream2(line2);
				linestream2 >> idStreet;
				if(idStreet==rua)
				{
					std::getline(linestream2, data, ';');  // read up-to the first ; (discard ;).
					linestream2 >> nomeRua;
					std::getline(linestream2, data, ';');
					linestream2 >> Direcao;
				}
			}
			if(Direcao==0)
				gv->addEdge(idAresta,idNoOrigem,idNoDestino, EdgeType::UNDIRECTED);

			else if (Direcao==1)
				gv->addEdge(idAresta,idNoOrigem,idNoDestino, EdgeType::DIRECTED);
		}

		inFile.close();


		gv->rearrange();

}


/////////////////////////////////////
// IMPLEMENTACAO DE FUNCOES GERAIS //
/////////////////////////////////////

/**
 * Verifica se a string number contem apenas digitos ou se contem simbolos ou caracteres nao
 * aceites para a situacao.
 * @param number string extraida da stream de input
 * @return Retorna true se number e um numero e false se number contem alguma coisa para alem de digitos.
 */
bool valid_number(string number)
{
	for (unsigned int i = 0; i < number.size(); i++){
		if (!(isdigit(number.at(i))))
			return false;
	}
	return true;
}

/**
 * Verifica se a string number contem apenas digitos e um ponto ou um hifen,
 * ou se contem simbolos ou caracteres nao aceites para a situacao.
 * @param number string extraida da stream de input
 * @return Retorna true se number e um numero decimal negativo ou positivo e false se number contem alguma coisa para alem de digitos.
 */
bool valid_number_double(string number)
{
	for (unsigned int i = 0; i < number.size(); i++){
		if ((!(isdigit(number.at(i)))) && (number.at(i) != '.') && (number.at(i) != '-'))
			return false;
	}
	return true;
}

/**
 * Verifica se a string word nao contem numeros.
 * @param word string extraida da stream de input
 * @return Retorna true se nao contem numeros e false caso contrario.
 */
bool valid_word(string word)
{
	for (unsigned int i = 0; i < word.size(); i++){
		if (isdigit(word.at(i)))
			return false;
	}
	return true;
}

/**
 * Verifica se o nome da bicicleta e correto, nao pode comecar por um numero.
 * @param bike string extraida da stream de input
 * @return Retorna true se nao comeca por um numero e false caso contrario.
 */
bool valid_bike(string bike)
{
	if (isdigit(bike.at(0)))
		return false;

	return true;
}

/**
 * Funcao que imprime no ecra o logotipo da empresa ECO RIDES.
 */
void mensagemInicial(){
	//Informacao inicial apresentada ao utilizador
	cout << "######  ####### #######      ##########  ##  #####    ######  #######" << endl;
	cout << "##      ##      ##   ##      ##      ##  ##  ##  ##   ##      ##     " << endl;
	cout << "#####   ##      ##   ##      ##  ######  ##  ##   ##  #####   #######" << endl;
	cout << "##      ##      ##   ##      ##    ##    ##  ##  ##   ##           ##" << endl;
	cout << "######  ####### #######      ##     ###  ##  #####    ######  #######" << endl << endl;
}


/////////////////////////
// INTERFACES -> MENUS //
/////////////////////////

/**
 * Primeiramente imprime a informacao de todos os utentes e pede ao utente que insira um id
 * para efetuar o login.
 * Apresenta no ecra os casos de utilizacao para o utente escolher a opcao que pretende (10 opcoes no total).
 * Depois de introduzida a opcao por parte do utente, e efetuado o procedimento que
 * corresponde a opcao escolhida. Para cada uma das 9 primeiras opcoes e chamado um metodo da classe Sistema
 * ou Utente, que executa o procedimento necessario para o que o utente pretende, e a ultima opcao ,
 * 10 - Logout, retorna a funcao openInterfaces, onde esta foi invocada.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 * @param ER sistema em execucao
 */
void menu_interface(Sistema &ER){

	mensagemInicial();

	int attempts{0};
	int identificacao{};
	int index{};	//Indice do utente no vector de utentes do sistema
	string info{};

	cout << "Utentes: " << endl << endl;

	ER.displayUtentes();

	while(attempts < 3)
	{
		try{
			attempts++;
			cout << "Login [Utente ID]: ";
			cin >> info;
			cin.ignore(1000,'\n');

			if(valid_number(info) == false)
				throw OpcaoInvalida<string>(info);

			identificacao = stoi(info);

			index = ER.getUtenteIndex(identificacao);

			if(index == -1)
				throw OpcaoInvalida<int>(identificacao);

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
	};

	if(attempts >= 3)
	{
		cout << endl << "Acesso negado: numero de tentativas esgotado" << endl << endl;
		system("pause");
		system("cls");
		return;
	}

	system("cls");

	Utente* utente = ER.getUtentes().at(index);

	string option{};
	int value{};

	do
	{
		mensagemInicial();

		cout << "Bem-Vindo !" << endl << endl;

		cout << "1  - Alugar bicicleta" << endl;
		cout << "2  - Devolver bicicleta" << endl;
		cout << "3  - Historico" << endl;
		cout << "4  - Atualizar localizacao" << endl;
		cout << "5  - Pontos de partilha mais proximos / GraphViewer caminho mais curto" << endl;
		cout << "6  - Informacoes sobre ECO_RIDES" << endl;
		cout << "7  - Logout" << endl << endl;

		while(1)
		{
			try {

				cout << endl << "Introduza uma opcao (1-7): ";
				cin >> option;
				cin.ignore(1000,'\n');

				if(valid_number(option) == false)
					throw OpcaoInvalida<string>(option);

				value = stoi(option);

				if(value < 1 || value > 7)
					throw OpcaoInvalida<int>(value);

				break;
			}
			catch (OpcaoInvalida<int> &op){

				cout << "Opcao invalida(" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
			catch (OpcaoInvalida<string> &op){

				cout << "Opcao invalida(" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
		};

		system("cls");
		mensagemInicial();

		//Opcoes possiveis apresentadas no menu
		switch (value)
		{
		case 1:
			ER.alugaBike(index); //Algoritmo de Dijkstra
			break;
		case 2:
			ER.devolveBike(index);
			break;
		case 3:
			utente->displayHistoric();
			break;
		case 4:
			utente->updateLocation(index);
			break;
		case 5:
			graphviewer_displayPath(ER,value);
			ER.displayNearestPP(index);
			break;
		case 6:
			ER.getInfo();
			break;
		case 7:
			if(!utente->getAvailable()) {
				cout << endl << "Antes de efetuar logout o utente necessita primeiramente de devolver a bicicleta !" << endl;
				value = -1;
			}
			cout << endl;
			break;
		}

		if(value != 7)
			system("pause");

		system("cls");

	}while(value != 7);

	cout << endl;
	system("cls");
	return;
}

/**
 * Primeiramente pede ao utilizador que insira a senha ("1234") para aceder a opcoes administrativas.
 * Apresenta no ecra os casos de utilizacao para aministrador escolher a opcao que pretende (7 opcoes no total).
 * Depois de introduzida a opcao, e efetuado o procedimento que corresponde a opcao escolhida.
 * Para cada uma das 6 primeiras opcoes e chamado um metodo da classe Sistema que
 * executa o procedimento necessario para o que e pretendido, e a ultima opcao , 7 - Sair,
 * retorna a funcao openInterfaces, onde esta foi invocada.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 * @param ER sistema em execucao
 */
void admin_interface(Sistema &ER) {

	mensagemInicial();

	int attempts{0};
	string info{};

	while(attempts < 3)
	{
		try{
			attempts++;
			cout << "Admin (Password): ";
			cin >> info;

			if(valid_number(info) == false)
				throw OpcaoInvalida<string>(info);

			if(info != "1234")
				throw OpcaoInvalida<string>(info);

			break;
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Password invalida (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};

	if(attempts >= 3)
	{
		cout << endl << "Acesso negado: numero de tentativas esgotado" << endl << endl;
		system("pause");
		system("cls");
		return;
	}

	system("cls");

	string option{};
	int value{};

	do
	{
		mensagemInicial();

		cout << "Administracao" << endl << endl;
		cout << "1 - Remover utente" << endl;
		cout << "2 - Informacoes sobre ECO_RIDES" << endl;
		cout << "3 - Sair" << endl;


		while(1)
		{
			try {

				cout << endl << "Introduza uma opcao (1-3): ";
				cin >> option;

				if(valid_number(option) == false)
					throw OpcaoInvalida<string>(option);

				value = stoi(option);

				if(value < 1 || value > 7)
					throw OpcaoInvalida<int>(value);

				break;
			}
			catch (OpcaoInvalida<int> &op){

				cout << "Opcao invalida(" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
				cin.ignore(1000,'\n');
			}
			catch (OpcaoInvalida<string> &op){

				cout << "Opcao invalida(" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
				cin.ignore(1000,'\n');
			}
		};

		system("cls");
		mensagemInicial();

		//Opcoes possiveis apresentadas no menu
		switch (value)
		{
		case 1:
			ER.removeUtente(); //Algoritmo de Dijkstra
			break;
		case 2:
			ER.getInfo();
			break;
		}
		if(value != 3)
			system("pause");

		system("cls");

	}while(value != 3);

	system("cls");
	return;
}

/**
 * Apresenta no ecra a pagina inicial do programa, e aguarda que o utente decida qual a opcao
 * que deseja. Depois de introduzida a opcao por parte do utente, e efetuado o procedimento que
 * corresponde a opcao escolhida. 1-Registar chama a funcao registaUtente; 2-Entrar chama a funcao
 * menu_interfaces; 3- Administrador chama a funcao admin_interfaces; 4 - Sair retorna a funcao main,
 * onde esta ,openinterfaces, e invocada.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e e lancada uma excecao.
 * @param ER sistema em execucao
 */
void openInterface(Sistema & ER){

	int value{};
	string option{};

	do
	{
		mensagemInicial();

		cout << "1 - Registar " << endl;
		cout << "2 - Entrar" << endl;
		cout << "3 - Administrador" << endl;
		cout << "4 - Sair" << endl;

		while(1)
		{
			try{
				cout << endl << "Introduza uma opcao (1-4): ";
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

				cout << "Opcao invalida(" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
			catch (OpcaoInvalida<string> &op){

				cout << "Opcao invalida(" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
		};

		system("cls");

		//Opcoes possiveis apresentadas no menu
		switch (value)
		{

		case 2:
			menu_interface(ER);
			break;
		case 3:
			admin_interface(ER);
			break;
		case 4:
			cout << endl;
			break;
		}
	}while(value != 4);

	return;
}

