#include <string>
#include "MapCoordinates.h"
#include "graphviewer.h"
#include "FileReading.h"
#include "Emergencies.h"
#include "RoadSearch.h"

int main () {
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

	ofstream algorithmResults, stringMatchResults;
	algorithmResults.open(filename + "AlgorithmResults.txt", ofstream::out | ofstream::app);
    stringMatchResults.open(filename + "StringMatchComparison.txt", ofstream::out | ofstream::app);

	Graph<NodeInformation> graph;
    vector<NodeInformation> buildings;

    GraphViewer* gv = new GraphViewer(MapCoordinates::windowWidth, MapCoordinates::windowHeight, false);
    gv->createWindow(MapCoordinates::windowWidth, MapCoordinates::windowHeight);

    if(!FileReading::readSimpleInfo(graph, gv, buildings, filename + "Nodes.txt", filename + "Roads.txt", filename + "SubRoads.txt")){
    	cerr << "Ficheiros invalidos ou mal formatados.";
    	return 1;
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
        cout << "2. Testar Algoritmos de caminho mais curto\n";
        cout << "3. Testar Conetividade\n";
        cout << "4. Procurar recursos de emergencia\n";
        cout << "5. Testar Algoritmos de comparacao de strings\n";
        cout << "0. Terminar programa\n";
        cout <<"Insira uma das opcoes: ";

        readInt(choice);
        string fn1, fn2, fn3;
        switch (choice){
            case 1:
                thread(randomEmergency, ref(graph), gv, ref(vehicles), ref(buildings)).detach();
                break;
            case 2:
                testEmergency(graph, algorithmResults);
                cout << "Os resultados foram escritos para um ficheiro\n";
                break;
            case 3:
            	testGraphConectivity(graph);
            	break;
            case 4:
            {
                int veiculo = -1;

            	string r1, r2;
            	cout << "Insira nome da 1a rua: ";
            	getline(cin, r1);
            	cout << "Insira nome da 2a rua: ";
            	getline(cin, r2);
                while (veiculo < 1 || veiculo > 5) {
                    cout << "Que veiculo procura?\n1. Mota do INEM\n2. Carrinha do INEM\n3. Ambulancia do INEM\n4. Camiao dos Bombeiros\n5. Carro da PSP\n\nOpcao: ";
                    readInt(veiculo);
                }
                searchStreetVehicles(graph, r1, r2, veiculo, vehicles);
            	break;
            }
            case 5:
                cout << "Insira o nome do ficheiro de texto nr. 1: ";
                getline(cin, fn1);
                cout << "Insira o nome do ficheiro de texto nr. 2: ";
                getline(cin, fn2);
                cout << "Insira o nome do ficheiro de texto nr. 3: ";
                getline(cin, fn3);
                compareStringMatchAlgorithms(fn1, fn2, fn3, stringMatchResults);
                break;
            case 0:
            	algorithmResults.close();
                return 0;
            default:
                cout << "Opcao invalida, tente novamente...\n";
                break;
        }
    }

}


