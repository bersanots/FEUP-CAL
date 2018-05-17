#include "Sistema.h"

int Utente::lastId{0};


///////////////////////
//// CLASSE UTENTE ////
///////////////////////

Utente::Utente() : id(++lastId){
	this->bike = 0;
	this->nome = "";
}

Utente::Utente(string nome,Localizacao spot) : id(++lastId) {
	this->nome = nome;
	this->bike = 0;
	local = spot;
}

void Utente::alugaBicicleta(Bicicleta* b, Utilizacao ut) {
	setBike(b);
	setAvailable();
	addUse(ut);

	return;
}


Bicicleta* Utente::removeBicicleta() {
	Bicicleta* b = bike;
	setAvailable();
	setBike(0);
	return b;
}


void Utente::updateLocation(int index) {

	cout << "Localizacao atual: (" << getLocalizacao().getX() << " , " << getLocalizacao().getY();
	cout << ")" << endl << endl;

	cout << "Indique as novas coordenadas GPS:" << endl;

	string option{};
	double coordX{}, coordY{};

	while(1)
	{
		try{
			cout << endl << "Coordenada X [-90 , 90]: ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number_double(option) == false)
				throw OpcaoInvalida<string>(option);

			coordX = stod(option);

			if((coordX < -90) || (coordX > 90))
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

			if((coordX < -180) || (coordX > 180))
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

	Localizacao spot(coordX,coordY);

	setUtenteLocation(spot);

	cout << endl << "O utente encontra-se agora num novo local de coordenadas (" << coordX << " , " << coordY << ")" << endl << endl;

	return;
}


// METODOS GET //

int Utente::getLastId(){
	return lastId;
}

int Utente::getId() const {
	return id;
}

string Utente::getNome() const {
	return nome;
}

Localizacao Utente::getLocalizacao() const {
	return local;
}

Bicicleta* Utente::getBike() const {
	return bike;
}

bool Utente::getAvailable() const {
	return disponivel;
}

vector<Utilizacao> Utente::getHistorico(){
	return historico;
}


// METODOS SET //

void Utente::setLastId(){
	lastId--;
}

void Utente::setIDBackward() {
	this->id--;
}

void Utente::setID(int identificacao){
	id = identificacao;
}

void Utente::setUtenteLocation(Localizacao spot) {
	local = spot;
	return;
}

void Utente::setAvailable() {
	disponivel = !disponivel;
}

void Utente::setBike(Bicicleta* bike) {
	this->bike = bike;
}

void Utente::setHistoric(Utilizacao ut) {
	this->historico.push_back(ut);
}

void Utente::setNome(string nome){
	this->nome = nome;
}

void Utente::addUse(Utilizacao ut){
	historico.push_back(ut);
}

void Utente::displayHistoric(){
	if(historico.empty())
		cout << "Este utente ainda nao utilizou o servico" << endl << endl;
	else {
		cout << "Historico: " << endl << endl;

		for(unsigned int i = 0; i < historico.size(); i++)
		{
			historico.at(i).displayUtilizacao();
			cout << endl;
		}
	}
}
