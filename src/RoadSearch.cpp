#include "RoadSearch.h"

void searchStreetVehicles(const Graph<NodeInformation> & graph, const string & s1, const string & s2, const int & vehicle, const vector<Vehicle> & vehicles){
    NodeInformation road1[2];
    NodeInformation road2[2];
    int road1Found = false;
    int road2Found = false;
    vector<Vertex<NodeInformation>* > v = graph.getVertexSet();
    for (size_t i = 0; i < v.size() && ( !road1Found || !road2Found); i++){
        vector<Edge<NodeInformation>> tmp = v[i]->getAdj();
        for (size_t a = 0; a < tmp.size(); a++) {
            if (!road1Found && kmp(tmp[a].getLabel(), s1)) {
                road1[0] = v[i]->getInfo();
                road1[1] = tmp[a].getDest()->getInfo();
                road1Found = true;
            }
            if (!road2Found && kmp(tmp[a].getLabel(), s2)) {
                road2[0] = v[i]->getInfo();
                road2[1] = tmp[a].getDest()->getInfo();
                road2Found = true;
            }
        }
    }
    if (!road1Found){
        cout << "Nao existe nenhuma rua com " << s1 << " no seu nome!\n";
        return;
    }
    if (!road2Found){
        cout << "Nao existe nenhuma rua com " << s2 << " no seu nome!\n";
        return;
    }

    NodeInformation node;

    if (verifyRoadConnection(road1, road2, node)){
        cout << "As ruas fornecidas nao se cruzam, impossivel verificar veiculos num cruzamento inexistente.\n";
        return;
    }

    string veiculo;

    switch(vehicle){
        case 1:
            veiculo = "Mota do INEM";
            for (int i = 0; i < vehicles.size(); i++){
                if (vehicles[i].getType() == "Mota" && vehicles[i].getInfo() == node){
                    cout << "Sim, neste preciso momento uma Mota do INEM encontra-se no cruzamento entre as ruas fornecidas.\n";
                    return;
                }
            }
            break;

        case 2:
            veiculo = "Carrinha do INEM";
            for (int i = 0; i < vehicles.size(); i++){
                if (vehicles[i].getType() == "Carrinha" && vehicles[i].getInfo() == node){
                    cout << "Sim, neste preciso momento uma Carrinha do INEM encontra-se no cruzamento entre as ruas fornecidas.\n";
                    return;
                }
            }
            break;
        case 3:
            veiculo = "Ambulancia do INEM";
            for (int i = 0; i < vehicles.size(); i++){
                if (vehicles[i].getType() == "Ambulancia" && vehicles[i].getInfo() == node){
                    cout << "Sim, neste preciso momento uma Ambulancia do INEM encontra-se no cruzamento entre as ruas fornecidas.\n";
                    return;
                }
            }
            break;
        case 4:
            veiculo = "Camiao dos Bombeiros";
            for (int i = 0; i < vehicles.size(); i++){
                if (vehicles[i].getType() == "Camiao dos Bombeiros" && vehicles[i].getInfo() == node){
                    cout << "Sim, neste preciso momento um Camiao dos Bombeiros encontra-se no cruzamento entre as ruas fornecidas.\n";
                    return;
                }
            }
            break;
        case 5:
            veiculo = "Carro da Policia";
            for (int i = 0; i < vehicles.size(); i++){
                if (vehicles[i].getType() == "Carro da Policia" && vehicles[i].getInfo() == node){
                    cout << "Sim, neste preciso momento um Carro da Policia encontra-se no cruzamento entre as ruas fornecidas.\n";
                    return;
                }
            }
            break;
    }

    cout << "Nenhum(a) " << veiculo << " se encontra no cruzamento entre as ruas fornecidas.\n";
    return;
}

int verifyRoadConnection(const NodeInformation road1[], const NodeInformation road2[], NodeInformation & node){
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            if (road1[i] == road2[j]) {
                node = road1[i];
                return 0;
            }
        }
    }
    return 1;
}
