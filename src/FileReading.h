#ifndef _FILE_READING_H_
#define _FILE_READING_H_

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <sstream>
#include <utility>

#include "Haversine.h"
#include "Graph.h"
#include "graphviewer.h"
#include "NodeInformation.h"


using namespace std;

class FileReading {
private:
public:
	static bool readNodesInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string fileName);
	static bool readRoadsInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string fileInfo, string fileGeometry);
	static bool readSimpleInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string nodes, string roads, string connections);
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
		//gv->setVertexLabel(idTemp, " ");

		NodeInformation nInfo(idNo, latDeg, longDeg);

		graph.addVertex(nInfo);

        cout << "idNo (grafo) " << idNo << "  Gv id" << idTemp;
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
	string undirected;

	map<unsigned long long, pair<string, string>> arestasInfo;

	while (getline(inFile, line)){
		stringstream linestream(line);
		string data;

		linestream >> idAr;
		getline(linestream, data, ';');
		getline(linestream, roadName, ';');
		linestream >> undirected;

		pair<string, string> roadInfo(roadName, undirected);
		pair<unsigned long long, pair<string, string>> road(idAr, roadInfo);
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

		if (((*it).second).second == "True")
			direction = EdgeType::UNDIRECTED;
		else
			direction = EdgeType::DIRECTED;


		gv->addEdge(arCounter++, v1temp, v2temp, direction);

		gv->setEdgeLabel(arCounter, ((*it).second).first);

		NodeInformation source = v1test->getInfo();
		NodeInformation dest = v2test->getInfo();
		double weight = Haversine::calculateDistance(source.getLatitude(), source.getLongitude(), dest.getLatitude(), dest.getLongitude());

		graph.addEdge(source, dest, weight, arCounter);
	}

	inFile.close();

	return true;
}

bool FileReading::readSimpleInfo(Graph<NodeInformation> & graph, GraphViewer *gv, string nodes, string roads, string connections){
	ifstream inFile;
	inFile.open(nodes);

	if (!inFile){
		cerr << "Unable to open file " << nodes << endl;
		return false;
	}

	string line;

	int idNo = 0;
	int x = 0;
	int y = 0;

	while(getline(inFile, line)){
		stringstream linestream(line);
		string trash;

		linestream >> idNo;
		getline(linestream, trash, ';');
		linestream >> x;
		getline(linestream, trash, ';');
		linestream >> y;

		gv->addNode(idNo, x, y);
		NodeInformation info(idNo, y, x);
		graph.addVertex(info);
	}

	inFile.close();

	inFile.open(roads);

	if (!inFile){
		cerr << "Unable to open file " << roads << endl;
		return false;
	}

	int idAresta = 0;
	string nomeAresta;
	string undirected;

	map<int, pair<string, string>> arestas;


	while(getline(inFile, line)){
		istringstream linestream(line);

		linestream >> idAresta;
		linestream.ignore(INT_MAX, ';');
		getline(linestream, nomeAresta,';');
		getline(linestream, undirected);

		pair<string, string> informAresta(nomeAresta, undirected);
		pair<int, pair<string, string>> aresta(idAresta, informAresta);

		arestas.insert(aresta);
	}

	inFile.close();

	inFile.open(connections);

	if (!inFile){
		cerr << "Unable to open file " << connections << endl;
		return false;
	}

	int source = 0, dest = 0;

	while(getline(inFile, line)){
		stringstream linestream(line);
		string data;

		linestream >> idAresta;
		getline(linestream, data, ';');
		linestream >> source;
		getline(linestream, data, ';');
		linestream >> dest;

		auto it = arestas.find(idAresta);

		int bidirected;

		if (((*it).second).second == "True")
			bidirected = EdgeType::UNDIRECTED;
		else
			bidirected = EdgeType::DIRECTED;

		gv->addEdge(idAresta, source, dest, bidirected);

		gv->setEdgeLabel(idAresta, ((*it).second).first);

		Vertex<NodeInformation> * v1test = graph.getVertex(NodeInformation(source, 0, 0));
		Vertex<NodeInformation> * v2test = graph.getVertex(NodeInformation(dest, 0, 0));

		NodeInformation sourc = v1test->getInfo();
		NodeInformation des = v2test->getInfo();
		int w = sqrt(pow(sourc.getLatitude() - des.getLatitude(), 2) + pow(sourc.getLongitude() - des.getLongitude(),2));

		graph.addEdge(sourc, des, w, idAresta);

		if (bidirected == EdgeType::UNDIRECTED){
			graph.addEdge(des, sourc, w, idAresta);
		}
	}

	inFile.close();

	return true;
}

#endif
