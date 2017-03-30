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
	long double getLatitude();
	long double getLongitude();
	unsigned int getId();
};

NodeInformation::NodeInformation(unsigned int id, long double latitude, long double longitude){
	this->id = id;
	this->latitude = latitude;
	this->longitude = longitude;
}

long double NodeInformation::getLatitude(){
	return latitude;
}

long double NodeInformation::getLongitude(){
	return longitude;
}

unsigned int NodeInformation::getId(){
	return id;
}

#endif
