#include "Sistema.h"

/////////////////
// METODOS ADD //
/////////////////

void Sistema::addNewUtente() {

	mensagemInicial();

	cout << "Regista novo utente:" << endl << endl;

	string nome("");
	string option("");
	double coordX(0), coordY(0);

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

	Utente* u = new Utente{nome, spot};

	addNewUtente(u);

	cout << endl << "Utente #" << u->getId() << " registado com sucesso." << endl << endl;

	system("pause");
	system("cls");
	return;
}


void Sistema::addNewUtente(Utente* u1){
	utentes.push_back(u1);
}

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

void Sistema::getInfo() const{

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


vector<Utente* > Sistema::getUtentes() const{
	return utentes;
}

vector<PontoPartilha* > Sistema::getPontosPartilha() const {
	return pontosPartilha;
}

vector<Node> Sistema::getNodes() const{
	return nos;
}

vector<Street> Sistema::getStreets() const{
	return estradas;
}


vector<int> Sistema::getOrderedPP(int index) const {

	//Retorna um vector com os indices dos pontos de partilha organizados por ordem crescente de distancia ao utente com indice = index
	vector<double> distancias{};
	vector<int> indices{};


	return indices;
}


int Sistema::getUtenteIndex(int identificacao) const {

	for(unsigned int i = 0; i < utentes.size() ; i++)
	{
		if(utentes.at(i)->getId() == identificacao)
			return i;
	}

	return -1;
}


Data Sistema::getData() const{
	return dataAtual;
}


///////////////////
///////OTHERS//////
///////////////////

void Sistema::incData(){
	if(dataAtual.getDia()<31)
		dataAtual.setDia(dataAtual.getDia()+1);
	else{
		dataAtual.setMes(dataAtual.getMes()+1);
		dataAtual.setDia(1);
	}
}

void Sistema::criarGrafo(){
	for(unsigned int i=0; i<nos.size(); i++){
		grafo.addVertex(nos.at(i).getID());
	}
	for(unsigned int i=0; i<estradas.size(); i++)
		for(unsigned int j=0; j<estradas.at(i).getVertices().size()/2; j++){
			Node no1{estradas.at(i).getVertices().at(j)->getInfo()};
			Node no2{estradas.at(i).getVertices().at(j+1)->getInfo()};
			grafo.addEdge(no1.getID(),no2.getID(),no1.distanceTo(no2));
		}
}


void Sistema::alugaBike(int index) {
	if(!utentes.at(index)->getAvailable()){
		cout << "Ainda nao devolveu a bicicleta atual!" << endl << endl;
		return;
	}

	Localizacao l = utentes.at(index)->getLocalizacao();
	int id = closestPoint(l).getID();
	grafo.dijkstraShortestPath(id);

	Vertex<int> min = minDistance(false);
	string name;
	float dist;
	int idPP;

	if(min.getInfo()==0){
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
	string option;
	int value;

	if(dist!=0){
		cout << "O ponto mais proximo com bicicletas disponiveis para aluguer e o ponto: " << name;
		cout << ", que implica uma deslocacao de " << dist << " metros." << endl;

		while(1)
		{
			try {

				cout << endl << "Deseja prosseguir (Y/N)? ";
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

	while(1)
	{
		try {

			cout << endl << "Indique por quantas horas pretende alugar a bicicleta: ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value <= 0)
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

	Utilizacao ut(value, dataAtual, name);

	utentes.at(index)->alugaBicicleta(pontosPartilha.at(idPP)->removeBike(), ut);
	incData();
	cout << "Bicicleta alugada com sucesso no ponto " << name << endl << endl;
}


Node Sistema::closestPoint(Localizacao l) const{
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


Vertex<int> Sistema::minDistance(bool modo_devolve) const{
	double min=INF;
	int minIndex=0;
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
	return *grafo.getVertexSet().at(minIndex);
}

double Sistema::getDist(PontoPartilha p) const{
	for(unsigned int i=0; i< grafo.getVertexSet().size() ;i++){
		if(grafo.getVertexSet().at(i)->getInfo() == p.getID())
			return grafo.getVertexSet().at(i)->getDist();
	}
	return 0;
}


vector<pair<float,int>> Sistema::organizePair(bool modo_devolve) const{
	vector<pair<float,int > > idDist;
	for(unsigned int i=0; i<pontosPartilha.size(); i++){
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

pair<float, int> Sistema::bestChoice(bool modo_devolve) const{
	vector<pair<float, int> > idFactor = organizePair(modo_devolve);
	if(!idFactor.empty()){
		sort(idFactor.begin(), idFactor.end());
		return idFactor[0];
	}
	else
		return pair<float, int>(0,0);
}

pair<float, int> Sistema::cheapestPoint(bool modo_devolve) const{
	vector<pair<double,int>> cheap;
	for(unsigned int i=0; i<pontosPartilha.size(); i++){
		if(getDist(*pontosPartilha.at(i))!=INF && (!modo_devolve || !pontosPartilha.at(i)->isFull()))
			cheap.push_back(make_pair(pontosPartilha.at(i)->getPrice(), pontosPartilha.at(i)->getID()));
	}
	if(!cheap.empty()){
		sort(cheap.begin(), cheap.end());
		return cheap[0];
	}
	else
		return pair<float, int>(0,0);
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

	vector<int> res = grafo.getPath(12,1);
	for(auto v : res)
		cout << v << ";";
	res = grafo.getPath(36,14);
	for(auto v : res)
		cout << v << ";";

	if(min.getInfo()==0){
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
		cout << "Ja se encontra num ponto de partilha! Bicicleta devolvida com sucesso no Ponto de Partilha " << name1 << endl << endl;
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
	vector<int> a = grafo.getPath(id,g);

	return a;
}


void Sistema::pesquisaRuas() const{

	string st1="", st2="", option;
	int value;
	vector<Vertex<Node>*> v1, v2, common;
	vector<string> ruas;
	bool exists=false;

	for(unsigned int i=0; i<estradas.size(); i++)
		ruas.push_back(estradas.at(i).getName());

	cout << "Que tipo de pesquisa pretende?" << endl << endl;
	cout << "1  - Pesquisa exata de ruas" << endl;
	cout << "2  - Pesquisa aproximada de ruas" << endl;

	while(1)
	{
		try {

			cout << endl << "Introduza uma opcao (1/2): ";
			cin >> option;
			cin.ignore(1000,'\n');

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value!=1 && value!=2)
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

	while(!exists){
		cout << endl << "Introduza o nome da primeira rua: " << endl;
		getline(cin, st1);

		for(unsigned int i=0; i<estradas.size(); i++)
			if(estradas.at(i).getName()==st1){
				exists=true;
				v1 = estradas.at(i).getVertices();
			}

		if(!exists){
			cout << endl << "A rua indicada não existe!" << endl;
			if(value==1)
				findMinExact(st1,ruas);
			else
				findMinApproximate(st1,ruas);
		}
	}

	exists = false;

	while(!exists){
		cout << endl << "Introduza o nome da segunda rua: " << endl;
		getline(cin, st2);

		for(unsigned int i=0; i<estradas.size(); i++)
			if(estradas.at(i).getName()==st2){
				exists=true;
				v2 = estradas.at(i).getVertices();
			}

		if(!exists){
			cout << endl << "A rua indicada não existe!" << endl;
			if(value==1)
				findMinExact(st2,ruas);
			else
				findMinApproximate(st2,ruas);
		}

		if(st1==st2){
			cout << endl << "Escolha uma rua diferente da primeira!" << endl;
			exists=false;
		}
	}

	for(unsigned int i=0; i<v1.size(); i++)
		for(unsigned int j=0; j<v2.size(); j++)
			if(v1.at(i)->getInfo().getID()==v2.at(j)->getInfo().getID())
				common.push_back(v1.at(i));

	if(common.empty()){
		cout << endl << "As estradas indicadas não se cruzam!" << endl;
		return;
	}

	int indexPP=-1;

	for(unsigned int i=0; i<pontosPartilha.size(); i++)
		for(unsigned int j=0; j<common.size(); j++)
			if(pontosPartilha.at(i)->getID()==common.at(j)->getInfo().getID())
				indexPP=i;

	if(indexPP==-1)
		cout << endl << "Não existem Pontos de Partilha nos cruzamentos entre as duas ruas!" << endl;
	else
		cout << endl << "No cruzamento entre as duas ruas localiza-se o Ponto de Partilha " << pontosPartilha.at(indexPP)->getNome() << endl;

}
