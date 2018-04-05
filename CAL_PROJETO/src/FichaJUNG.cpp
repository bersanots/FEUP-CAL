#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Grafos.h"
#include "Node.h"


void graphviewer_display();

void print_path_GV(vector<Node> path,GraphViewer * gv);


void graphviewer_display()
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
	int X=0;
	int Y=0;
	int idStore=0;
	string a="";


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
