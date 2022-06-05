#pragma once
#include <stdlib.h>
#include "Graph.h"
#include "EdgeNode.h"

struct Campus {
    Graph G;
    Campus();
    explicit Campus(int n);
    ~Campus();
    void addDirectedEdge
        (int u, int v, double dis, double crowdDegree, bool bikeAccess);
    void addUndirectedEdge
        (int u, int v, double dis, double crowdDegree, bool bikeAccess);
    Vector<Pair<EdgeNode, int> > shortestPath(
        int startVertex,
        int endVertex,
        double *ans,
        int type);
    Array<double> singleSourceShortestPath(int startVertex, int type);
    Vector<Pair<EdgeNode, int> > shortestPath(
        int startVertex,
        int endVertex,
        Vector<int> midVertex,
        double *ans,
        int type);
};
