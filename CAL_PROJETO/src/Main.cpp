#include "Includes.h"
#include "Sistema.h"
#include "graphviewer.h"
using namespace std;

void openInterface(Sistema & ER);
void checkinSys(Sistema & ER);
void checkoutSys(Sistema & ER);
void graphviewer_display(Sistema & ER);

/**
 * Inicializacao do programa, checkin do sistema , apresentacao de interface ,
 * execucao das funcoes selecionadas e no final checkout do sistema.
 */
int main()
{

	///////////////////////////////////////
	// Zona de inicializacao do programa //
	///////////////////////////////////////

	mensagemInicial();

	Sistema sys{};

	cout << "APPLICATION LOADING";

	checkinSys(sys);

	sys.criarGrafo();

	graphviewer_display(sys);

	openInterface(sys);

	checkoutSys(sys);

	return 0;
}


void graphviewer_display(Sistema &ER)
{
	GraphViewer *gv = new GraphViewer(800, 800, false);
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

void print_path_GV(vector<Node> path,GraphViewer * gv)
{
	for(auto const &v: path)
	{
		gv->setVertexColor(v.getID(), RED);
	}
}

/**
 * Efetua a leitura dos 3 ficheiros se texto que contem a informacao sobre o sistema
 * e coloca-a corretamente no sistema.
 * Para efetuar a extracao da informacao, a funcao recorre ao operador de extracao >>
 * que foi redefenido para todas as classes usadas no sistema.
 * @param ER sistema que se pretende completar
 */
void checkinSys(Sistema & ER){
	ifstream f_utentes{};
	string f_line{};
	stringstream ss{};

	try{
		f_utentes.open("utentes.txt");
		if (!f_utentes.is_open())
			throw AberturaFalhada<string>("utentes.txt");
	}
	catch (AberturaFalhada<string> &a){
		cout << "Falha ao abrir o ficheiro " << a.getFicheiro() << "." << endl;
		cout << "Tente mais tarde.\n";
		return;
	}

	while(!f_utentes.eof()){
		getline(f_utentes,f_line);
		if (f_line != ""){
			ss << f_line;
			Utente *ut = new Utente{};
			ss >> *ut;
			ER.addNewUtente(ut);
		}
	}

	f_utentes.close();

	ifstream f_pontos_partilha{};

	try{
		f_pontos_partilha.open("pontosPartilha.txt");
		if (!f_pontos_partilha.is_open())
			throw AberturaFalhada<string>("pontosPartilha.txt");
	}
	catch (AberturaFalhada<string> &a){
		cout << "Falha ao abrir o ficheiro " << a.getFicheiro() << "." << endl;
		cout << "Tente mais tarde.\n";
		return;
	}

	while(!f_pontos_partilha.eof()){
		getline(f_pontos_partilha,f_line);
		if (f_line != ""){
			ss << f_line;
			PontoPartilha *pp = new PontoPartilha{};
			ss >> *pp;
			ER.addPontoPartilha(pp);
		}
	}

	f_pontos_partilha.close();

	ifstream f_nodes{};
	stringstream ss2{};

	try{
		f_nodes.open("nodes.txt");
		if (!f_nodes.is_open())
			throw AberturaFalhada<string>("nodes.txt");
	}
	catch (AberturaFalhada<string> &a){
		cout << "Falha ao abrir o ficheiro " << a.getFicheiro() << "." << endl;
		cout << "Tente mais tarde.\n";
		return;
	}

	while(!f_nodes.eof()){
		getline(f_nodes,f_line);
		if (f_line != ""){
			ss2 << f_line;
			Node node{};
			ss2 >> node;
			ER.addNode(node);
		}
	}

	f_nodes.close();

	ifstream f_streets{};
	ifstream f_connects{};
	stringstream ss3{};

	try{
		f_streets.open("roads.txt");
		if (!f_streets.is_open())
			throw AberturaFalhada<string>("roads.txt");
	}
	catch (AberturaFalhada<string> &a){
		cout << "Falha ao abrir o ficheiro " << a.getFicheiro() << "." << endl;
		cout << "Tente mais tarde.\n";
		return;
	}

	try{
		f_connects.open("subroads.txt");
		if (!f_connects.is_open())
			throw AberturaFalhada<string>("subroads.txt");
	}
	catch (AberturaFalhada<string> &a){
		cout << "Falha ao abrir o ficheiro " << a.getFicheiro() << "." << endl;
		cout << "Tente mais tarde.\n";
		return;
	}

	f_connects.close();

	stringstream ss4{};
	long long st{}, no1{}, no2{};
	char c1{}, c2{}, c3{};
	int id{0};

	while(!f_streets.eof()){
		getline(f_streets,f_line);
		if (f_line != ""){
			ss3 << f_line;
			Street street{};
			ss3 >> street;
			f_connects.open("subroads.txt");
			while(!f_connects.eof()){
				getline(f_connects,f_line);
				if (f_line != ""){
					ss4 << f_line;
					ss4 >> st >> c1 >> no1 >> c2 >> no2 >> c3;
					if(street.getID()==st)
						for(unsigned int i=0; i<ER.getNodes().size(); i++)
							if(ER.getNodes().at(i).getID()==no1 || ER.getNodes().at(i).getID()==no2){
								Node node{ER.getNodes().at(i)};
								//node.setID(i);
								Vertex<Node>* vert = new Vertex<Node>{node};
								street.addVertex(vert);
							}
				}
			}
			f_connects.close();
			//street.setID(id++);
			ER.addStreet(street);
		}
	}

	f_streets.close();

	return;
};

/**
 * Insere nos ficheiros de texto a informacao contida no sistema formatadamente.
 * Para efetuar a insercao da informacao, a funcao recorre ao operador de insercao <<
 * que foi redefenido para todas as classes usadas no sistema.
 * @param ER sistema que se pretende guardar
 */
void checkoutSys(Sistema & ER){

	ofstream f_utentes{};

	try{
		f_utentes.open("utentes.txt");
		if (!f_utentes.is_open())
			throw AberturaFalhada<string>("utentes.txt");
	}
	catch (AberturaFalhada<string> &a){
		cout << "Falha ao abrir o ficheiro " << a.getFicheiro() << "." << endl;
		cout << "Tente mais tarde./n";
		return;
	}

	for(unsigned int it=0 ; it<ER.getUtentes().size() ; it++){
		f_utentes << *ER.getUtentes().at(it) << endl;
	}

	f_utentes.close();

	ofstream f_pontos_partilha{};

	try{
		f_pontos_partilha.open("pontosPartilha.txt");
		if (!f_pontos_partilha.is_open())
			throw AberturaFalhada<string>("pontos_partilha.txt");
	}
	catch (AberturaFalhada<string> &a){
		cout << "Falha ao abrir o ficheiro " << a.getFicheiro() << "." << endl;
		cout << "Tente mais tarde./n";
		return;
	}

	for(unsigned int it=0 ; it<ER.getPontosPartilha().size() ; it++){
		f_pontos_partilha << *ER.getPontosPartilha().at(it) << endl;
	}

	f_pontos_partilha.close();

	ofstream f_nodes{};

	try{
		f_nodes.open("nodes.txt");
		if (!f_nodes.is_open())
			throw AberturaFalhada<string>("nodes.txt");
	}
	catch (AberturaFalhada<string> &a){
		cout << "Falha ao abrir o ficheiro " << a.getFicheiro() << "." << endl;
		cout << "Tente mais tarde./n";
		return;
	}

	for(unsigned int it=0 ; it<ER.getNodes().size() ; it++){
		f_nodes << ER.getNodes().at(it) << endl;
	}

	f_nodes.close();

	ofstream f_streets{};
	ofstream f_connections{};

	try{
		f_utentes.open("roads.txt");
		if (!f_utentes.is_open())
			throw AberturaFalhada<string>("roads.txt");
	}
	catch (AberturaFalhada<string> &a){
		cout << "Falha ao abrir o ficheiro " << a.getFicheiro() << "." << endl;
		cout << "Tente mais tarde./n";
		return;
	}

	try{
		f_connections.open("subroads.txt");
		if (!f_connections.is_open())
			throw AberturaFalhada<string>("subroads.txt");
	}
	catch (AberturaFalhada<string> &a){
		cout << "Falha ao abrir o ficheiro " << a.getFicheiro() << "." << endl;
		cout << "Tente mais tarde.\n";
		return;
	}

	for(unsigned int it=0 ; it<ER.getStreets().size() ; it++){
		f_streets << ER.getStreets().at(it) << endl;
		for(unsigned int i=0; i<ER.getStreets().at(it).getVertices().size()/2; i++){
			f_connections << ER.getStreets().at(it).getID() << ";";
			f_connections << ER.getStreets().at(it).getVertices().at(i)->getInfo().getID() << ";";
			f_connections << ER.getStreets().at(it).getVertices().at(i+1)->getInfo().getID() << ";";
			f_connections << endl;
		}
	}

	f_connections.close();

	f_streets.close();

	return;
}
