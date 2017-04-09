#ifndef Emergencies_H_
#define Emergencies_H_

#include <cstdlib>
#include "Graph.h"
#include "NodeInformation.h"
#include "graphviewer.h"
#include "Vehicle.h"
#include <time.h>
#include <thread>
#include <chrono>

vector<Vehicle> generateVehicles(const Graph<NodeInformation> & graph, GraphViewer *gv);

void randomEmergency(Graph<NodeInformation> & graph, GraphViewer *gv, vector<Vehicle> vehicles, const vector<NodeInformation> &buildings);

void followPath(const Graph<NodeInformation> & graph, GraphViewer *gv, Vehicle &vehicle);

void getPathToEmergencyCentre(Graph<NodeInformation> & graph, int emergencyType, const vector<NodeInformation> & buildings, Vehicle & vehicle);

string iconPath(const string &vehicleType);

#endif
