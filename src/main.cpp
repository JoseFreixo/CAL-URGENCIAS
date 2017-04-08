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

	Graph<NodeInformation> graph;

    GraphViewer* gv = new GraphViewer(MapCoordinates::windowWidth, MapCoordinates::windowHeight, false);
    gv->createWindow(MapCoordinates::windowWidth, MapCoordinates::windowHeight);

    FileReading::readSimpleInfo(graph, gv, "FileNodes.txt", "FileRoads.txt", "FileConection.txt");

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
        cout << "2. Mostrar unidades disponiveis\n";
        cout <<"Insira uma das opcoes: ";

        readInt(choice);

        switch (choice){
            case 1:
                //randomEmergency();
                break;
            case 2:
                //showAvaiableUnits();
                break;
            case 0:
                return 0;
            default:
                cout << "Opcao invalida, tente novamente...\n";
                break;
        }
    }

}


