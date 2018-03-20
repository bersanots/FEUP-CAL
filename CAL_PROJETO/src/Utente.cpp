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
 * @param ut utilizacao = aluguer da bicicleta em questao
 */
void Utente::alugaBicicleta(Bicicleta* b, Utilizacao ut) {
	setBike(b);
	setAvailable();
	addUse(ut);
	return;
}

/**
 * Remove a bicicleta do utente.
 * @return Retorna um apontador para a bicicleta que o utente possuia.
 */
Bicicleta* Utente::removeBicicleta() {
	Bicicleta* b = bike;
	setAvailable();
	setBike(0);
	return b;
}

/**
 * Mostra a localizacao atual e extrai da stream de input a nova localizacao introduzida pelo utente
 * e chama o metodo setUtenteLocation que altera a localizacao.
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e levantada uma excecao.
 * @param index indice do utente no vetor de utentes do sistema
 */
void Utente::updateLocation(int index) {

	cout << "Localização atual: (" << getLocalizacao().getX() << " , " << getLocalizacao().getY();
	cout << ")" << endl << endl;

	cout << "Indique as novas coordenadas GPS:" << endl;

	string option;
	double coordX { }, coordY { };

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

			if((coordX < -180) || (coordX > 180))
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

	Localizacao spot(coordX,coordY);

	setUtenteLocation(spot);

	cout << endl << "O utente encontra-se agora num novo local de coordenadas (" << coordX << " , " << coordY << ")" << endl << endl;

	return;
}

/**
 * Imprime no ecra o historico de compras do utente, apresentando o local da compra, a data,
 * o tipo de bicicleta, quantidade e o preco.
 */
void Utente::displayHistoricoCompras() {

	if(historicoCompras.size() == 0)
	{
		cout << "Este cliente ainda não efetuou nenhuma compra !" << endl << endl;
		return;
	}

	cout << "Histórico de compras:" << endl << endl;

	for(unsigned int i = 0; i < historicoCompras.size(); i++)
	{
		cout << "Local da compra: " << historicoCompras.at(i).getLocation() << endl;
		cout << "Data (DD:MM:AAAA): " << historicoCompras.at(i).getData().getDia() << "/" << historicoCompras.at(i).getData().getMes() << "/"
				<<  historicoCompras.at(i).getData().getAno() << endl;
		cout << "Tipo de bicicleta: " << historicoCompras.at(i).getBikeType() << endl;
		cout << "Quantidade: " << historicoCompras.at(i).getUseTime() << endl;
		cout << "Preço: ";

		if(historicoCompras.at(i).getBikeType() == "Urbana")
			cout << 150*historicoCompras.at(i).getUseTime() << "€" << endl << endl;
		else if(historicoCompras.at(i).getBikeType() == "Urbana Simples")
			cout << 200*historicoCompras.at(i).getUseTime() << "€" << endl << endl;
		else if(historicoCompras.at(i).getBikeType() == "Corrida")
			cout << 250*historicoCompras.at(i).getUseTime() << "€" << endl << endl;
		else
			cout << 100*historicoCompras.at(i).getUseTime() << "€" << endl << endl;
	}
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
 * Retorna um apontador para a bicicleta que o utente esta a usar.
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
vector<Utilizacao> Utente::getHistorico() const{
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
 * Acrescenta uma utilizacao ao historico do utente.
 * @param ut utilizacao a acrescentar
 */
void Utente::setHistoric(Utilizacao ut) {
	this->historico.push_back(ut);
}

/**
 * Acrescenta uma compra ao historico do utente.
 * @param info compra a acrescentar
 */
void Utente::setHistoricoCompras(Utilizacao info) {
	historicoCompras.push_back(info);
}

//////////////////////
//// CLASSE SOCIO ////
//////////////////////

/**
 * Construtor padrao da subclasse Socio.
 */
Socio::Socio() : Utente{}
{}

/**
 * Construtor da subclasse Socio.
 * @param nome nome do utente
 * @param spot localizacao atual do utente
 */
Socio::Socio(string nome,Localizacao spot) : Utente{nome, spot} {}

/**
 * Paga a mensalidade do mes selecionado, removendo as utilizacoes correspondentes a esse mes do vetor utilizacoes
 * e colocando-as no historico do utente.
 * @param ano do qual pretende pagar um mes
 * @param mes que pretende pagar
 */
void Socio::pagaMensalidade(unsigned int ano, unsigned int mes) {

	unsigned int numUseHours{0};
	double prestacao{-1};
	string mesName;

	for(unsigned int i = 0; i < utilizacoes.size(); i++)
	{
		if((utilizacoes.at(i).getData().getAno() == ano) && (utilizacoes.at(i).getData().getMes() == mes))
		{
			//Soma as horas de uso do respetivo mes
			numUseHours += utilizacoes.at(i).getUseTime();

			//Verifica o tipo de prestação a ser aplicada
			unsigned int tmp{};


			if(utilizacoes.at(i).getBikeType() == "Urbana")
				tmp = 40;
			else if(utilizacoes.at(i).getBikeType() == "Urbana Simples")
				tmp = 30;
			else if(utilizacoes.at(i).getBikeType() == "Corrida")
				tmp = 50;
			else
				tmp = 20;

			if(prestacao < tmp)
				prestacao = tmp;

			//Adiciona utilização ao histórico e remove-a das utilizações
			historico.push_back(utilizacoes.at(i));
			utilizacoes.erase(utilizacoes.begin() + i);
			i--;

		}
	}

	string monthNames[] = {"Janeiro","Fevereiro","Março","Abril", "Maio", "Junho",
			"Julho", "Agosto","Setembro","Outubro","Novembro", "Dezembro"};

	mesName = monthNames[mes-1];

	cout << "Montante a pagar referente ao mês " << mesName << " do ano " << ano << ": ";

	if(numUseHours >= 20)
		prestacao = prestacao*0.9;

	cout << prestacao << "€" << endl << endl;

	return;
}

/**
 * Imprime no ecra o historico do Utente Socio.
 */
void Socio::displayHistoric() const{

	if(historico.empty())
		cout << "Este utente ainda não utilizou o serviço ou então possui pagamentos pendentes" << endl << endl;
	else {
		cout << "Histórico: " << endl << endl;

		for(unsigned int i = 0; i < historico.size(); i++)
		{
			historico.at(i).displayUtilizacao();
			cout << endl;
		}
	}

	return;
}

/**
 * Imprime no ecra as utilizacoes por pagar do utente.
 * Esta opcao e apenas para socios. Se um utente regular acede a esta opcao,
 * e-lhe apresentada uma mensagem.
 * @param index indice do utente no vetor de utentes do sistema
 */
void Socio::displayPagPendentes(int index){

	if(utilizacoes.size() != 0)
	{
		cout << "Pagamentos pendentes:" << endl << endl;

		for(unsigned int i = 0; i < utilizacoes.size(); i++)
		{
			utilizacoes.at(i).displayUtilizacao();
			cout << endl;
		}
	}
	else
	{
		cout << "Este utente não possui qualquer pagamento pendente" << endl << endl;
	}

	return;
}

/**
 * Efetua o pagamento de mensalidades, para tal, sera impresso no ecra os anos que contem utilizacoes
 * por saldar, e depois do utente selecionar o ano, e-lhe apresentado os meses que tem em divida;
 * depois de selecionar chama-se o metodo da subclasse Socio pagaMensalidade que calcula a mensalidade
 * consoante o numero de horas de uso nesse mes (desconto) e consoante o tipo de bicicletas alugadas
 * (ver tabela de mensalidades (infoER)).
 * Para cada introducao do utente e verificado se o mesmo introduziu o formato de dados pedido
 * e se os dados sao validos, caso contrario e impressa uma mensagem e levantada uma excecao.
 * @param index indice do utente no vetor de utentes do sistema
 */
void Socio::efetuaPag(int index){

	cout << "Efetua pagamento" << endl << endl;

	unsigned int ano{}, mes{};
	string option {};
	vector<unsigned int> meses;
	vector<unsigned int> anos;

	if(disponivel == false)
	{
		cout << "Não é possível efetuar o pagamento uma vez que a bicicleta alugada ainda não foi devolvida" << endl << endl;
		return;
	}

	else if(utilizacoes.size() == 0){
		cout << "Este utente não possui qualquer pagamento pendente" << endl << endl;
		return;
	}

	//Verifica os anos com mensalidades em atraso
	for(unsigned int i = 0; i < utilizacoes.size(); i++)
	{
		if(anos.size() == 0)
			anos.push_back(utilizacoes.at(i).getData().getAno());

		bool cond {false};
		for(unsigned int k = 0; k < anos.size(); k++)
		{
			if(anos.at(k) == utilizacoes.at(i).getData().getAno()) {
				cond = true;
				break;
			}
		}
		if(cond == false)
			anos.push_back(utilizacoes.at(i).getData().getAno());

		cond = false;
	}

	//Organiza o vetor "anos" por ordem crescente
	sort(anos.begin(),anos.end());

	cout << "Anos com mensalidades em atraso: " << endl;
	for(unsigned int i = 0; i < anos.size(); i++)
	{
		cout << "-> " << anos.at(i) << endl;
	}

	cout << endl;

	//Executa até obter um ano válido
	while(1)
	{
		try{
			cout << "Liquidação de mensalidades do ano: ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			ano = stoi(option);
			if(ano < 2017)
				throw OpcaoInvalida<int>(ano);

			cout << endl;
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

	//Verifica meses de utilização do respetivo ano
	for(unsigned int i = 0; i < utilizacoes.size(); i++)
	{
		if(utilizacoes.at(i).getData().getAno() == ano)
		{
			if(meses.size() == 0)
				meses.push_back(utilizacoes.at(i).getData().getMes());

			bool cond {false};
			for(unsigned int k = 0; k < meses.size(); k++)
			{
				if(meses.at(k) == utilizacoes.at(i).getData().getMes())
					cond = true;
			}

			if(cond == false)
				meses.push_back(utilizacoes.at(i).getData().getMes());

			cond = false;
		}
	}

	string monthNames[] = {"Janeiro","Fevereiro","Março","Abril", "Maio", "Junho",
			"Julho", "Agosto","Setembro","Outubro","Novembro", "Dezembro"};

	cout << "Meses com mensalidades em atraso: " << endl;

	for(unsigned int i = 0; i < meses.size(); i++)
	{
		cout << meses.at(i) << " - " << monthNames[meses.at(i)-1] << endl;
	}

	cout << endl;

	//Executa até obter um ano válido
	while(1)
	{
		try{
			cout << "Liquidação de mensalidades do mês: ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			mes = stoi(option);

			bool cond {false};

			for(unsigned int i = 0; i < meses.size(); i++)
			{
				if(meses.at(i) == mes)
				{
					cond = true;
					break;
				}
			}

			if(cond == false)
				throw OpcaoInvalida<int>(mes);

			cout << endl;
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


	pagaMensalidade(ano,mes);

	return;
}

/**
 * @return Retorna false se o vetor utilizacoes esta vazio, caso contrario, retorna true.
 */
bool Socio::hasPendingPay() {
	return utilizacoes.size() > 0;
}

/**
 * Adiciona uma utilizacao ao vetor utilizacoes do Socio.
 * @param use nova utilizacao
 */
void Socio::addUse(Utilizacao use) {
	utilizacoes.push_back(use);
	return;
}


// METODOS GET //

/**
 * @return Retorna vetor de utilizacoes por pagar do utente.
 */
vector<Utilizacao> Socio::getUtilizacoes() const {
	return utilizacoes;
}

/**
 * @return Retorna a ultima utlilizacao do vetor utilizacoes.
 */
Utilizacao Socio::getLastUse() {
	return utilizacoes.back();
}

/**
 * @return Retorna o tipo do utente (socio).
 */
string Socio::getTipoUtente() const {
	return "Socio";
}


////////////////////////
//// CLASSE REGULAR ////
////////////////////////

/**
 * Construtor padrao da classe Regular.
 */
Regular::Regular() : Utente{} {}

/**
 * Construtor da subclasse Regular.
 * @param nome nome do utente
 * @param spot localizacao atual do utente
 */
Regular::Regular(string nome,Localizacao spot) : Utente{nome, spot} {}

/**
 * Imprime no ecra o historico do utente Regular e tambem e apresentado o total pago por cada utilizacao.
 */
void Regular::displayHistoric() const{

	if(historico.empty())
		cout << "Este utente ainda não utilizou o serviço." << endl << endl;
	else {
		cout << "Histórico: " << endl << endl;

		for(unsigned int i = 0; i < historico.size(); i++)
		{
			historico.at(i).displayUtilizacao();
			cout << "Montante: " << historico.at(i).getPrice() << "€" << endl << endl;
		}
	}

	return;
}

/**
 * Imprime no ecra uma mensagem quando chamada para este tipo (Regular), porque o mesmo
 * nao tem pagamentos pendentes.
 * @param index indice do utente no vetor de utentes do sistema
 */
void Regular::displayPagPendentes(int index){

	cout << "Neste tipo de utente [Regular] não é possível ter pagamentos pendentes !" << endl << endl;

	return;
}

/**
 * Imprime no ecra a uma mensagem quando chamada para este tipo (Regular), porque o mesmo
 * nao tem pagamentos pendentes, logo nao pode efetuar pagamento.
 * @param index indice do utente no vetor de utentes do sistema
 */
void Regular::efetuaPag(int index){

	cout << "Efetua pagamento" << endl << endl;

	cout << "O pagamento já foi feito na altura do aluguer!" << endl << endl;

	return;
}

/**
 * @return Retorna false visto nao ter utilizacoes com pagamentos pendentes.
 */
bool Regular::hasPendingPay() {
	return false;
}

/**
 * Adiciona uma utilizacao ao vetor historico do Utente Regular.
 * @param use nova utilizacao
 */
void Regular::addUse(Utilizacao use) {
	historico.push_back(use);
}


// METODOS GET //

/**
 * @return Retorna o tipo do utente (regular).
 */
string Regular::getTipoUtente() const {
	return "Regular";
}

/**
 * @return Retorna a ultima utilizacao do utente Regular.
 */
Utilizacao Regular::getLastUse() {
	return historico.back();
}
