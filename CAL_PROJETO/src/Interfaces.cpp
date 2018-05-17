#include "Includes.h"
#include "Sistema.h"

/////////////////////////////////////
// IMPLEMENTACAO DE FUNCOES GERAIS //
/////////////////////////////////////

bool valid_number(string number)
{
	for (unsigned int i = 0; i < number.size(); i++){
		if (!(isdigit(number.at(i))))
			return false;
	}
	return true;
}

bool valid_number_double(string number)
{
	for (unsigned int i = 0; i < number.size(); i++){
		if ((!(isdigit(number.at(i)))) && (number.at(i) != '.') && (number.at(i) != '-'))
			return false;
	}
	return true;
}

bool valid_word(string word)
{
	for (unsigned int i = 0; i < word.size(); i++){
		if (isdigit(word.at(i)))
			return false;
	}
	return true;
}

void mensagemInicial(){
	//Informacao inicial apresentada ao utilizador
	cout << "######  ####### #######      ##########  ##  #####    ######  #######" << endl;
	cout << "##      ##      ##   ##      ##      ##  ##  ##  ##   ##      ##     " << endl;
	cout << "#####   ##      ##   ##      ##  ######  ##  ##   ##  #####   #######" << endl;
	cout << "##      ##      ##   ##      ##    ##    ##  ##  ##   ##           ##" << endl;
	cout << "######  ####### #######      ##     ###  ##  #####    ######  #######" << endl << endl;
}


//// --- VISUALIZACAO DO GRAFO --- ////

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
					if(idNoDestino==path.at(j)){
						gv->setEdgeThickness(idAresta,4);
						gv->setEdgeColor(idAresta,"red");
					}
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
				std::getline(linestream2, nomeRua, ';');
				linestream2 >> Direcao;
			}
		}
		if(Direcao==0)
			gv->addEdge(idAresta,idNoOrigem,idNoDestino, EdgeType::UNDIRECTED);

		else if (Direcao==1)
			gv->addEdge(idAresta,idNoOrigem,idNoDestino, EdgeType::DIRECTED);

		gv->setEdgeLabel(idAresta, nomeRua);
	}

	inFile.close();


	gv->rearrange();

}


/////////////////////////
// INTERFACES -> MENUS //
/////////////////////////

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
		cout << "5  - Visualizar caminho mais curto até um Ponto de Partilha" << endl;
		cout << "6  - Pesquisar Ponto de Partilha entre duas ruas" << endl;
		cout << "7  - Informacoes sobre ECO_RIDES" << endl;
		cout << "8  - Logout" << endl << endl;

		while(1)
		{
			try {

				cout << endl << "Introduza uma opcao (1-8): ";
				cin >> option;
				cin.ignore(1000,'\n');

				if(valid_number(option) == false)
					throw OpcaoInvalida<string>(option);

				value = stoi(option);

				if(value < 1 || value > 8)
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
			ER.alugaBike(index);
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
			graphviewer_displayPath(ER,index);
			break;
		case 6:
			ER.pesquisaRuas();
			break;
		case 7:
			ER.getInfo();
			break;
		case 8:
			if(!utente->getAvailable()) {
				cout << endl << "Antes de efetuar logout o utente necessita primeiramente de devolver a bicicleta !" << endl;
				value = -1;
			}
			cout << endl;
			break;
		}

		if(value != 8)
			system("pause");

		system("cls");

	}while(value != 8);

	cout << endl;
	system("cls");
	return;
}

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
			ER.removeUtente();
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
		case 1:
			ER.addNewUtente();
			break;
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

