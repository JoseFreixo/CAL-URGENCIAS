#ifndef _MAP_COORDINATES_H_
#define _MAP_COORDINATES_H_

class MapCoordinates{
public:
	constexpr static double minLat = 41.1704; //41.1134;
	constexpr static double maxLat = 41.1851; //41.1863;
	constexpr static double minLong = -8.6151; //-8.6929;
	constexpr static double maxLong = -8.5885; //-8.5661;
	constexpr static double deltaLat = maxLat - minLat;
	constexpr static double deltaLong = maxLong - minLong;
	const static int windowHeight = 1710; //1000
	const static int windowWidth = 2321; //1000
};

#endif
