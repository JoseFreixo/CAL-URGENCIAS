#include "RoadSearch.h"

void searchStreetVehicles(const Graph<NodeInformation> & graph, string s1, string s2, int vehicle){
    vector<Vertex<NodeInformation>* > v = graph.getVertexSet();
    for (size_t i = 0; i < v.size(); i++){
        vector<Edge<NodeInformation>> tmp = v[i]->getAdj();
        for (size_t a = 0; a < tmp.size(); a++)
            cout << tmp[a].getLabel() << endl;
    }
}
