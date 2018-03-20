#include "Oficina.h"
#include "Excecoes.h"

/////////////////
// METODOS GET //
/////////////////

/**
 * @return Retorna o vetor de apontadores das bicicletas que estao na oficina para reparacao
 */
vector<Bicicleta *> Oficina::getBrokenBikes() const {
	return brokenBikes;
}

/////////////////
// METODOS SET //
/////////////////

/**
 * Altera o vetor de apontadores de bicicletas avariadas
 * @param newBrokenBikes novo vetor de bicicletas avariadas
 */
void Oficina::setBrokenBikes(vector<Bicicleta *> newBrokenBikes) {
	brokenBikes = newBrokenBikes;
}

/////////////////
// METODOS ADD //
/////////////////

/**
 * Adiciona uma bicicleta avariada na lista para reparacao
 * @param bike apontador da bicicleta a adicionar
 */
void Oficina::addBrokenBike(Bicicleta * bike) {
	brokenBikes.push_back(bike);
}

/**
 * Adiciona uma peca a lista de pecas.
 * Pede ao utilizador para escolher o tipo de peca a adicionar, escrever o fornecedor e verifica
 * se ja existe alguma peca desse tipo com o mesmo fornecedor.
 * Caso se verifique o utilizador e indicado da situacao senao, a peca e adicionada a BST.
 * Para cada introducao do utilizador e verificado se o mesmo introduziu o formato de dados pedido.
 */
void Oficina::addPiece() {

	cout << "Adiciona pe�a: " << endl << endl;

	string piece,option,nome;
	int value {};
	vector<string> piecesAvailable;

	piecesAvailable.push_back("Pneu"); piecesAvailable.push_back("Corrente"); piecesAvailable.push_back("Pedais");
	piecesAvailable.push_back("Guiador"); piecesAvailable.push_back("Assento"); piecesAvailable.push_back("Cremalheira");
	piecesAvailable.push_back("Punhos"); piecesAvailable.push_back("Trav�o"); piecesAvailable.push_back("Amortecedor");
	piecesAvailable.push_back("Roda");

	//Mostra as pe�as possiveis para se adicionarem a BST
	cout << "Pe�as disponiveis: " << endl;

	for(unsigned int i = 0; i < piecesAvailable.size(); i++)
		cout << left << setw(2) << (i+1) << " -> " << piecesAvailable.at(i) << endl;

	//Seleciona uma das pe�as
	while(1)
	{
		try {
			cout << endl << "Pe�a (1-10): ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value < 1 || value > 10)
				throw OpcaoInvalida<int>(value);

			piece = piecesAvailable.at(value - 1);
			break;
		}
		catch (OpcaoInvalida<int> &op){
			cout << "Pe�a inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		catch (OpcaoInvalida<string> &op){
			cout << "Pe�a inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};

	cin.ignore(1000,'\n');

	do
	{
		BSTItrIn<Peca> it(pieces);
		bool exist {false};

		//Verifica o nome do fornecedor da respetiva pe�a
		while(1)
		{
			try {
				cout << endl << "Nome do fornecedor: " ;
				getline(cin,nome);

				if((valid_word(nome) == false) || (nome.empty()))
					throw OpcaoInvalida<string>(nome);

				break;
			}
			catch (OpcaoInvalida<string> &op) {
				cout << "Nome do fornecedor inv�lido(" << op.opcao << ") ! Tente novamente." << endl;
				cin.clear();
			}
		}

		//Procura na BST o respetivo fornecedor, se ja existir verifica se este ja tem a pe�a,

		while(!it.isAtEnd())
		{
			if(it.retrieve().getSupplier() == nome)
			{
				if(it.retrieve().getPieceType() == piece){
					exist = true;
					break;
				}
			}
			it.advance();
		}

		if(exist == false)
			break;
		else
			cout << "J� existe um fornecedor " << nome << " a vender pe�as do tipo " << piece << " ! Tente novamente." << endl;


	}while(1);

	//Adiciona a nova pe�a
	pieces.insert(Peca(0,piece,nome));

	cout << endl << "Pe�a adicionada com sucesso !" << endl << endl;
}

////////////////////
// METODOS REMOVE //
////////////////////

/**
 * Remove uma peca da lista de pecas.
 * Pede ao utilizador para escolher o tipo de peca a remover, das existentes, e escolher o fornecedor
 * da lista apresentada.
 * Para cada introducao do utilizador e verificado se o mesmo introduziu o formato de dados pedido.
 */
void Oficina::removePieceBST() {

	BSTItrIn<Peca> it(pieces);

	if(it.isAtEnd())
	{
		cout << "N�o existem pe�as para serem removidas " << endl << endl;
		return;
	}

	cout << "Remove pe�a: " << endl << endl;

	string piece,option,nome;
	int value {};
	vector<string> piecesAvailable, toRemove, suppliers;

	piecesAvailable.push_back("Pneu"); piecesAvailable.push_back("Corrente"); piecesAvailable.push_back("Pedais");
	piecesAvailable.push_back("Guiador"); piecesAvailable.push_back("Assento"); piecesAvailable.push_back("Cremalheira");
	piecesAvailable.push_back("Punhos"); piecesAvailable.push_back("Trav�o"); piecesAvailable.push_back("Amortecedor");
	piecesAvailable.push_back("Roda");

	//Guarda as pe�as possiveis a serem removidas da BST
	for(unsigned int i = 0; i < piecesAvailable.size(); i++)
	{
		BSTItrIn<Peca> search(pieces);

		while(!search.isAtEnd())
		{
			if(search.retrieve().getPieceType() == piecesAvailable.at(i)){
				toRemove.push_back(search.retrieve().getPieceType());
				break;
			}
			search.advance();
		}
	}

	//Mostra as pe�as possiveis para remocao
	cout << "Pe�as possiveis para remo��o: " << endl;

	for(unsigned int i = 0; i < toRemove.size(); i++)
		cout << i+1 << " -> " << toRemove.at(i) << endl;

	//Seleciona uma das pe�as
	while(1)
	{
		try {
			cout << endl << "Pe�a (1-" << toRemove.size() << "): ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value < 1 || value > (int)toRemove.size())
				throw OpcaoInvalida<int>(value);

			piece = toRemove.at(value - 1);

			break;
		}
		catch (OpcaoInvalida<int> &op){
			cout << "Pe�a inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		catch (OpcaoInvalida<string> &op){
			cout << "Pe�a inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};


	//Mostra se possivel as pe�as associadas aos fornecedores que podem ser removidas
	while(!it.isAtEnd())
	{
		if(it.retrieve().getPieceType() == piece)
			suppliers.push_back(it.retrieve().getSupplier());

		it.advance();
	}

	if(suppliers.size() == 0)
	{
		cout << "N�o existem pe�as do tipo " << piece << " dispoveis para serem removidas !" << endl << endl;
		return;
	}

	system("cls");
	mensagemInicial();

	cout << "Remove pe�a: " << endl << endl;
	cout << "Pe�a: " << piece << endl << endl;
	cout << "Fornecedores: " << endl;

	for(unsigned int i = 0; i < suppliers.size(); i++)
		cout << (i+1) << " -> " << suppliers.at(i) << endl;

	//Seleciona a pe�a associada ao fornecedor X a ser removida
	while(1)
	{
		try {
			cout << endl << "Pe�a (1-" << suppliers.size() << "): ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value < 1 || value > (int)suppliers.size())
				throw OpcaoInvalida<int>(value);

			nome = suppliers.at(value - 1);

			break;
		}
		catch (OpcaoInvalida<int> &op){
			cout << "Pe�a inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		catch (OpcaoInvalida<string> &op){
			cout << "Pe�a inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};

	//Remove a pe�a
	BSTItrIn<Peca> iterator(pieces);
	BST<Peca> tmp = pieces; tmp.makeEmpty();

	while(!iterator.isAtEnd())
	{
		if((iterator.retrieve().getPieceType() == piece) && (iterator.retrieve().getSupplier() == nome)) {}
		else
			tmp.insert(iterator.retrieve());

		iterator.advance();
	}
	pieces = tmp;
	cout << endl << "Pe�a do tipo " << piece << " fornecida por " << nome << " removida com sucesso !" << endl << endl;
}

/**
 * Remove a piece da lista de avarias da bicicleta, isto e, repara a avaria
 * "piece" da bicicleta.
 * @param index indice da bicicleta em reparacao
 * @param piece	peca reparada
 */
void Oficina::removePieceBike(int index, string piece) {

	vector<string> avarias;

	for(unsigned int i = 0; i < brokenBikes.at(index)->getAvarias().size(); i++)
	{
		if(brokenBikes.at(index)->getAvarias().at(i) != piece)
			avarias.push_back(brokenBikes.at(index)->getAvarias().at(i));
	}

	brokenBikes.at(index)->setAvarias(avarias);
}


////////////
// OTHERS //
////////////

/**
 * Compra uma peca para reparar uma bicicleta avariada.
 * Pede ao utlizador para escolher uma bicicleta para reparar, da lista apresentada, escolher a peca
 * que pretende reparar, da lista apresentada, escolher o fornecedor, e ainda e pedido para inserir
 * o preco da peca que pretende comprar. Se existir a peca com o fornecedor selecionados na BST da
 * oficina, o preco dessa peca e atualizado, senao e inserida uma nova peca.
 * Para cada introducao do utilizador e verificado se o mesmo introduziu o formato de dados pedido.
 */
void Oficina::buyPiece() {

	cout << "Compra pe�a:" << endl << endl;

	if(brokenBikes.size() == 0)
	{
		cout << "Neste momento n�o � poss�vel comprar pe�as visto que n�o existem bicicletas avariadas !" << endl << endl;
		return;
	}

	string option, piece, nome;
	int value {}, indicator {};

	cout << "Bicicletas avariadas: " << endl;

	for(unsigned int i = 0; i < brokenBikes.size(); i++)
		cout << (i+1) << " -> " << brokenBikes.at(i)->getBikeName() << endl;

	//Seleciona uma das bicicletas avariadas
	while(1)
	{
		try {

			cout << endl << "Selecione uma bicicleta (1-" << brokenBikes.size() << "): ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value < 1 || value > (int)brokenBikes.size())
				throw OpcaoInvalida<int>(value);

			indicator = value - 1;

			break;
		}
		catch (OpcaoInvalida<int> &op){

			cout << "Bicicleta inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Bicicleta inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};

	system("cls");
	mensagemInicial();
	cout << "Compra pe�a:" << endl << endl;

	//Mostra informa��o relativa a bicicleta selecionada
	cout << "Pe�as possiveis para compra: " << endl;

	for(unsigned int i = 0; i < brokenBikes.at(indicator)->getAvarias().size(); i++)
		cout << (i+1) << " -> " << brokenBikes.at(indicator)->getAvarias().at(i) << endl;

	//Seleciona uma pe�a para compra de modo a compor a mesma relativa a bicicleta selecionada
	while(1)
	{
		try {

			cout << endl << "Selecione uma pe�a (1-" << brokenBikes.at(indicator)->getAvarias().size() << "): ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value < 1 || value > (int)brokenBikes.at(indicator)->getAvarias().size())
				throw OpcaoInvalida<int>(value);

			piece = brokenBikes.at(indicator)->getAvarias().at(value-1);

			break;
		}
		catch (OpcaoInvalida<int> &op){

			cout << "Pe�a inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Pe�a inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};


	cin.ignore(1000,'\n');

	BSTItrIn<Peca> it(pieces);
	bool exist {false};

	//Verifica o nome do fornecedor da respetiva pe�a
	while(1)
	{
		try {
			cout << endl << "Nome do fornecedor: " ;
			getline(cin,nome);

			if((valid_word(nome) == false) || (nome.empty()))
				throw OpcaoInvalida<string>(nome);

			break;
		}
		catch (OpcaoInvalida<string> &op) {
			cout << "Nome do fornecedor inv�lido(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	}

	//Procura na BST o respetivo fornecedor, se ja existir verifica se este ja tem a pe�a,

	while(!it.isAtEnd())
	{
		if(it.retrieve().getSupplier() == nome)
		{
			if(it.retrieve().getPieceType() == piece){
				exist = true;
				break;
			}
		}
		it.advance();
	}

	//Executa at� obter um pre�o v�lido
	while(1)
	{
		try{
			cout << endl << "Pre�o: ";
			cin >> option;
			cin.ignore(1000,'\n');
			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);
			if(value <= 0)
				throw OpcaoInvalida<int>(value);

			break;
		}
		catch (OpcaoInvalida<int> &op){

			cout << "Pre�o inv�lido (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Pre�o inv�lido (" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
		}
	};

	if(exist == true)
	{
		//Remove a pe�a, altera-a e volta a adicionar
		BSTItrIn<Peca> iterator(pieces);
		BST<Peca> tmp = pieces; tmp.makeEmpty();

		while(!iterator.isAtEnd())
		{
			if((iterator.retrieve().getPieceType() == piece) && (iterator.retrieve().getSupplier() == nome)) {
				Peca subject = iterator.retrieve();
				subject.setLastPurchasePrice(value);
				tmp.insert(subject);
			}
			else
				tmp.insert(iterator.retrieve());

			iterator.advance();
		}
		pieces = tmp;
	}
	else
		pieces.insert(Peca(value,piece,nome));

	//Remove a peca comprada do vetor de avarias da bicicleta
	removePieceBike(indicator,piece);

	cout << endl << "Pe�a do tipo " << piece << " comprada com sucesso ao fornecedor " << nome << " por " << value << "�" << endl << endl;
}


/////////////////////
// METODOS DISPLAY //
/////////////////////

/**
 * Imprime no ecra a informacao das pecas existentes na BST da oficina.
 */

void Oficina::displayBSTInfo() {

	BSTItrIn<Peca> it(pieces);

	if(it.isAtEnd()) {
		cout << "No momento n�o existe registo de qualquer tipo de pe�a" << endl << endl;
		return;
	}

	cout << "Informa��o acerca das pe�as: " << endl << endl;

	while(!it.isAtEnd())
	{
		cout << "Pe�a: " << it.retrieve().getPieceType() << endl;
		cout << "Fornecedor: " << it.retrieve().getSupplier() << endl;
		if(it.retrieve().getLastPurchasePrice() != 0)
			cout << "Valor da �ltima compra: " << it.retrieve().getLastPurchasePrice() << endl << endl;
		else
			cout << "Valor da �ltima compra: " << "---" << endl << endl;

		it.advance();
	}
}


/**
 * Imprime a informacao sobre uma bicicleta avariada: nome, tipo e avarias.
 * Pede ao utilizador que escolha uma bicicleta da lista apresentada.
 * Para cada introducao do utilizador e verificado se o mesmo introduziu o formato de dados pedido.
 */
void Oficina::displayBrokenBikeInfo() {

	if(brokenBikes.size() == 0)
	{
		cout << "Neste momento n�o existem bicicletas avariadas !" << endl << endl;
		return;
	}

	cout << "Informa��es acerca das bicicletas avariadas" << endl << endl;

	string option;
	int value {};

	cout << "Bicicletas avariadas: " << endl;

	for(unsigned int i = 0; i < brokenBikes.size(); i++)
		cout << (i+1) << " -> " << brokenBikes.at(i)->getBikeName() << endl;

	//Seleciona uma das bicicletas avariadas
	while(1)
	{
		try {

			cout << endl << "Selecione uma bicicleta (1-" << brokenBikes.size() << "): ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value < 1 || value > (int)brokenBikes.size())
				throw OpcaoInvalida<int>(value);

			break;
		}
		catch (OpcaoInvalida<int> &op){

			cout << "Bicicleta inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		catch (OpcaoInvalida<string> &op){

			cout << "Bicicleta inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};

	system("cls");
	mensagemInicial();

	cout << "Informa��o: " << endl << endl;

	//Mostra informa��o relativa a bicicleta selecionada
	cout << "Nome: " << brokenBikes.at(value - 1)->getBikeName() << endl << endl;

	if(brokenBikes.at(value - 1)->getBikeName().at(0) == 'c')
		cout << "Tipo: Corrida" << endl << endl;
	else if(brokenBikes.at(value - 1)->getBikeName().at(0) == 'i')
		cout << "Tipo: Infantil" << endl << endl;
	else
	{
		if(brokenBikes.at(value - 1)->getBikeName().at(1) == 's')
			cout << "Tipo: Urbana Simples" << endl << endl;
		else
			cout << "Tipo: Urbana" << endl << endl;
	}

	cout << "Avarias:" << endl;

	for(unsigned int i = 0; i < brokenBikes.at(value - 1)->getAvarias().size(); i++)
		cout << (i+1) <<" -> " << brokenBikes.at(value - 1)->getAvarias().at(i) << endl;

	cout << endl;
}


/**
 * Imprime no ecra o fornecedor que vendeu mais barato uma determinada peca.
 * Pede ao utilizador que escolha, de uma lista, a peca que pretende verificar.
 * Para cada introducao do utilizador e verificado se o mesmo introduziu o formato de dados pedido.
 */
void Oficina::displayPieceLowestPrice() {

	BSTItrIn<Peca> it(pieces);
	vector<Peca> piecesOrderedPrice;

	if(it.isAtEnd())
	{
		cout << "Neste momento n�o existem fornecedores de qualquer tipo de pe�a " << endl << endl;
		return;
	}

	cout << "Verificar qual o fornecedor que vendeu determinada pe�a a pre�o mais baixo" << endl << endl;

	string piece,option,nome;
	int value {}, price {};
	vector<string> piecesAvailable;

	piecesAvailable.push_back("Pneu"); piecesAvailable.push_back("Corrente"); piecesAvailable.push_back("Pedais");
	piecesAvailable.push_back("Guiador"); piecesAvailable.push_back("Assento"); piecesAvailable.push_back("Cremalheira");
	piecesAvailable.push_back("Punhos"); piecesAvailable.push_back("Trav�o"); piecesAvailable.push_back("Amortecedor");
	piecesAvailable.push_back("Roda");

	//Mostra as pe�as possiveis
	cout << "Pe�as disponiveis: " << endl;

	for(unsigned int i = 0; i < piecesAvailable.size(); i++)
		cout << left << setw(2) << (i+1) << " -> " << piecesAvailable.at(i) << endl;

	//Seleciona uma das pe�as
	while(1)
	{
		try {
			cout << endl << "Pe�a (1-10): ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value < 1 || value > 10)
				throw OpcaoInvalida<int>(value);

			piece = piecesAvailable.at(value - 1);
			break;
		}
		catch (OpcaoInvalida<int> &op){
			cout << "Pe�a inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		catch (OpcaoInvalida<string> &op){
			cout << "Pe�a inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};

	//Adiciona as pe�as do tipo selecionado ao vetor
	while(!it.isAtEnd())
	{
		if(it.retrieve().getPieceType() == piece)
			piecesOrderedPrice.push_back(it.retrieve());

		it.advance();
	}

	if(piecesOrderedPrice.empty())
	{
		cout << "Neste momento n�o existem fornecedores do tipo de pe�a: " << piece << endl << endl;
		return;
	}

	//Ordena o vetor "piecesOrderedPrice" por ordem crescente de pre�o
	sort(piecesOrderedPrice.begin(),piecesOrderedPrice.end());

	for(unsigned int i = 0; i < piecesOrderedPrice.size(); i++)
	{
		if(piecesOrderedPrice.at(i).getLastPurchasePrice() != 0)
		{
			price = piecesOrderedPrice.at(i).getLastPurchasePrice();
			nome = piecesOrderedPrice.at(i).getSupplier();
			break;
		}
	}

	//Mostra a informacao da pe�a com o pre�o mais baixo do tipo "piece"
	system("cls");
	mensagemInicial();
	if(nome.empty())
	{
		cout << "Neste momento a pe�a do tipo " << piece << " ainda n�o foi comprada" << endl << endl;
	}
	else
	{
		cout << "Verificar qual o fornecedor que vendeu determinada pe�a a pre�o mais baixo" << endl << endl;
		cout << "Pe�a: " << piece << endl;
		cout << "Pre�o: " << price << "�" << endl;
		cout << "Fornecedor: " << nome << endl << endl;
	}
}


/**
 * Imprime no ecra os fornecedores que venderam uma determinada peca.
 * Pede ao utilizador que escolha, de uma lista, a peca que pretende verificar.
 * Para cada introducao do utilizador e verificado se o mesmo introduziu o formato de dados pedido.
 */
void Oficina::displaySupliersInfo() {


	BSTItrIn<Peca> it(pieces);
	vector<Peca> piecesOrderedPrice;

	if(it.isAtEnd())
	{
		cout << "Neste momento n�o existem fornecedores de qualquer tipo de pe�a " << endl << endl;
		return;
	}

	cout << "Informa��o acerca dos fornecedores" << endl << endl;

	string piece,option;
	int value {};
	vector<string> piecesAvailable;

	piecesAvailable.push_back("Pneu"); piecesAvailable.push_back("Corrente"); piecesAvailable.push_back("Pedais");
	piecesAvailable.push_back("Guiador"); piecesAvailable.push_back("Assento"); piecesAvailable.push_back("Cremalheira");
	piecesAvailable.push_back("Punhos"); piecesAvailable.push_back("Trav�o"); piecesAvailable.push_back("Amortecedor");
	piecesAvailable.push_back("Roda");

	//Mostra as pe�as possiveis para se adicionarem a BST
	cout << "Pe�as disponiveis: " << endl;

	for(unsigned int i = 0; i < piecesAvailable.size(); i++)
		cout << left << setw(2) << (i+1) << " -> " << piecesAvailable.at(i) << endl;

	//Seleciona uma das pe�as
	while(1)
	{
		try {
			cout << endl << "Pe�a (1-10): ";
			cin >> option;

			if(valid_number(option) == false)
				throw OpcaoInvalida<string>(option);

			value = stoi(option);

			if(value < 1 || value > 10)
				throw OpcaoInvalida<int>(value);

			piece = piecesAvailable.at(value - 1);
			break;
		}
		catch (OpcaoInvalida<int> &op){
			cout << "Pe�a inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		catch (OpcaoInvalida<string> &op){
			cout << "Pe�a inv�lida(" << op.opcao << ") ! Tente novamente." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
	};

	//Adiciona as pe�as do tipo selecionado ao vetor
	while(!it.isAtEnd())
	{
		if(it.retrieve().getPieceType() == piece)
			piecesOrderedPrice.push_back(it.retrieve());

		it.advance();
	}

	if(piecesOrderedPrice.empty())
	{
		cout << endl << "Neste momento n�o existem fornecedores do tipo de pe�a: " << piece << endl << endl;
		return;
	}

	//Ordena o vetor "piecesOrderedPrice" por ordem crescente de pre�o
	sort(piecesOrderedPrice.begin(),piecesOrderedPrice.end());

	//Verifica se alguma das pe�as ja foi comprada
	bool bought {false};

	for(unsigned int i = 0; i < piecesOrderedPrice.size(); i++)
	{
		if(piecesOrderedPrice.at(i).getLastPurchasePrice() != 0)
		{
			bought = true;
			break;
		}
	}

	//Mostra os diferentes pre�os dos diferentes fornecedores de uma pe�a
	system("cls");
	mensagemInicial();

	if(bought == false)
	{
		cout << "Neste momento a pe�a do tipo " << piece << " ainda n�o foi comprada" << endl << endl;
	}
	else
	{	int ord(1);

		cout << "Informa��o acerca dos fornecedores" << endl << endl;
		cout << "Pe�a: " << piece << endl << endl;

		cout << left << setw(10) << "Ordem " << setw(22) << "Fornecedor" << "Pre�o" << endl;

		for(unsigned int i = 0; i < piecesOrderedPrice.size(); i++)
		{
			if(piecesOrderedPrice.at(i).getLastPurchasePrice() != 0){
				cout << "  " << left << setw(8) << ord <<  setw(23) << piecesOrderedPrice.at(i).getSupplier() << right << setw(3) << piecesOrderedPrice.at(i).getLastPurchasePrice() << endl;
				ord++;
			}
		}
		cout << endl;
	}
}
