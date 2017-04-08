#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "NodeInformation.h"
#include <string>
#include <vector>

using namespace std;

class Vehicle{
private:
	string type;
	NodeInformation info;
	bool busy;
	vector<int> way;
public:
	Vehicle(string type, const NodeInformation &info, bool busy);
	string getType() const;
	NodeInformation getInfo() const;
	bool getBusy() const;
	vector<int> getWay() const;
	void setInfo(NodeInformation info);
	void setBusy(bool busy);
	void setWay(vector<int> way);
};

#endif

