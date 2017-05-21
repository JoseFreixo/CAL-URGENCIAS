#include <string>
#include "MapCoordinates.h"
#include "graphviewer.h"
#include "FileReading.h"
#include "Emergencies.h"
#include "RoadSearch.h"

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
	algorithmResults.open(filename + "AlgorithmResults.txt", ofstream::out | ofstream::app);

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
        cout << "2. Testar Algoritmos\n";
        cout << "3. Testar Conetividade\n";
        cout << "4. Procurar recursos de emergencia\n";
        cout << "0. Terminar programa\n";
        cout <<"Insira uma das opcoes: ";

        readInt(choice);

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
            	string r1, r2;
            	cout << "Insira nome da 1a rua: ";
            	getline(cin, r1);
            	cout << "Insira nome da 2a rua: ";
            	getline(cin, r2);
                cout << "Que veiculo procura?\n1. Mota do INEM\n2. Carrinha do INEM\n3. Ambulancia do INEM\n4. Camiao dos Bombeiros\n5. Carro da PSP\n\nOpcao: ";
                int veiculo = -1;
                readInt(veiculo);
            	searchStreetVehicles(graph, r1, r2, veiculo, vehicles);
            	break;
            }
            case 0:
            	algorithmResults.close();
                return 0;
                break;
            default:
                cout << "Opcao invalida, tente novamente...\n";
                break;
        }
    }

}


