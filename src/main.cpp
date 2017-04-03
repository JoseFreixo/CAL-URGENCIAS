#include <cstdio>
#include "graphviewer.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "FileReading.h"
#include "NodeInformation.h"
#include "utils.h"

int main () {
	Graph<NodeInformation> graph;

	GraphViewer *gv = new GraphViewer(1000, 1000, true);

	gv->setBackground("background.jpg");

	gv->createWindow(1000, 1000);

	gv->defineEdgeDashed(false);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	MapCoordinates lol;

	FileReading::readNodesInfo(graph, gv, "Nodes.txt", lol);

//	gv->addNode(0);
//	gv->addNode(1);
//	gv->addNode(2);
//	gv->addEdge(0, 0, 1, EdgeType::DIRECTED);
//	gv->addEdge(1, 0, 2, EdgeType::DIRECTED);

	getchar();
	return 0;
}

