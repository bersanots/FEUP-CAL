#include "Sistema.h"

int Utente::lastId = 0;


///////////////////////
//// CLASSE UTENTE ////
///////////////////////

/**
 * Construtor padrao da classe Utente.
 */
Utente::Utente() : id(++lastId){
	this->bike = 0;
	this->nome = "";
}

/**
 * Construtor da classe Utente.
 * @param nome nome do utente
 * @param spot localizacao atual do utente
 */
Utente::Utente(string nome,Localizacao spot) : id(++lastId) {
	this->nome = nome;
	this->bike = 0;
	local = spot;
}

/**
 * Atribui a bicicleta ao utente e remove-a do ponto de partilha mais proximo do utente.
 * @param b apontador para a bicicleta a alugar
 * @param ut utilizacao = aluger da bicicleta em questao
 */
void Utente::alugaBicicleta(Bicicleta* b, Utilizacao ut) {
	setBike(b);
	setAvailable();
	addUse(ut);

	return;
}

/**
// * Remove a bicicleta do utente e coloca-a no ponto de partilha, nao lotado, mais proximo do utente.
 * @param index_distancias vetor de indice dos pontos de partilha ordenados por distancia
 * @return Retorna um apontador para bicicleta que o utente possuia.
 */
Bicicleta* Utente::removeBicicleta(vector<int> index_distancias) {

	Bicicleta* b = bike;
	setAvailable();
	setBike(0);

	return b;
}

/**
 * Mostar a localizacao atual e extrai da stream de input a nova localizacao introduzida pelo utente
 * e chama o metodo setUtenteLocation que altera a localizacao.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e levantada uma excecao.
 * @param index indice do utente no vetor de utentes do sistema
 */
void Utente::updateLocation(int index) {

	cout << "Localizacao atual: (" << getLocalizacao().getX() << " , " << getLocalizacao().getY();
	cout << ")" << endl << endl;

	cout << "Indique as novas coordenadas GPS:" << endl;

	string option;
	double coordX, coordY;

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

/**
 * @return Retorna o identificador do ultimo utente criado.
 */
int Utente::getLastId(){
	return lastId;
}

/**
 * @return Retorna o identificador do utente.
 */
int Utente::getId() const {
	return id;
}

/**
 * @return Retorna o nome do utente.
 */
string Utente::getNome() const {
	return nome;
}

/**
 * @return Retorna localizacao do utente.
 */
Localizacao Utente::getLocalizacao() const {
	return local;
}

/**
 * Retorna um apontador para bicicleta que o utente esta a usar.
 * Caso nao esteja a usar uma bicicleta, o apontador tem o valor 0.
 * @return Retorna um apontador para bicicleta.
 */
Bicicleta* Utente::getBike() const {
	return bike;
}

/**
 * @return Retorna valor do atributo disponivel do utente.
 */
bool Utente::getAvailable() const {
	return disponivel;
}

/**
 * @return Retorna vetor de utilizacoes ja liquidadas do utente.
 */
vector<Utilizacao> Utente::getHistorico(){
	return historico;
}


// METODOS SET //

/**
 * Decrementa o numero de identificacao do ultimo utente.
 */
void Utente::setLastId(){
	lastId--;
}

/**
 * Decrementa o numero de identificacao do utente.
 */
void Utente::setIDBackward() {
	this->id--;
}

/**
 * Altera o numero de identificacao do utente.
 * @param identificacao novo numero de identificacao
 */
void Utente::setID(int identificacao){
	id = identificacao;
}

/**
 * Altera a localizacao do utente.
 * @param spot nova localizacao
 */
void Utente::setUtenteLocation(Localizacao spot) {
	local = spot;
	return;
}

/**
 * Coloca a disponibilidade do utente contraria a actual.
 */
void Utente::setAvailable() {
	disponivel = !disponivel;
}

/**
 * Atribui a bicicleta ao utente.
 * @param bike bicicleta que vai usar
 */
void Utente::setBike(Bicicleta* bike) {
	this->bike = bike;
}

/**
 * Acrescenta uma utilizcao ao historico do utente.
 * @param ut utilizacao a acrescentar
 */
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

}
