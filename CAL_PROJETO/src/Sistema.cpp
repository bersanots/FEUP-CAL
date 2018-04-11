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
/*void Sistema::addPontoPartilha() {

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
				cout << "Ja existe um Ponto de Partilha nessa localizacao!" << endl << endl;
				break;
			}
		}

	}while(newcord == false);

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

	addPontoPartilha(new PontoPartilha{spot,value,nome,});

	for(unsigned int i = 0; i < 5; i++)
	{
		pontosPartilha.at(pontosPartilha.size() - 1)->adicionaBike(new Bicicleta{""});
	}


	cout << endl << "Novo ponto de partilha adicionado ao sistema" << endl << endl;

	return;
}*/

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

void Sistema::addNode(Node n){
	nos.push_back(n);
}


void Sistema::addStreet(Street st){
	estradas.push_back(st);
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
	cout << setw (20) << left << "Nome" << setw (13) << "GPS" << setw (10) << "Altitude" << setw (13) << "Capacidade" << setw (13) << "Num Bicicletas" << endl;

	for (unsigned int i=0 ; i<pontosPartilha.size() ; i++){
		cout << setw(10) << pontosPartilha.at(i)->getNome();
		cout << '(' << setw(9) << pontosPartilha.at(i)->getLocal().getX();
		cout << "," << setw(9) << pontosPartilha.at(i)->getLocal().getY() << setw(6) << ')';
		cout << setw(10) << pontosPartilha.at(i)->getAltitude();
		cout << setw(15) << pontosPartilha.at(i)->getCapacidade();
		cout << pontosPartilha.at(i)->getBikes().size();
		cout << endl;
	}

	cout << endl;

	cout << "Numero total de utentes registados: " << utentes.size() << endl << endl;

	displayUtentes();

	cout << endl;

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

vector<Node> Sistema::getNodes() const{
	return nos;
}

vector<Street> Sistema::getStreets() const{
	return estradas;
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


void Sistema::criarGrafo(){
	for(unsigned int i=0; i<nos.size(); i++){
		//nos.at(i).setID(i);
		grafo.addVertex(nos.at(i).getID());
	}
	for(unsigned int i=0; i<estradas.size(); i++)
		for(unsigned int j=0; j<estradas.at(i).getVertices().size()/2; j++){
			Node no1{estradas.at(i).getVertices().at(j)->getInfo()};
			Node no2{estradas.at(i).getVertices().at(j+1)->getInfo()};
			grafo.addEdge(no1.getID(),no2.getID(),no1.distanceTo(no2));
		}
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

/**
 * Apresenta a informacao do aluger e chama-se o metodo da classe utente removeBicicleta
 * e o metodo adicionaBike da classe pontoPartilha para remover a bicicleta do utente e
 * coloca-la no ponto de partilha.
 * A devolucao e feita no ponto de partilha mais proximo do utente.
 * No final, chama a funcao Sistem_Manager para gerir as bicicletas.
 * @param index indice do utente no vetor de utentes do sistema
 */
void Sistema::alugaBike(int index) {
	if(!utentes.at(index)->getAvailable()){
		cout << "Ainda nao devolveu a bicicleta atual!" << endl << endl;
		return;
	}

	Localizacao l = utentes.at(index)->getLocalizacao();
	int id = closestPoint(l).getID();
	grafo.dijkstraShortestPath(id);

	Vertex<int> min = minDistance(true);
	string name;
	float dist;
	int idPP;

	if(min.getInfo()==NULL){
		cout << "[Os pontos encontram-se todos cheios ou nao sao alcancaveis, tente mais tarde!]" << endl;
		return;
	}

	for(unsigned int i=0; i<pontosPartilha.size(); i++)
		if(pontosPartilha.at(i)->getID()==min.getInfo()){
			idPP = i;
			name = pontosPartilha.at(i)->getNome();
		}

	dist = min.getDist()*1000;

	Data d;
	Utilizacao ut(0, d, name);
	string option;

	if(dist!=0){
		cout << "O ponto mais proximo com bicicletas disponiveis para aluguer e o ponto: " << name;
		cout << ", que implica uma deslocacao de " << dist << " metros." << endl;

		while(1)
		{
			try {

				cout << endl << "Deseja prosseguir (Y/N)?";
				cin >> option;
				cin.ignore(1000,'\n');

				if(option!="Y" && option!="N")
					throw OpcaoInvalida<string>(option);

				break;
			}
			catch (OpcaoInvalida<string> &op){

				cout << "Opcao invalida(" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
		};

		Localizacao locpp(pontosPartilha.at(idPP)->getLongitude(), pontosPartilha.at(idPP)->getLatitude());

		if(option=="Y"){
			utentes.at(index)->setUtenteLocation(locpp);
		}else{
			cout << "Operacao cancelada com sucesso!" << endl << endl;
			return;
		}
	}

	utentes.at(index)->alugaBicicleta(pontosPartilha.at(idPP)->removeBike(), ut);
	cout << "Bicicleta alugada com sucesso no ponto " << name << endl << endl;
}

Node Sistema::closestPoint(Localizacao l){
	double minDist=INF;
	Node currentNode(0,l.getX(),l.getY()), minNode;
	for(unsigned int i=0; i<nos.size(); i++){
		if(nos.at(i).distanceTo(currentNode)<minDist){
			minDist=nos.at(i).distanceTo(currentNode);
			minNode = nos.at(i);
		}
	}
	return minNode;
}

Vertex<int> Sistema::minDistance(bool modo_devolve){
	double min=INF;
	unsigned int minIndex=-1;
	bool isvalidPP;	//verifica se existe um ponto de partilha no vertice
	for(int i=0; i<grafo.getNumVertex(); i++){
		isvalidPP=false;
		for(unsigned int j=0; j<pontosPartilha.size(); j++)
			if(pontosPartilha.at(j)->getID()==grafo.getVertexSet().at(i)->getInfo() && (!modo_devolve || !pontosPartilha.at(j)->isFull()))
				isvalidPP=true;
		if(grafo.getVertexSet().at(i)->getDist()<min && isvalidPP){
			min=grafo.getVertexSet().at(i)->getDist();
			minIndex=i;
		}
	}
	if(minIndex==-1)
		return Vertex<int>(NULL);
	return *grafo.getVertexSet().at(minIndex);
}

double Sistema::getDist(PontoPartilha p){
	for(int i=0; i< grafo.getVertexSet().size() ;i++){
		if(grafo.getVertexSet().at(i)->getInfo() == p.getID())
			return grafo.getVertexSet().at(i)->getDist();
	}
	return 0;
}


vector<pair<float,int>> Sistema::organizePair(bool modo_devolve){
	vector<pair<float,int > > idDist;
	for(int i=0; i<pontosPartilha.size(); i++){
		float factor=0;
		int id = pontosPartilha.at(i)->getID();
		double d = getDist(*pontosPartilha.at(i));
		double price = pontosPartilha.at(i)->getPrice();
		factor = price * d;
		if(getDist(*pontosPartilha.at(i))!=INF && (!modo_devolve || !pontosPartilha.at(i)->isFull()))
			idDist.push_back(make_pair(factor,id));
	}
	return idDist;
}

pair<float, int> Sistema::bestChoice(bool modo_devolve){
	vector<pair<float, int> > idFactor = organizePair(modo_devolve);
	if(!idFactor.empty()){
		sort(idFactor.begin(), idFactor.end());
		return idFactor[0];
	}
	else
		return pair<float, int>(NULL,NULL);
}

pair<float, int> Sistema::cheapestPoint(bool modo_devolve){
	vector<pair<double,int>> cheap;
	for(int i=0; i<pontosPartilha.size(); i++){
		if(getDist(*pontosPartilha.at(i))!=INF && (!modo_devolve || !pontosPartilha.at(i)->isFull()))
			cheap.push_back(make_pair(pontosPartilha.at(i)->getPrice(), pontosPartilha.at(i)->getID()));
	}
	if(!cheap.empty()){
		sort(cheap.begin(), cheap.end());
		return cheap[0];
	}
	else
		return pair<float, int>(NULL,NULL);
}

void Sistema::devolveBike(int index) {
	if(utentes.at(index)->getAvailable()){
		cout << "Ainda nao alugou uma bicicleta!" << endl << endl;
		return;
	}

	Localizacao l = utentes.at(index)->getLocalizacao();
	int id = closestPoint(l).getID();
	grafo.dijkstraShortestPath(id);

	Vertex<int> min = minDistance(true);
	string name1, name2, name3;
	int idPP1, idPP2, idPP3;
	float price, dist;

	if(min.getInfo()==NULL){
		cout << "[Os pontos encontram-se todos cheios ou nao sao alcancaveis, tente mais tarde!]" << endl;
		return;
	}

	//----- POR DISTANCIA ----- //
	for(unsigned int i=0; i<pontosPartilha.size(); i++){
		if(pontosPartilha.at(i)->getID()==min.getInfo()){
			idPP1=i;
			name1 = pontosPartilha.at(i)->getNome();
			price=trunc(100 * pontosPartilha.at(i)->getPrice()) / 100;
		}
	}
	dist = min.getDist()*1000;

	if(dist==0){
		pontosPartilha.at(idPP1)->adicionaBike(utentes.at(index)->removeBicicleta());
		cout << "Bicicleta devolvida com sucesso no Ponto de Partilha " << name1 << endl << endl;
		return;
	}

	cout << "PONTO DE ENTREGA MAIS PROXIMO: " << name1;
	cout << " [DISTANCIA: " << dist << " metros  |  PRECO: " << price << " euro(s)]" << endl;


	//----- POR PRECO ----- //
	for(unsigned int i=0; i<pontosPartilha.size(); i++){
		if(pontosPartilha.at(i)->getID()==cheapestPoint(true).second){
			idPP2=i;
			name2 = pontosPartilha.at(i)->getNome();
			price=trunc(100 * cheapestPoint(true).first) / 100;
			dist=getDist(*pontosPartilha.at(i))*1000;
		}
	}

	cout << "PONTO DE ENTREGA MAIS BARATO: " << name2;
	cout << " [DISTANCIA: " << dist << " metros  |  PRECO: " << price << " euro(s)]" << endl;


	//----- POR RELACAO PRECO/DISTANCIA ----- //
	for(unsigned int i=0; i<pontosPartilha.size(); i++){
		if(pontosPartilha.at(i)->getID()==bestChoice(true).second){
			idPP3=i;
			name3 = pontosPartilha.at(i)->getNome();
			price=trunc(100 * bestChoice(true).first/getDist(*pontosPartilha.at(i))) / 100;
			dist=getDist(*pontosPartilha.at(i))*1000;
		}
	}

	cout << "PONTO DE ENTREGA MAIS EM CONTA (considerando altitude, preco e distancia): " << name3;
	cout << " [DISTANCIA: " << dist << " metros  |  PRECO: " << price << " euro(s)]" << endl;

	string option{};
	int value{};

	cout << endl << endl << "Opcoes para devolucao de bicicleta:" << endl << endl;
	cout << "1  - Ponto de entrega mais proximo" << endl;
	cout << "2  - Ponto de entrega mais barato" << endl;
	cout << "3  - Ponto de entrega mais em conta" << endl;
	cout << "4  - Cancelar" << endl << endl;

	while(1)
	{
		try {

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

	switch (value)
	{
	case 1:
		pontosPartilha.at(idPP1)->adicionaBike(utentes.at(index)->removeBicicleta());
		cout << "Bicicleta devolvida com sucesso no Ponto de Partilha " << name1 << endl << endl;
		break;
	case 2:
		pontosPartilha.at(idPP2)->adicionaBike(utentes.at(index)->removeBicicleta());
		cout << "Bicicleta devolvida com sucesso no Ponto de Partilha " << name2 << endl << endl;
		break;
	case 3:
		pontosPartilha.at(idPP3)->adicionaBike(utentes.at(index)->removeBicicleta());
		cout << "Bicicleta devolvida com sucesso no Ponto de Partilha " << name3 << endl << endl;
		break;
	case 4:
		cout << "Operacao cancelada com sucesso!" << endl << endl;
		break;
	}
}


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
				pontosPartilha.at(indicesSup5.at(k))->removeBike();
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
				pontosPartilha.at(index)->removeBike();
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

vector<int> Sistema::path_rentavel(double client) {
	Localizacao L(utentes.at(client)->getLocalizacao());
	double g = bestChoice(true).second;
	double id = closestPoint(L).getID();
	vector<int> a =grafo.getPath(id,g);

	return a;

}
