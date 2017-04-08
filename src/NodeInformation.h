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
	NodeInformation(unsigned int id, long double latitude, long double longitude);
	NodeInformation(unsigned int id, long double latitude, long double longitude, string nodeType);
	long double getLatitude() const;
	long double getLongitude() const;
	unsigned int getId() const;
	string getType() const;
	void setType(string type);
	bool operator==(const NodeInformation & nInfo) const;
};
#endif
