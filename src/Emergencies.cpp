#include "Emergencies.h"

vector<Vehicle> generateVehicles(const Graph<NodeInformation> & graph, GraphViewer *gv){
	vector<Vehicle> vehicles;
    vector<Vertex<NodeInformation>*> vertexes = graph.getVertexSet();

	int indexVertex;
	srand (time(NULL));


	do{
		indexVertex = rand() % graph.getNumVertex();
	} while(vertexes[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle1("Ambulancia", vertexes[indexVertex]->getInfo(), false);
	gv->setVertexIcon(vertexes[indexVertex]->getInfo().getId(), "ambulance.png");
	vehicles.push_back(vehicle1);

	do{
		indexVertex = rand() % graph.getNumVertex();
	} while(vertexes[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle2("Carrinha", vertexes[indexVertex]->getInfo(), false);
	gv->setVertexIcon(vertexes[indexVertex]->getInfo().getId(), "van.png");
	vehicles.push_back(vehicle2);

	do{
		indexVertex = rand() % graph.getNumVertex();
	} while(vertexes[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle3("Mota", vertexes[indexVertex]->getInfo(), false);
	gv->setVertexIcon(vertexes[indexVertex]->getInfo().getId(), "motorcycle.png");
	vehicles.push_back(vehicle3);

	do{
		indexVertex = rand() % graph.getNumVertex();
	} while(vertexes[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle4("Carro da Policia", vertexes[indexVertex]->getInfo(), false);
	gv->setVertexIcon(vertexes[indexVertex]->getInfo().getId(), "police.png");
	vehicles.push_back(vehicle4);

	do{
		indexVertex = rand() % graph.getNumVertex();
	} while(vertexes[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle5("Camiao dos Bombeiros", vertexes[indexVertex]->getInfo(), false);
	gv->setVertexIcon(vertexes[indexVertex]->getInfo().getId(), "firemen.png");
	vehicles.push_back(vehicle5);

	return vehicles;
}

void randomEmergency(Graph<NodeInformation> & graph, GraphViewer *gv, vector<Vehicle> & vehicles, const vector<NodeInformation> &buildings)
{
	int indexVertex;
    vector<Vertex<NodeInformation>*> vertexes = graph.getVertexSet();

    do{
		indexVertex = rand() % graph.getNumVertex();
	} while(vertexes[indexVertex]->getInfo().getType() != "");
	int emergencyType = rand() % 5 + 1;

	unsigned int id;
	id = vertexes[indexVertex]->getInfo().getId();

	int pos;
	int distance = INT_INFINITY;

	switch(emergencyType){
		case 1:
			gv->setVertexColor(id, BLUE);
			for (size_t i = 0; i < vehicles.size(); i++){
				if (vehicles[i].getType() == "Carro da Policia" && !(vehicles[i].getBusy())) {
					graph.dijkstraShortestPath(vehicles[i].getInfo());
					if (graph.getVertex(vertexes[indexVertex]->getInfo())->getDist() < distance){
						pos = i;
						distance = graph.getVertex(vertexes[indexVertex]->getInfo())->getDist();

						NodeInformation currentNode = vertexes[indexVertex]->getInfo();
						vector<int> way;
						do{
							way.insert(way.begin(), currentNode.getId());
							currentNode = ((graph.getVertex(currentNode))->path)->getInfo();
						}while(currentNode.getId() != vehicles[i].getInfo().getId());

						vehicles[pos].setWay(way);
					}
				}
			}
            break;
		case 2:
			gv->setVertexColor(id, RED);
			for (size_t i = 0; i < vehicles.size(); i++){
				if (vehicles[i].getType() == "Camiao dos Bombeiros" && !(vehicles[i].getBusy())) {
					graph.dijkstraShortestPath(vehicles[i].getInfo());
					if (graph.getVertex(vertexes[indexVertex]->getInfo())->getDist() < distance) {
						pos = i;
						distance = graph.getVertex(vertexes[indexVertex]->getInfo())->getDist();

						NodeInformation currentNode = vertexes[indexVertex]->getInfo();
						vector<int> way;
						do {
							way.insert(way.begin(), currentNode.getId());
							currentNode = ((graph.getVertex(currentNode))->path)->getInfo();
						} while (currentNode.getId() != vehicles[i].getInfo().getId());

						vehicles[pos].setWay(way);
					}
				}
			}
            break;
		case 3:
			gv->setVertexColor(id, YELLOW);
			for (size_t i = 0; i < vehicles.size(); i++){
				if (vehicles[i].getType() == "Mota" && !(vehicles[i].getBusy())) {
					graph.dijkstraShortestPath(vehicles[i].getInfo());
					if (graph.getVertex(vertexes[indexVertex]->getInfo())->getDist() < distance) {
						pos = i;
						distance = graph.getVertex(vertexes[indexVertex]->getInfo())->getDist();

						NodeInformation currentNode = vertexes[indexVertex]->getInfo();
						vector<int> way;
						do {
							way.insert(way.begin(), currentNode.getId());
							currentNode = ((graph.getVertex(currentNode))->path)->getInfo();
						} while (currentNode.getId() != vehicles[i].getInfo().getId());

						vehicles[pos].setWay(way);
					}
				}
			}
            break;
		case 4:
			gv->setVertexColor(id, ORANGE);
			for (size_t i = 0; i < vehicles.size(); i++){
				if (vehicles[i].getType() == "Carrinha" && !(vehicles[i].getBusy())) {
					graph.dijkstraShortestPath(vehicles[i].getInfo());
					if (graph.getVertex(vertexes[indexVertex]->getInfo())->getDist() < distance) {
						pos = i;
						distance = graph.getVertex(vertexes[indexVertex]->getInfo())->getDist();

						NodeInformation currentNode = vertexes[indexVertex]->getInfo();
						vector<int> way;
						do {
							way.insert(way.begin(), currentNode.getId());
							currentNode = ((graph.getVertex(currentNode))->path)->getInfo();
						} while (currentNode.getId() != vehicles[i].getInfo().getId());

						vehicles[pos].setWay(way);
					}
				}
			}
            break;
		case 5:
			gv->setVertexColor(id, BLACK);
			for (size_t i = 0; i < vehicles.size(); i++) {
				if (vehicles[i].getType() == "Ambulancia" && !(vehicles[i].getBusy())) {
					graph.dijkstraShortestPath(vehicles[i].getInfo());
					if (graph.getVertex(vertexes[indexVertex]->getInfo())->getDist() < distance) {
						pos = i;
						distance = graph.getVertex(vertexes[indexVertex]->getInfo())->getDist();

						NodeInformation currentNode = vertexes[indexVertex]->getInfo();
						vector<int> way;
						do {
							way.insert(way.begin(), currentNode.getId());
							currentNode = ((graph.getVertex(currentNode))->path)->getInfo();
						} while (currentNode.getId() != vehicles[i].getInfo().getId());

						vehicles[pos].setWay(way);
					}
				}
			}
			break;
	}

	gv->rearrange();

	if (distance == INT_INFINITY){
		cout << "Nao ha veiculos adequados disponiveis.\n";
		return;
	}
	cout << "O/A "<< vehicles[pos].getType() <<" percorreu a distancia minima de " << distance <<" metros ate a emergencia!\n";
	vehicles[pos].setBusy(true);
    followPath(graph, gv, vehicles, pos);
    getPathToEmergencyCentre(graph, emergencyType, buildings, vehicles[pos]);
    followPath(graph, gv, vehicles, pos);
    vehicles[pos].setBusy(false);
    cout << "Emergencia resolvida!\n";
}

void testEmergency(Graph<NodeInformation> & graph, ofstream & algorithmResults){
	int emergencyVertex;
	vector<Vertex<NodeInformation>*> vertexes = graph.getVertexSet();

	if(!algorithmResults.is_open())
		cout << "Nao e possivel abrir/criar o ficheiro de tempos dos algoritmos\n";

	do{
		emergencyVertex = rand() % graph.getNumVertex();
	} while(vertexes[emergencyVertex]->getInfo().getType() != "");


	chrono::time_point<chrono::high_resolution_clock > n1, n2, n3, n4;
	n1 = chrono::high_resolution_clock::now();
	graph.floydWarshallShortestPath();
	n2 = chrono::high_resolution_clock::now();
	graph.bellmanFordShortestPath(vertexes[emergencyVertex]->getInfo());
	n3 = chrono::high_resolution_clock::now();
	graph.dijkstraShortestPath(vertexes[emergencyVertex]->getInfo());
	n4 = chrono::high_resolution_clock::now();
	chrono::high_resolution_clock::duration t1 = n2 - n1, t2 = n3 - n2, t3 = n4 - n3;
	algorithmResults << chrono::duration_cast<chrono::nanoseconds>(t2).count() << "," << chrono::duration_cast<chrono::nanoseconds>(t3).count() << "," << chrono::duration_cast<chrono::nanoseconds>(t1).count() << endl;

	/*clock_t n1, n2, n3, n4;
	n4 = clock();
	graph.dijkstraShortestPath(vertexes[emergencyVertex]->getInfo());
	n2 = clock();
	graph.bellmanFordShortestPath(vertexes[emergencyVertex]->getInfo());
	n1 = clock();
	graph.floydWarshallShortestPath();
	n3 = clock();
	clock_t t1 = n2 - n4, t2 = n1 - n2, t3 = n3 - n1;
	algorithmResults << 1000*((float)t2)/CLOCKS_PER_SEC << "," << 1000*((float)t3)/CLOCKS_PER_SEC << "," << 1000*((float)t1)/CLOCKS_PER_SEC << endl;*/

	/*chrono::time_point<chrono::high_resolution_clock> n1, n2, n3, n4;
		n4 = chrono::high_resolution_clock::now();
		graph.dijkstraShortestPath(vertexes[emergencyVertex]->getInfo());
		n2 = chrono::high_resolution_clock::now();
		graph.bellmanFordShortestPath(vertexes[emergencyVertex]->getInfo());
		n1 = chrono::high_resolution_clock::now();
		graph.floydWarshallShortestPath();
		n3 = chrono::high_resolution_clock::now();
		auto t1 = n2 - n4, t2 = n1 - n2, t3 = n3 - n1;
		algorithmResults << t2.count() << "," << t3.count() << "," << t1.count() << endl;*/
}


void followPath(const Graph<NodeInformation> & graph, GraphViewer *gv, vector<Vehicle> &vehicle, int pos){
    vector<int> pathIDs = vehicle[pos].getWay();
	string iconPth = iconPath(vehicle[pos].getType());


    for (size_t i = 0; i < pathIDs.size(); i++)
    {
		this_thread::sleep_for(chrono::seconds(3));
        gv->clearVertexIcon(vehicle[pos].getInfo().getId());
        repaintVehicles(gv, vehicle, pos);
		gv->setVertexIcon(pathIDs[i], iconPth);
		vehicle[pos].setInfo(graph.getVertex(NodeInformation(pathIDs[i], 1,1))->getInfo());
		gv->rearrange();
    }
    gv->setVertexColor(pathIDs[pathIDs.size() - 1], GREEN);
    gv->rearrange();
}

void getPathToEmergencyCentre(Graph<NodeInformation> & graph, int emergencyType, const vector<NodeInformation> & buildings, Vehicle & vehicle){
	int distance = INT_INFINITY;
	int distBuilding = 0;

	switch(emergencyType){
	case 1:
		for (size_t i = 0; i < buildings.size(); i++){
			if (buildings[i].getType() == "Police Department"){
				graph.dijkstraShortestPath(graph.getVertex(vehicle.getInfo())->getInfo());
				distBuilding = graph.getVertex(buildings[i])->getDist();
				if (distBuilding < distance){
					distance = distBuilding;

					NodeInformation currentNode = buildings[i];
					vector<int> way;
					do {
						way.insert(way.begin(), currentNode.getId());
						currentNode = ((graph.getVertex(currentNode))->path)->getInfo();
					} while (currentNode.getId() != vehicle.getInfo().getId());

					vehicle.setWay(way);
				}
			}
		}
		break;
	case 2:
		for (size_t i = 0; i < buildings.size(); i++){
			if (buildings[i].getType() == "Fire Department"){
				graph.dijkstraShortestPath(graph.getVertex(vehicle.getInfo())->getInfo());
				distBuilding = graph.getVertex(buildings[i])->getDist();
				if (distBuilding < distance){
					distance = distBuilding;

					NodeInformation currentNode = buildings[i];
					vector<int> way;
					do {
						way.insert(way.begin(), currentNode.getId());
						currentNode = ((graph.getVertex(currentNode))->path)->getInfo();
					} while (currentNode.getId() != vehicle.getInfo().getId());

					vehicle.setWay(way);
				}
			}
		}
		break;
	default:
		for (size_t i = 0; i < buildings.size(); i++){
			if (buildings[i].getType() == "Hospital"){
				graph.dijkstraShortestPath(graph.getVertex(vehicle.getInfo())->getInfo());
				distBuilding = graph.getVertex(buildings[i])->getDist();
				if (distBuilding < distance){
					distance = distBuilding;

					NodeInformation currentNode = buildings[i];
					vector<int> way;
					do {
						way.insert(way.begin(), currentNode.getId());
						currentNode = ((graph.getVertex(currentNode))->path)->getInfo();
					} while (currentNode.getId() != vehicle.getInfo().getId());

					vehicle.setWay(way);
				}
			}
		}
		break;
	}
	cout << "O/A " << vehicle.getType() << " percorreu " <<distance <<" metros, ate ao centro de emergencias\n";
}

string iconPath(const string &vehicleType){
	if(vehicleType == "Ambulancia")
		return "ambulance.png";
	if(vehicleType == "Carrinha")
		return  "van.png";
	if(vehicleType == "Mota")
		return "motorcycle.png";
	if(vehicleType == "Carro da Policia")
		return "police.png";
	if(vehicleType == "Camiao dos Bombeiros")
		return "firemen.png";

	return "";
}

void testGraphConectivity(const Graph<NodeInformation> & graph){
	vector<Vertex<NodeInformation>* > vx = graph.getVertexSet();
	for (size_t i = 0; i < vx.size(); i++)
		if ((int)graph.dfsTest(vx[i]).size() != graph.getNumVertex()){
			cout << "O grafo nao e conexo.\n";
			return;
		}
	cout << "\nO grafo e conexo.\n";
}

void repaintVehicles(GraphViewer *gv, vector<Vehicle> &vehicles, int pos){
	for (size_t i = 0; i < vehicles.size(); i++){
		if (i != pos){
			gv->setVertexIcon(vehicles[i].getInfo().getId(), iconPath(vehicles[i].getType()));
		}
	}
}
