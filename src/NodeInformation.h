#ifndef NODEINFORMATION_H_
#define NODEINFORMATION_H_

#include <string>

using namespace std;

class NodeInformation{
private:
	long double latitude;
	long double longitude;
	unsigned long long id;
	string nodeType;
public:
	NodeInformation(unsigned int id, long double latitude, long double longitude, string nodeType);
	long double getLatitude() const;
	long double getLongitude() const;
	unsigned int getId() const;
	string getType() const;
	void setType(string type);
	bool operator==(const NodeInformation & nInfo) const;
};

NodeInformation::NodeInformation(unsigned int id, long double latitude, long double longitude, string nodeType = ""){
	this->id = id;
	this->latitude = latitude;
	this->longitude = longitude;
	this->nodeType = nodeType;
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

string NodeInformation::getType() const{
	return nodeType;
}

void NodeInformation::setType(string type)
{
	this->nodeType = type;
}

bool NodeInformation::operator==(const NodeInformation & nInfo) const {
	if (getId() == nInfo.getId())
		return true;
	return false;
}



#endif
