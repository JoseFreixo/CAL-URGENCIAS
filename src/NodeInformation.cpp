#include "NodeInformation.h"

NodeInformation::NodeInformation(unsigned int id, long double latitude, long double longitude){
    this->id = id;
    this->latitude = latitude;
    this->longitude = longitude;
    this->nodeType = "";
}

NodeInformation::NodeInformation(unsigned int id, long double latitude, long double longitude, string nodeType){
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
