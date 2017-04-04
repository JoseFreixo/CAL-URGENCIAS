#ifndef _NODE_INFORMATION_H_
#define _NODE_INFORMATION_H_

#include <string>

using namespace std;

class NodeInformation{
private:
	long double latitude;
	long double longitude;
	unsigned long long id;
public:
	NodeInformation(unsigned int id, long double latitude, long double longitude);
	long double getLatitude() const;
	long double getLongitude() const;
	unsigned int getId() const;
	bool operator==(const NodeInformation & nInfo) const;
};

NodeInformation::NodeInformation(unsigned int id, long double latitude, long double longitude){
	this->id = id;
	this->latitude = latitude;
	this->longitude = longitude;
}

long double NodeInformation::getLatitude() const{
	return latitude;
}

long double NodeInformation::getLongitude() const{
	return longitude;
}

unsigned int NodeInformation::getId() const{
	return id;
}

bool NodeInformation::operator==(const NodeInformation & nInfo) const {
	if (getId() == nInfo.getId())
		return true;
	return false;
}

#endif
