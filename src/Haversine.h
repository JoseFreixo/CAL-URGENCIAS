#ifndef HAVERSINE_H_
#define HAVERSINE_H_

class Haversine{
private:
	static double deg2rad(double deg);
public:
	static double calculateDistance(double lat1, double lon1, double lat2, double lon2);
};

double Haversine::calculateDistance(double lat1, double lon1, double lat2, double lon2){
	const int earthRadius = 6371;
	double dLat = deg2rad(lat2 - lat1);
	double dLon = deg2rad(lon2 - lon1);
	double a = sin(dLat/2) * sin(dLat/2) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * sin(dLon/2) * sin(dLon/2);
	double c = 2 * atan2(sqrt(a), sqrt(1-a));
	double d = earthRadius * c;
	return d;
}

double Haversine::deg2rad(double deg){
	return deg * acos(-1) / 180;

}

#endif
