#ifndef _FILE_READING_H_
#define _FILE_READING_H_
#include <string>
#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graphviewer.h"
#include "NodeInformation.h"
#include "Graph.h"
#include "utils.h"

using namespace std;

class FileReading {
private:
public:
	static bool readNodesInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string fileName, MapCoordinates lol);
	static bool readRoadsInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string fileInfo, string fileGeometry, MapCoordinates lol);
};

bool FileReading::readNodesInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string fileName, MapCoordinates lol){
	ifstream inFile;

	//Ler o ficheiro Nodes.txt
	inFile.open(fileName);

	if (!inFile) {
		cerr << "Unable to open file " << fileName;
		return false;
	}

	string line;
	unsigned long long idNo = 0;
	long double x = 0, y = 0;

	while(getline(inFile, line)) {
		stringstream linestream(line);
		string data;

		linestream >> idNo;
		getline(linestream, data, ';');
		linestream >> x;
		getline(linestream, data, ';');
		linestream >> y;
		gv->addNode(idNo, (unsigned long long)((lol.maxLat - x) * 1000 / (lol.maxLat - lol.minLat)), (unsigned long long)((lol.maxLon - y) * 1000 / (lol.maxLon - lol.minLon)));

		NodeInformation nInfo(idNo, x, y);

		graph.addVertex(nInfo);
	}

	inFile.close();
	return true;
}

bool FileReading::readRoadsInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string fileInfo, string fileGeometry, MapCoordinates lol){

	ifstream inFile;

	//Ler o ficheiro Roads.txt
	inFile.open(fileInfo);

	if (!inFile) {
		cerr << "Unable to open file " << fileInfo;
		return false;
	}

	return true;
}

#endif
