#include "Campus.h"

Campus :: Campus() : G(0) {
}

Campus :: Campus(int n) : G(n) {
}

void Campus :: addDirectedEdge
(int u, int v, double dis, double crowdDegree, bool bikeAccess) {
    G.addDirectedEdge(u, v, EdgeNode(dis, crowdDegree, bikeAccess));
}

void Campus :: addUndirectedEdge
(int u, int v, double dis, double crowdDegree, bool bikeAccess) {
    G.addUndirectedEdge(u, v, EdgeNode(dis, crowdDegree, bikeAccess));
}

Vector<Pair<EdgeNode, int> > Campus::shortestPath(
    int startVertex,
    int endVertex,
    double *ans,
    int type
) {
    switch (type) {
        case 0:
            return G.shortestPath<DisCalc> (startVertex, endVertex, ans);
        case 1:
            return G.shortestPath<WalkCalc> (startVertex, endVertex, ans);
        case 2:
            return G.shortestPath<BikeCalc> (startVertex, endVertex, ans);
        default:
            return Vector<Pair<EdgeNode, int> >(0);
    }
}

Array<double> Campus::singleSourceShortestPath(int startVertex, int type) {
    switch (type) {
        case 0:
            return G.singleSourceShortestPath<DisCalc> (startVertex);
        case 1:
            return G.singleSourceShortestPath<WalkCalc> (startVertex);
        case 2:
            return G.singleSourceShortestPath<BikeCalc> (startVertex);
        default:
            return Array<double>(0);
    }
}

Vector<Pair<EdgeNode, int> > Campus::shortestPath(
    int startVertex,
    int endVertex,
    Vector<int> midVertex,
    double *ans,
    int type
) {
    switch (type) {
        case 0:
            return G.shortestPath<DisCalc>
                (startVertex, endVertex, midVertex, ans);
        case 1:
            return G.shortestPath<WalkCalc>
                (startVertex, endVertex, midVertex, ans);
        case 2:
            return G.shortestPath<BikeCalc>
                (startVertex, endVertex, midVertex, ans);
        default:
            return Vector<Pair<EdgeNode, int> >(0);
    }
}
