#ifndef Emergencies_H_
#define Emergencies_H_

#include <cstdlib>
#include "Graph.h"
#include "NodeInformation.h"
#include "graphviewer.h"
#include "Vehicle.h"
#include <ctime>
#include <thread>
#include <chrono>
#include <fstream>

vector<Vehicle> generateVehicles(const Graph<NodeInformation> & graph, GraphViewer *gv);

void randomEmergency(Graph<NodeInformation> & graph, GraphViewer *gv, vector<Vehicle> & vehicles, const vector<NodeInformation> &buildings);

void testEmergency(Graph<NodeInformation> & graph, ofstream & algorithmResults);

void followPath(const Graph<NodeInformation> & graph, GraphViewer *gv, vector<Vehicle> &vehicle, int pos);

void getPathToEmergencyCentre(Graph<NodeInformation> & graph, int emergencyType, const vector<NodeInformation> & buildings, Vehicle & vehicle);

string iconPath(const string &vehicleType);

void testGraphConectivity(const Graph<NodeInformation> & graph);

void repaintVehicles(GraphViewer *gv, vector<Vehicle> &vehicles, int pos);

void searchStreetVehicles(const Graph<NodeInformation> & graph, string s1, string s2);

#endif
