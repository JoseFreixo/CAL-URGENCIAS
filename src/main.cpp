#include <cstdio>
#include "graphviewer.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "FileReading.h"
#include "MapCoordinates.h"
#include "NodeInformation.h"

int main () {
	Graph<NodeInformation> graph;

	GraphViewer *gv = new GraphViewer(MapCoordinates::windowWidth, MapCoordinates::windowHeight, false);

	//gv->setBackground("background.png");

	gv->createWindow(MapCoordinates::windowWidth, MapCoordinates::windowHeight);

	//FileReading::readNodesInfo(graph, gv, "Nodes.txt");
	//FileReading::readRoadsInfo(graph, gv, "Roads.txt", "SubRoads.txt");
	FileReading::readSimpleInfo(graph, gv, "FileNodes.txt", "FileRoads.txt", "FileConection.txt");

	gv->defineEdgeCurved(false);
	gv->defineEdgeColor("black");

	gv->rearrange();

	getchar();
	return 0;
}

