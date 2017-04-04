#ifndef _FILE_READING_H_
#define _FILE_READING_H_
#include <string>
#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>
#include "graphviewer.h"
#include "NodeInformation.h"
#include "Graph.h"
#include "MapCoordinates.h"

using namespace std;

class FileReading {
private:
public:
	static bool readNodesInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string fileName);
	static bool readRoadsInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string fileInfo, string fileGeometry);
};

bool FileReading::readNodesInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string fileName){
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

		unsigned int idTemp;

		linestream >> idNo;
		idTemp = idNo % numeric_limits<unsigned int>::max();
		getline(linestream, data, ';');
		linestream >> y;
		getline(linestream, data, ';');
		linestream >> x;
		gv->addNode(idTemp, (int)((MapCoordinates::maxLat - x) * MapCoordinates::windowSize / (MapCoordinates::maxLat - MapCoordinates::minLat)), (int)((MapCoordinates::maxLon - y) * MapCoordinates::windowSize / (MapCoordinates::maxLon - MapCoordinates::minLon)));

		NodeInformation nInfo(idNo, y, x);

		graph.addVertex(nInfo);
	}

	inFile.close();
	return true;
}

bool FileReading::readRoadsInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string fileInfo, string fileGeometry){

	ifstream inFile;

	//Ler o ficheiro Roads.txt
	inFile.open(fileInfo);

	if (!inFile) {
		cerr << "Unable to open file " << fileInfo;
		return false;
	}

	string line;
	unsigned long long idAr = 0;
	string roadName;
	bool undirected;

	map<unsigned long long, pair<string, bool>> arestasInfo;

	while (getline(inFile, line)){
		stringstream linestream(line);
		string data;

		linestream >> idAr;
		getline(linestream, data, ';');
		linestream >> roadName;
		getline(linestream, data, ';');
		linestream >> undirected;

		pair<string, bool> roadInfo(roadName, undirected);
		pair<unsigned long long, pair<string, bool>> road(idAr, roadInfo);
		arestasInfo.insert(road);
	}

	inFile.open(fileGeometry);

	if (!inFile) {
		cerr << "Unable to open file " << fileGeometry;
		return false;
	}

	int arCounter = 0;

	while (getline(inFile, line)){
		stringstream linestream(line);
		string data;

		linestream >> idAr;
		getline(linestream, data, ';');


	}

	return true;
}

#endif
