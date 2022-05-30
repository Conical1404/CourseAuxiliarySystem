#pragma once
#include <stdlib.h>
#include "Graph.hpp"

class Guider {
 private:
    struct EdgeNode {
        double dis;
        double speed;
        double crowdDegree;
        EdgeNode();
        EdgeNode(double d, double s, double c);
        inline double TransitTime();
        inline bool operator < (const EdgeNode & other) const;
    };
    double walkSpeed;
    double bikeSpeed;
 public:
    Graph<EdgeNode> walkGraph;
    Graph<EdgeNode> bikeGraph;
    Graph<double> disGraph;
    Guider();
    Guider(int n, double v1, double v2);
    void addDirectedEdge
        (int u, int v, double dis, double crowdDegree, bool bikeAccess);
    void addUndirectedEdge
        (int u, int v, double dis, double crowdDegree, bool bikeAccess);
};

Guider :: EdgeNode :: EdgeNode() {
    dis = 0, speed = 0, crowdDegree = 0;
}

Guider :: EdgeNode :: EdgeNode(double d, double s, double c) {
    dis = d, speed = s, crowdDegree = c;
}

double Guider :: EdgeNode :: TransitTime() {
    return dis / (speed * crowdDegree);
}

bool Guider :: EdgeNode :: operator < (const EdgeNode & other) const {
    return TransitTime() < other.TransitTime();
}

Guider :: Guider() : walkGraph(0), bikeGraph(0), disGraph(0) {
    walkSpeed = 0, bikeSpeed = 0;
}

Guider :: Guider(int n, double v1, double v2) :
walkGraph(n), bikeGraph(n), disGraph(n) {
    walkSpeed = v1, bikeSpeed = v2;
}

void Guider :: addDirectedEdge
(int u, int v, double dis, double crowdDegree, bool bikeAccess) {
    disGraph.addDirectedEdge(u, v, dis);
    walkGraph.addDirectedEdge(u, v, EdgeNode(dis, walkSpeed, crowdDegree));
    if (bikeAccess)
        bikeGraph.addDirectedEdge(u, v, EdgeNode(dis, bikeSpeed, crowdDegree));
}

void Guider :: addUndirectedEdge
(int u, int v, double dis, double crowdDegree, bool bikeAccess) {
    addDirectedEdge(u, v, dis, crowdDegree, bikeAccess);
    addDirectedEdge(v, u, dis, crowdDegree, bikeAccess);
}
