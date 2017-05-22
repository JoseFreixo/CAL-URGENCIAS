#include "RoadSearch.h"

void searchStreetVehicles(const Graph<NodeInformation> & graph, const string & s1, const string & s2, const int & vehicle, const vector<Vehicle> & vehicles){
    vector<pair<NodeInformation, NodeInformation>> roads1Nodes;
    vector<pair<NodeInformation, NodeInformation>> roads2Nodes;
    vector<string> roads1;
    vector<string> roads2;
    vector<Vertex<NodeInformation>* > v = graph.getVertexSet();
    for (size_t i = 0; i < v.size(); i++){
        vector<Edge<NodeInformation>> tmp = v[i]->getAdj();
        for (size_t a = 0; a < tmp.size(); a++) {
            if (naive(tmp[a].getLabel(), s1)) {
                if (vectorNonRepeatedInsert(roads1, tmp[a].getLabel())) {
                    pair<NodeInformation, NodeInformation> road;
                    road.first = v[i]->getInfo();
                    road.second = tmp[a].getDest()->getInfo();
                    roads1Nodes.push_back(road);
                }
            }
            if (naive(tmp[a].getLabel(), s2)) {
                if (vectorNonRepeatedInsert(roads2, tmp[a].getLabel())) {
                    pair<NodeInformation, NodeInformation> road;
                    road.first = v[i]->getInfo();
                    road.second = tmp[a].getDest()->getInfo();
                    roads2Nodes.push_back(road);
                }
            }
        }
    }
    if (roads1.size() == 0){
        cout << "Nao existe nenhuma rua com '" << s1 << "' no seu nome! A efetuar pesquisa aproximada...\n";
        if(!findApproximateRoads(roads1Nodes, roads1, s1, graph))
            return;
    }
    if (roads2.size() == 0){
        cout << "Nao existe nenhuma rua com '" << s2 << "' no seu nome! A efetuar pesquisa aproximada...\n";
        if(!findApproximateRoads(roads2Nodes, roads2, s2, graph))
            return;
    }

    int choice = -1;
    if (roads1.size() != 1){
        while (choice < 1 || choice > roads1.size()){
            cout << "Foram encontradas as seguintes ruas na pesquisa por '" << s1 << "', qual delas quer?\n\n";
            for (int i = 0; i < roads1.size(); i++){
                cout << i + 1 << ". " << roads1[i] << endl;
            }
            cout << endl << "Opcao: ";
            readInt(choice);
        }
    }
    if(choice == -1)
        choice = 1;
    NodeInformation r1[] = {roads1Nodes[choice - 1].first, roads1Nodes[choice - 1].second};

    choice = -1;
    if (roads2.size() != 1){
        while (choice < 1 || choice > roads2.size()){
            cout << "Foram encontradas as seguintes ruas na pesquisa por '" << s2 << "', qual delas quer?\n\n";
            for (int i = 0; i < roads2.size(); i++){
                cout << i + 1 << ". " << roads2[i] << endl;
            }
            cout << endl << "Opcao: ";
            readInt(choice);
        }
    }
    if(choice == -1)
        choice = 1;
    NodeInformation r2[] = {roads2Nodes[choice - 1].first, roads2Nodes[choice - 1].second};

    NodeInformation node;

    if (verifyRoadConnection(r1, r2, node)){
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
        default:
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

template <class T>
bool vectorNonRepeatedInsert(vector<T> & vec, T elem){
    for(size_t i = 0; i < vec.size(); i++){
        if (vec[i] == elem)
            return false;
    }
    vec.push_back(elem);
    return true;
}

bool findApproximateRoads(vector<pair<NodeInformation, NodeInformation>> & roadsNodes, vector<string> & roads, const string & s, const Graph<NodeInformation> & graph){
    vector<Vertex<NodeInformation>* > v = graph.getVertexSet();
    for (size_t i = 0; i < v.size(); i++){
        vector<Edge<NodeInformation>> tmp = v[i]->getAdj();
        for (size_t a = 0; a < tmp.size(); a++) {
            if (approximateStringMatching(tmp[a].getLabel(), s)) {
                if (vectorNonRepeatedInsert(roads, tmp[a].getLabel())) {
                    pair<NodeInformation, NodeInformation> road;
                    road.first = v[i]->getInfo();
                    road.second = tmp[a].getDest()->getInfo();
                    roadsNodes.push_back(road);
                }
            }
        }
    }
    if (roads.size())
        return true;
    cout << "Nao foram encontradas ruas com nome aproximado a '" << s << "'.\n";
    return false;
}

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