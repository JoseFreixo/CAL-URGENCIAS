#include "Emergencies.h"

vector<Vehicle> generateVehicles(const Graph<NodeInformation> & graph, GraphViewer *gv){
	vector<Vehicle> vehicles;

	int indexVertex;

	do{
		indexVertex = rand() % graph.getNumVertex() + 1;
	} while(graph.getVertexSet()[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle1("Ambulance", graph.getVertexSet()[indexVertex]->getInfo(), false);
	vehicles.push_back(vehicle1);

	do{
		indexVertex = rand() % graph.getNumVertex() + 1;
	} while(graph.getVertexSet()[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle2("Van", graph.getVertexSet()[indexVertex]->getInfo(), false);
	vehicles.push_back(vehicle2);

	do{
		indexVertex = rand() % graph.getNumVertex() + 1;
	} while(graph.getVertexSet()[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle3("Motorcycle", graph.getVertexSet()[indexVertex]->getInfo(), false);
	vehicles.push_back(vehicle3);

	do{
		indexVertex = rand() % graph.getNumVertex() + 1;
	} while(graph.getVertexSet()[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle4("Policecar", graph.getVertexSet()[indexVertex]->getInfo(), false);
	vehicles.push_back(vehicle4);

	do{
		indexVertex = rand() % graph.getNumVertex() + 1;
	} while(graph.getVertexSet()[indexVertex]->getInfo().getType() != "");

	Vehicle vehicle5("Firetruck", graph.getVertexSet()[indexVertex]->getInfo(), false);
	vehicles.push_back(vehicle5);

	return vehicles;
}

void RandomEmergency(Graph<NodeInformation> & graph, GraphViewer *gv){
	int indexVertex;
	do{
		indexVertex = rand() % graph.getNumVertex() + 1;
	} while(graph.getVertexSet()[indexVertex]->getInfo().getType() != "");
	int emergencyType = rand() % 5 + 1;

	int id;
	id = graph.getVertexSet()[indexVertex]->getInfo().getId();
	graph.dijkstraShortestPath(graph.getVertexSet()[indexVertex]->getInfo());

	switch(emergencyType){
		case 1:
			gv->setVertexColor(id, BLUE);
			break;
		case 2:
			gv->setVertexColor(id, RED);
			break;
		case 3:
			gv->setVertexColor(id, YELLOW);
			break;
		case 4:
			gv->setVertexColor(id, ORANGE);
			break;
		case 5:
			gv->setVertexColor(id, BLACK);
			break;
	}

}
