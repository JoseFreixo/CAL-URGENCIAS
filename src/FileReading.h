#ifndef _FILE_READING_H_
#define _FILE_READING_H_
#include <string>
#include "Graph.h"

using namespace std;

template <class T>
class FileReading {
public:
	static bool readNodesInfo(Graph<T> graph, string fileName);
	static bool readRoadsInfo(Graph<T> graph, string fileInfo, string fileGeometry);
};


template <class T>
bool FileReading<T>::readNodesInfo(Graph<T> graph, string fileName){
	return true;
}

template <class T>
bool FileReading<T>::readRoadsInfo(Graph<T> graph, string fileInfo, string fileGeometry){
	return true;
}

#endif
