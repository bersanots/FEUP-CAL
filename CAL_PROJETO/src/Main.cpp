#include "Includes.h"
#include "Sistema.h"
#include <sstream>
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

	///////////////////////////////////////
	// Zona de inicializacao do programa //
	///////////////////////////////////////

	mensagemInicial();

	Sistema sys{};

	cout << "APPLICATION LOADING";

	checkinSys(sys) ;

	openInterface(sys);

	checkoutSys(sys);

	return 0;
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

	/*ifstream f_nodes{};

		try{
			f_nodes.open("nodes.txt");
			if (!f_pontos_partilha.is_open())
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
				ss << f_line;
				Node *node = new Node{};
				ss >> *node;
				ER.addNode(node);
			}
		}

		f_nodes.close();*/

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
		f_utentes << ER.getUtentes().at(it) << endl;
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
		f_pontos_partilha << ER.getPontosPartilha().at(it) << endl;
	}

	f_pontos_partilha.close();

	return;
}
