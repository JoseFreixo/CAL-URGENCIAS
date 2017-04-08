#include "Emergencies.h"

void RandomEmergency(Graph<NodeInformation> graph, GraphViewer *gv){
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
