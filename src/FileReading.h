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
	static bool readSimpleInfo(Graph<NodeInformation> & graph, GraphViewer *gv, vector<NodeInformation> &buildings, string nodes, string roads, string connections);
};

bool FileReading::readSimpleInfo(Graph<NodeInformation> & graph, GraphViewer *gv, vector<NodeInformation> &buildings, string nodes, string roads, string connections){

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
		string trash, nodeType = "";

		linestream >> idNo;
		getline(linestream, trash, ';');
		linestream >> x;
		getline(linestream, trash, ';');
		linestream >> y;
        getline(linestream, trash, ';');
        getline(linestream, nodeType, ';');

		gv->addNode(idNo, x, y);
        NodeInformation info(idNo, y, x, nodeType);
        if(nodeType != ""){
            gv->setVertexLabel(idNo, nodeType);
            buildings.push_back(info);
        }

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
