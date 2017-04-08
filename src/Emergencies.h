#ifndef Emergencies_H_
#define Emergencies_H_

#include <cstdlib>
#include "Graph.h"
#include "NodeInformation.h"
#include "graphviewer.h"
#include "Vehicle.h"
#include <time.h>

vector<Vehicle> generateVehicles(const Graph<NodeInformation> & graph, GraphViewer *gv);

void RandomEmergency(Graph<NodeInformation> & graph, GraphViewer *gv, vector<Vehicle> vehicles);

#endif

