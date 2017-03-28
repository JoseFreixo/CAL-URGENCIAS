#ifndef _FILE_READING_H_
#define _FILE_READING_H_
#include <string>

template <class T>
class FileReading {
public:
	bool readNodesInfo(Graph<T> graph, string fileName);
	bool readRoadsInfo(Graph<T> graph, string fileInfo, string fileGeometry);
};

#endif
