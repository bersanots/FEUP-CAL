#include "Includes.h"
#include "Sistema.h"

using namespace std;

void openInterface(Sistema & ER);
void checkinSys(Sistema & ER);
void checkoutSys(Sistema & ER);

/**
 * Inicializacao do programa, checkin do sistema , apresentacao de interface ,
 * execucao das funcoes selecionadas e no final checkout do sistema.
 */
int main()
{
	//Códigos para aceitação de caracteres da língua portuguesa
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	///////////////////////////////////////
	// Zona de inicialização do programa //
	///////////////////////////////////////

	globalData = Data(0,0,0);

	mensagemInicial();

	Sistema sys;

	cout << "APPLICATION LOADING"; cout << " .";

	try{
		checkinSys(sys);
	}
	catch (AberturaFalhada<string> &a){
		cout << "Falha ao abrir o ficheiro " << a.getFicheiro() << "." << endl;
		cout << "Tente mais tarde.\n";
		system("pause");
		return 1;
	}

	Sleep(500);
	system("cls");

	sys.setDataAtual(globalData);

	openInterface(sys);

	try{
		checkoutSys(sys);
	}
	catch (AberturaFalhada<string> &a){
		cout << "Falha ao abrir o ficheiro " << a.getFicheiro() << "." << endl;
		cout << "Tente mais tarde./n";
		return 1;
	}

	return 0;
}

/**
 * Efetua a leitura dos 3 ficheiros de texto que contem a informacao sobre o sistema
 * e coloca-a corretamente no sistema.
 * Para efetuar a extracao da informacao, a funcao recorre ao operador de extracao >>
 * que foi redefinido para todas as classes usadas no sistema.
 * @param ER sistema que se pretende completar
 */
void checkinSys(Sistema & ER){
	ifstream file_1, file_2;
	string f_line;
	stringstream ss;
	char tipoUtente;

	file_1.open("utentes.txt");
	if (!file_1.is_open())
		throw AberturaFalhada<string>("utentes.txt");

	while(!file_1.eof()){
		getline(file_1,f_line);
		if (f_line != ""){
			ss << f_line;
			tipoUtente = ss.get();
			ss.get();

			if(tipoUtente == 'R'){
				Regular u1;
				ss >> u1;
				if (u1.getNome() != ""){
					Utente * u = new Regular(u1);
					ER.addNewUtente(u);
				}
				else{
					Utente::setLastId();
					break;
				}
			}
			else {
				Socio u1;
				ss >> u1;
				if (u1.getNome()!=""){
					Utente * u = new Socio(u1);
					ER.addNewUtente(u);
				}
				else{
					Utente::setLastId();
					break;
				}
			}
		}
	}

	file_1.close();

	cout << ".";

	file_1.open("pontosPartilha.txt");
	if (!file_1.is_open())
		throw AberturaFalhada<string>("pontos_partilha.txt");

	file_2.open("bicicletas.txt");
	if (!file_2.is_open())
		throw AberturaFalhada<string>("bicicletas.txt");

	while(!file_1.eof()){
		PontoPartilha p1;
		file_1 >> p1;

		if(p1.getNome()==""){
			break;
		}
		file_1.ignore();

		vector<int> numType = p1.getNumberOfBikes();
		p1.limpaVectorBike();

		for (unsigned int j=0 ; j<numType.size() ; j++){
			for (int k=0 ; k < numType.at(j) ; k++){
				string b;
				Bicicleta* bike;
				getline(file_2, b,'\n');

				if(b.at(0) == 'u') {
					if(b.at(1) == 's') {
						bike = new UrbanaSimples(b);
					}
					else
						bike = new Urbana(b);
				}
				else if(b.at(0) == 'c')
					bike = new Corrida(b);
				else
					bike = new Infantil(b);

				if(bike->getBikeName()==""){
					continue;
				}

				p1.adicionaBike(bike);
			}
		}

		PontoPartilha * p = new PontoPartilha(p1);
		ER.addPontoPartilha(p);
	}

	file_1.close();

	file_2.close();

	/// LOJAS ///
	file_1.open("lojas.txt");
	if (!file_1.is_open())
		throw AberturaFalhada<string>("lojas.txt");

	priority_queue<Loja> tmp;

	while (!file_1.eof()) {

		getline(file_1,f_line);
		if (f_line != ""){
			ss << f_line;

			Loja lj;

			ss >> lj;

			tmp.push(lj);
		}
	}
	ER.setStores(tmp);

	file_1.close();

	cout << ".";

	/// OFICINA ///
	file_2.open("oficina.txt");
	if (!file_2.is_open())
		throw AberturaFalhada<string>("oficina.txt");

	Oficina of;

	file_2 >> of;

	ER.setOficina(of);

	file_2.close();

	/// ABATES ///
	file_1.open("abates.txt");
	if (!file_1.is_open())
		throw AberturaFalhada<string>("abates.txt");

	tabHAbates tmptab;

	while (!file_1.eof()) {
		getline(file_1,f_line);

		if (f_line != ""){
			stringstream ss1;

			ss1 << f_line;
			string name;

			getline(ss1, name,',');

			Bicicleta bike(name);
			Data data;
			ss1 >> data;

			bike.setAbate(data);
			tmptab.insert(bike);
		}
	}
	ER.setJunkyard(tmptab);

	file_1.close();

	return;
};

/**
 * Insere nos ficheiros de texto a informacao contida no sistema formatadamente.
 * Para efetuar a insercao da informacao, a funcao recorre ao operador de insercao <<
 * que foi redefinido para todas as classes usadas no sistema.
 * @param ER sistema que se pretende guardar
 */
void checkoutSys(Sistema & ER){

	ofstream file_1;
	ofstream file_2;

	/// UTENTES ///
	file_1.open("utentes.txt");
	if (!file_1.is_open())
		throw AberturaFalhada<string>("utentes.txt");

	for(unsigned int it=0 ; it<ER.getUtentes().size() ; it++){
		if(ER.getUtentes().at(it)->getTipoUtente() == "Socio" ){
			Socio s = *static_cast<Socio *> (ER.getUtentes().at(it));
			file_1 << s << endl;
		}
		else {
			Regular r = *static_cast<Regular *> (ER.getUtentes().at(it));
			file_1 << r << endl;
		}
	}

	file_1.close();

	/// PONTOS PARTILHA ///
	file_1.open("pontosPartilha.txt");
	if (!file_1.is_open())
		throw AberturaFalhada<string>("pontos_partilha.txt");

	file_2.open("bicicletas.txt");
	if (!file_2.is_open())
		throw AberturaFalhada<string>("bicicletas.txt");

	for(unsigned int it=0 ; it<ER.getPontosPartilha().size() ; it++){
		file_1 << (*ER.getPontosPartilha().at(it)) << endl;

		PontoPartilha p(*ER.getPontosPartilha().at(it));

		for(unsigned int j=0 ; j<p.getBikes().size() ; j++)
			for(unsigned int k=0 ; k <p.getBikes().at(j).size() ; k++){
				file_2 << (*p.getBikes().at(j).at(k)).getBikeName() << endl;
			}
	}

	file_1.close();
	file_2.close();

	/// LOJAS ///
	file_1.open("lojas.txt");
	if (!file_1.is_open())
		throw AberturaFalhada<string>("lojas.txt");

	priority_queue<Loja> tmp = ER.getStores();

	while (!tmp.empty()) {
		file_1 << tmp.top() << endl;
		tmp.pop();
	}

	file_1.close();

	/// OFICINA ///
	file_2.open("oficina.txt");
	if (!file_2.is_open())
		throw AberturaFalhada<string>("oficina.txt");

	file_2 << ER.getOficina();

	file_2.close();

	/// ABATES ///
	file_1.open("abates.txt");
	if (!file_1.is_open())
		throw AberturaFalhada<string>("abates.txt");

	tabHAbates tmptab = ER.getJunkyard();

	tabHAbates::iterator it = tmptab.begin();

	while(it != ER.getJunkyard().end()) {
		if(it->getBikeName() != "")
			file_1 << it->getBikeName() << ',' << it->getAbate() << endl;

		it++;
	}

	file_1.close();

	return;
}
