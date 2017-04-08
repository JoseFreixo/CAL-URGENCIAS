#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "NodeInformation.h"
#include <string>

using namespace std;

class Vehicle{
private:
	string type;
	NodeInformation info;
	bool busy;
public:
	Vehicle(string type, const NodeInformation &info, bool busy);
	string getType() const;
	NodeInformation getInfo() const;
	bool getBusy() const;
	void setInfo(NodeInformation info);
	void setBusy(bool busy);
};

#endif
