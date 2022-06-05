#pragma once
#include <stdio.h>
#include "Campus.h"
#include "EdgeNode.h"
#include "Vector.h"
#include "Basic.h"

typedef Vector<Pair<EdgeNode, int> > Route;

struct CrossEdge {
    int x, y, u, v;
    double dis, time;
};

struct CrossTimeNode {
    CrossEdge e;
    int m;
    Vector<double> timeTable;
};

class Guider {
 private:
    int campusNum, crossEdgeNum;
    Vector<CrossTimeNode> crossEdge;
    Campus campusMap[2];

 public:
    Guider();
    Guider(int n, int m1, int m2);
    void addEdge(int x, int u, int v, double d, double c, bool f);
    void addEdge(CrossTimeNode w);
    double shortestPath(
        int startCampus,
        int startVertex,
        int endCampus,
        int endVertex,
        double curTime,
        int type);
    double shortestPath(
        int startCampus,
        int startVertex,
        int endCampus,
        int endVertex,
        double curTime,
        Vector<int> midVertex1,
        Vector<int> midVertex2,
        int type);
};
