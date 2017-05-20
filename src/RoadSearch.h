#ifndef CAL_URGENCIAS_ROADSEARCH_H
#define CAL_URGENCIAS_ROADSEARCH_H

#include "Graph.h"
#include "NodeInformation.h"
#include "graphviewer.h"
#include "Vehicle.h"

void searchStreetVehicles(const Graph<NodeInformation> & graph, string s1, string s2, int vehicle);

#endif //CAL_URGENCIAS_ROADSEARCH_H
