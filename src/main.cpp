#include <string>
#include "MapCoordinates.h"
#include "graphviewer.h"
#include "FileReading.h"
#include "NodeInformation.h"
#include "Emergencies.h"
#include <iostream>
#include "Graph.h"
#include "Vehicle.h"
#include <vector>
#include <fstream>

void readInt(int &n){
//    int tmp = n;
    do
    {
        if(cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cerr << "\nInseriu um caracter invalido, tente novamente ";
        }

        cin >> n;

    }while(cin.fail());

    cin.ignore(); //Ignores the '\n' character

}

int main () {

	int option;
	bool wrongChoice = true;
	cout << "Deseja ler mapas simples ou mapas reais? (1: mapas simples, 2: mapas reais)\nOpcao: ";
	readInt(option);

	if (option == 1 || option == 2)
			wrongChoice = false;

	while(wrongChoice){
		cout << "Numero invalido. (1: mapas simples, 2: mapas reais)\n Opcao: ";
		readInt(option);
		if (option == 1 || option == 2)
			wrongChoice = false;
	}

	cout << "Introduza o prefixo dos ficheiros que deseja ler (Ex: 'Prefixo'Nodes.txt, excluindo as plicas): ";
	string filename;
	getline(cin, filename);

	ifstream fileN, fileR, fileSR;
	fileN.open(filename + "Nodes.txt");
	fileR.open(filename + "Roads.txt");
	fileSR.open(filename + "SubRoads.txt");

	while(!fileN.is_open() || !fileR.is_open() || !fileSR.is_open()){
		cout << "Pelo menos um dos ficheiros nao foi encontrado, reintroduza o prefixo ou verifique se existe algum erro no nome dos ficheiros: ";
		getline(cin, filename);
		fileN.open(filename + "Nodes.txt");
		fileR.open(filename + "Roads.txt");
		fileSR.open(filename + "SubRoads.txt");
	}

	fileN.close();
	fileR.close();
	fileSR.close();

	ofstream algorithmResults;
	algorithmResults.open(filename + "AlgorithmResults.txt");

	Graph<NodeInformation> graph;
    vector<NodeInformation> buildings;

    GraphViewer* gv = new GraphViewer(MapCoordinates::windowWidth, MapCoordinates::windowHeight, false);
    gv->createWindow(MapCoordinates::windowWidth, MapCoordinates::windowHeight);

    switch(option){
    case 1:
    	if(!FileReading::readSimpleInfo(graph, gv, buildings, filename + "Nodes.txt", filename + "Roads.txt", filename + "SubRoads.txt")){
    		cerr << "Ficheiros invalidos ou mal formatados.";
    		return 1;
    	}
    	break;
    case 2:
    	if(!FileReading::readNodesInfo(graph, gv, buildings, filename + "Nodes.txt", filename) || !FileReading::readRoadsInfo(graph, gv, filename + "Roads.txt", filename + "SubRoads.txt")){
    	    cerr << "Ficheiros invalidos ou mal formatados.";
    	    return 1;
    	}
    	break;
    }

    vector<Vehicle> vehicles = generateVehicles(graph, gv);

    gv->defineEdgeCurved(false);
    gv->defineVertexColor("green");
    gv->defineEdgeColor("black");
    gv->rearrange();



    int choice = -1;

    while(true){

        /*Menu*/
        cout << "\nSistema de Gestao de Emergencias\n\n";
        cout << "1. Gerar Emergencia aleatoria\n";
        //cout << "2. Mostrar unidades disponiveis\n";
        cout << "0. Terminar programa\n";
        cout <<"Insira uma das opcoes: ";

        readInt(choice);

        switch (choice){
            case 1:
                randomEmergency(graph, gv, vehicles, buildings);
                break;
//            case 2:
//                //showAvaiableUnits();
//                break;
            case 0:
                return 0;
            default:
                cout << "Opcao invalida, tente novamente...\n";
                break;
        }
    }

}


