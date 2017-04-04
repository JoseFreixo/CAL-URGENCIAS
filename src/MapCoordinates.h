#ifndef _MAP_COORDINATES_H_
#define _MAP_COORDINATES_H_

class MapCoordinates{
public:
	constexpr static double minLat = 41.7145;
	constexpr static double maxLat = 41.7282;
	constexpr static double minLong = -8.7881;
	constexpr static double maxLong = -8.7669;
	constexpr static double deltaLat = maxLat - minLat;
	constexpr static double deltaLong = maxLong - minLong;
	const static int windowHeight = 859;
	const static int windowWidth = 985;
};

#endif
