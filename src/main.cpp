#include <cstdio>
#include "graphviewer.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "FileReading.h"
#include "NodeInformation.h"

int main () {
	Graph<NodeInformation> graph();

	FileReading<NodeInformation>::readNodesInfo(graph, "Nodes.txt");

	GraphViewer *gv = new GraphViewer(600, 600, true);

	gv->setBackground("background.jpg");

	gv->createWindow(600, 600);

	gv->defineEdgeDashed(false);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(0);
	gv->addNode(1);
	gv->addNode(2);
	gv->addEdge(0, 0, 1, EdgeType::DIRECTED);
	gv->addEdge(1, 0, 2, EdgeType::DIRECTED);

	getchar();
	return 0;
}

