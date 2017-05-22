#ifndef CAL_URGENCIAS_ROADSEARCH_H
#define CAL_URGENCIAS_ROADSEARCH_H

#include "Graph.h"
#include "NodeInformation.h"
#include "graphviewer.h"
#include "Vehicle.h"
#include <vector>
#include "matcher.h"
#include <chrono>
#include <ctime>
#include <iomanip>

void searchStreetVehicles(const Graph<NodeInformation> & graph, const string & s1, const string & s2, const int & vehicle, const vector<Vehicle> & vehicles);

int verifyRoadConnection(const NodeInformation road1[], const NodeInformation road2[], NodeInformation & node);

template <class T>
bool vectorNonRepeatedInsert(vector<T> & vec, T elem);

bool findApproximateRoads(vector<pair<NodeInformation, NodeInformation>> & roadsNodes, vector<string> & roads, const string & s, const Graph<NodeInformation> & graph);

void compareStringMatchAlgorithms(string filename1, string filename2, string filename3, ofstream & stringMatchResults);

void readInt(int &n);

#endif //CAL_URGENCIAS_ROADSEARCH_H
