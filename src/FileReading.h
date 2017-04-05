#ifndef _FILE_READING_H_
#define _FILE_READING_H_

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <utility>

#include "graphviewer.h"
#include "Graph.h"
#include "Haversine.h"
#include "MapCoordinates.h"
#include "NodeInformation.h"

using namespace std;

class FileReading {
private:
public:
	static bool readNodesInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string fileName);
	static bool readRoadsInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string fileInfo, string fileGeometry);
	static bool readSimpleInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string nodes, string roads);
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
	long double longDeg = 0, latDeg = 0;

	while(getline(inFile, line)) {
		stringstream linestream(line);
		string data;

		unsigned int idTemp;

		linestream >> idNo;
		idTemp = idNo % numeric_limits<unsigned int>::max();
		getline(linestream, data, ';');
		linestream >> latDeg;
		getline(linestream, data, ';');
		linestream >> longDeg;

		if (latDeg > MapCoordinates::maxLat || latDeg < MapCoordinates::minLat || longDeg > MapCoordinates::maxLong || longDeg < MapCoordinates::minLong)
			continue;

		double xPerc, yPerc;

		xPerc = (longDeg - MapCoordinates::minLong) / MapCoordinates::deltaLong;
		yPerc = 1 - (latDeg - MapCoordinates::minLat) / MapCoordinates::deltaLat;

		int width, height;

		width = round(xPerc * MapCoordinates::windowWidth);
		height = round(yPerc * MapCoordinates::windowHeight);

		gv->addNode(idTemp, width, height);
		gv->setVertexLabel(idTemp, " ");

		NodeInformation nInfo(idNo, latDeg, longDeg);

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
		getline(linestream, roadName, ';');
		linestream >> undirected;

		pair<string, bool> roadInfo(roadName, undirected);
		pair<unsigned long long, pair<string, bool>> road(idAr, roadInfo);
		arestasInfo.insert(road);
	}

	inFile.close();

	inFile.open(fileGeometry);

	if (!inFile) {
		cerr << "Unable to open file " << fileGeometry;
		return false;
	}

	int arCounter = 0;
	unsigned long long v1, v2;

	while (getline(inFile, line)){
		stringstream linestream(line);
		string data;

		linestream >> idAr;
		getline(linestream, data, ';');

		auto it = arestasInfo.find(idAr);

		linestream >> v1;
		getline(linestream, data, ';');
		linestream >> v2;

		unsigned int v1temp = v1 % numeric_limits<unsigned int>::max();
		unsigned int v2temp = v2 % numeric_limits<unsigned int>::max();

		Vertex<NodeInformation> * v1test = graph.getVertex(NodeInformation(v1, 0, 0));
		Vertex<NodeInformation> * v2test = graph.getVertex(NodeInformation(v2, 0, 0));

		if (NULL == v1test || NULL == v2test)
			continue;

		int direction;

		if (((*it).second).second)
			direction = EdgeType::UNDIRECTED;
		else
			direction = EdgeType::DIRECTED;


		gv->addEdge(arCounter++, v1temp, v2temp, direction);

		gv->setEdgeLabel(arCounter, ((*it).second).first);

		NodeInformation source = v1test->getInfo();
		NodeInformation dest = v2test->getInfo();
		double weight = Haversine::calculateDistance(source.getLatitude(), source.getLongitude(), dest.getLatitude(), dest.getLongitude());

		graph.addEdge(source, dest, weight);
	}

	inFile.close();

	return true;
}

static bool FileReading::readSimpleInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string nodes, string roads){

	ifstream inFile;
	inFile.open(nodes);

	if (!inFile){
		cerr << "Unable to open file " << nodes << endl;
		exit(1);
	}

	string line;

	int idNo = 0;
	int x = 0;
	int y = 0;

	while(getline(inFile, line)){
		stringstream linestream(line);
		string data;

		linestream >> idNo;
		getline(linestream, data, ';');
		linestream >> x;
		getline(linestream, data, ';');
		linestream >> y;

		gv->addNode(idNo, x, y);
		NodeInformation info(idNo, y, x);
		graph.addVertex(info);
	}

	inFile.close();

	inFile.open(roads);

	if (!inFile){
		cerr << "Unable to open file " << roads << endl;
		exit(1);
	}

	int idAresta = 0;
	string nomeAresta;
	bool undirected;

	map<int, pair<string, bool>> arestas;

	while(getline(inFile, line)){
		stringstream linestream(line);
		string data;

		linestream >> idAresta;
		getline(linestream, data, ';');
		getline(linestream, nomeAresta,';');
		linestream >> undirected;

		pair<string, bool> informAresta(nomeAresta, undirected);
		pair<int, pair<string, bool>> aresta(idAresta, informAresta);

		arestas.insert(aresta);
	}

	inFile.close();
}

#endif
