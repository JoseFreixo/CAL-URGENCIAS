#include "Emergencies.h"

vector<Vehicle> generateVehicles(const Graph<NodeInformation> & graph, GraphViewer *gv){
	vector<Vehicle> vehicles;
    vector<Vertex<NodeInformation>*> vertexes = graph.getVertexSet();

	int indexVertex;
	srand (time(NULL));


	do{
		indexVertex = rand() % graph.getNumVertex();
	} while(vertexes[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle1("Ambulance", vertexes[indexVertex]->getInfo(), false);
	gv->setVertexIcon(vertexes[indexVertex]->getInfo().getId(), "ambulance.png");
	vehicles.push_back(vehicle1);

	do{
		indexVertex = rand() % graph.getNumVertex();
	} while(vertexes[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle2("Van", vertexes[indexVertex]->getInfo(), false);
	gv->setVertexIcon(vertexes[indexVertex]->getInfo().getId(), "van.png");
	vehicles.push_back(vehicle2);

	do{
		indexVertex = rand() % graph.getNumVertex();
	} while(vertexes[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle3("Motorcycle", vertexes[indexVertex]->getInfo(), false);
	gv->setVertexIcon(vertexes[indexVertex]->getInfo().getId(), "motorcycle.png");
	vehicles.push_back(vehicle3);

	do{
		indexVertex = rand() % graph.getNumVertex();
	} while(vertexes[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle4("Policecar", vertexes[indexVertex]->getInfo(), false);
	gv->setVertexIcon(vertexes[indexVertex]->getInfo().getId(), "police.png");
	vehicles.push_back(vehicle4);

	do{
		indexVertex = rand() % graph.getNumVertex();
	} while(vertexes[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle5("Firetruck", vertexes[indexVertex]->getInfo(), false);
	gv->setVertexIcon(vertexes[indexVertex]->getInfo().getId(), "firemen.png");
	vehicles.push_back(vehicle5);

	return vehicles;
}

void randomEmergency(Graph<NodeInformation> & graph, GraphViewer *gv, vector<Vehicle> &vehicles){
	int indexVertex;
    vector<Vertex<NodeInformation>*> vertexes = graph.getVertexSet();

    do{
		indexVertex = rand() % graph.getNumVertex();
	} while(vertexes[indexVertex]->getInfo().getType() != "");
	int emergencyType = rand() % 5 + 1;

	unsigned int id;
	id = vertexes[indexVertex]->getInfo().getId();
	graph.dijkstraShortestPath(vertexes[indexVertex]->getInfo());

	int pos;
	int distance = INT_INFINITY;

	switch(emergencyType){
		case 1:
			gv->setVertexColor(id, BLUE);
			for (size_t i = 0; i < vehicles.size(); i++){
				if (vehicles[i].getType() == "Policecar" && !(vehicles[i].getBusy()) && graph.getVertex(vehicles[i].getInfo())->getDist() < distance){
					pos = i;
					distance = graph.getVertex(vehicles[i].getInfo())->getDist();
				}
			}
            cout << "O carro da Policia ira percorrer a distancia minima de " << distance <<" metros" <<" ate ao vertice Azul\n";
			break;
		case 2:
			gv->setVertexColor(id, RED);
			for (size_t i = 0; i < vehicles.size(); i++){
				if (vehicles[i].getType() == "Firetruck" && !(vehicles[i].getBusy()) && graph.getVertex(vehicles[i].getInfo())->getDist() < distance){
					pos = i;
					distance = graph.getVertex(vehicles[i].getInfo())->getDist();
				}
			}
            cout << "O Camiao dos Bombeiros ira percorrer a distancia minima de " << distance <<" metros" <<" ate ao incendio (vertice vermelho)\n";
			break;
		case 3:
			gv->setVertexColor(id, YELLOW);
			for (size_t i = 0; i < vehicles.size(); i++){
				if (vehicles[i].getType() == "Motorcycle" && !(vehicles[i].getBusy()) && graph.getVertex(vehicles[i].getInfo())->getDist() < distance){
					pos = i;
					distance = graph.getVertex(vehicles[i].getInfo())->getDist();
				}
			}
            cout << "A Mota do INEM ira percorrer a distancia minima de " << distance <<" metros" <<" ate a emergencia de baixa gravidade\n";
			break;
		case 4:
			gv->setVertexColor(id, ORANGE);
			for (size_t i = 0; i < vehicles.size(); i++){
				if (vehicles[i].getType() == "Van" && !(vehicles[i].getBusy()) && graph.getVertex(vehicles[i].getInfo())->getDist() < distance){
					pos = i;
					distance = graph.getVertex(vehicles[i].getInfo())->getDist();
				}
			}
            cout << "A Carrinha INEM ira percorrer a distancia minima de " << distance <<" metros" <<" ate a emergencia de moderada gravidade\n";
            break;
		case 5:
			gv->setVertexColor(id, BLACK);
			for (size_t i = 0; i < vehicles.size(); i++) {
				if (vehicles[i].getType() == "Ambulance" && !(vehicles[i].getBusy()) && graph.getVertex(vehicles[i].getInfo())->getDist() < distance) {
					pos = i;
					distance = graph.getVertex(vehicles[i].getInfo())->getDist();
				}
			}
            cout << "A Ambulancia ira percorrer a distancia minima de " << distance <<" metros" <<" ate a emergencia de elevada gravidade\n";
			break;
	}

	NodeInformation currentNode = vehicles[pos].getInfo();
	vector<int> way;
	do{
		currentNode = ((graph.getVertex(currentNode))->path)->getInfo();
		way.push_back(currentNode.getId());
	}while(currentNode.getId() != id);
	vehicles[pos].setWay(way);

    followPath(graph, gv, vehicles[pos]);
	vehicles[pos].setBusy(true);
}


void followPath(Graph<NodeInformation> & graph, GraphViewer *gv, Vehicle &vehicle){
   vector<int> pathIDs = vehicle.getWay();
	string iconPth = iconPath(vehicle.getType());


    for (int i = 0; i < pathIDs.size()-1; i++)
    {
		this_thread::sleep_for(chrono::seconds(3));
        gv->clearVertexIcon(pathIDs[i]);
		gv->setVertexIcon(pathIDs[i+1], iconPth);
		vehicle.setInfo(graph.getVertex(NodeInformation(pathIDs[i+1], 1,1))->getInfo());
    }
}

string iconPath(const string &vehicleType){
	if(vehicleType == "Ambulance")
		return "ambulance.png";
	if(vehicleType == "Van")
		return  "van.png";
	if(vehicleType == "Motorcycle")
		return "motocycle.png";
	if(vehicleType == "Policecar")
		return "police.png";
	if(vehicleType == "Firetruck")
		return "firemen.png";

	return "";
}