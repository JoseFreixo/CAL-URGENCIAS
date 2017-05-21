#ifndef CAL_URGENCIAS_ROADSEARCH_H
#define CAL_URGENCIAS_ROADSEARCH_H

#include "Graph.h"
#include "NodeInformation.h"
#include "graphviewer.h"
#include "Vehicle.h"
#include <vector>
#include "matcher.h"

void searchStreetVehicles(const Graph<NodeInformation> & graph, const string & s1, const string & s2, const int & vehicle, const vector<Vehicle> & vehicles);

int verifyRoadConnection(const NodeInformation road1[], const NodeInformation road2[], NodeInformation & node);

template <class T>
bool vectorNonRepeatedInsert(vector<T> & vec, T elem);

void readInt(int &n);

#endif //CAL_URGENCIAS_ROADSEARCH_H
