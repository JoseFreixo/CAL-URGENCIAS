#include "RoadSearch.h"

void searchStreetVehicles(const Graph<NodeInformation> & graph, string s1, string s2, int vehicle){
    NodeInformation road1[2];
    NodeInformation road2[2];
    int road1Found = false;
    int road2Found = false;
    vector<Vertex<NodeInformation>* > v = graph.getVertexSet();
    for (size_t i = 0; i < v.size() && ( !road1Found || !road2Found); i++){
        vector<Edge<NodeInformation>> tmp = v[i]->getAdj();
        for (size_t a = 0; a < tmp.size(); a++) {
            if (!road1Found && tmp[a].getLabel() == s1) {
                road1[0] = v[i]->getInfo();
                road1[1] = tmp[a].getDest()->getInfo();
                road1Found = true;
            }
            if (!road2Found && tmp[a].getLabel() == s2) {
                road2[0] = v[i]->getInfo();
                road2[1] = tmp[a].getDest()->getInfo();
                road2Found = true;
            }
        }
    }
    if (!road1Found || !road2Found){
        cout << "Pelo menos uma das ruas fornecidas nao existe!\n";
        return;
    }
}
