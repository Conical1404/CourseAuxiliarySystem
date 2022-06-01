#pragma once
#include <stdio.h>
#include "Campus.hpp"
#include "EdgeNode.hpp"
#include "Vector.hpp"
#include "Basic.hpp"

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

Guider::Guider() { }

Guider::Guider(int n, int m1, int m2) :
campusMap[0](m1), campusMap[1](m2) {
    campusNum = n;
    crossEdgeNum = 0;
}

void Guider::addEdge(int x, int u, int v, double d, double c, bool f) {
    campusMap[x].addUndirectedEdge(u, v, d, c, f);
}

void Guider::addEdge(CrossTimeNode w) {
    crossEdge.pushBack(w);
    crossEdgeNum++;
}

double Guider::shortestPath(
    int startCampus,
    int startVertex,
    int endCampus,
    int endVertex,
    double curTime,
    int type
) {
    double ans = 1e18;
    if (startCampus == endCampus)  {
        Route tmpx = campusMap[startCampus].shortestPath(
            startVertex,
            endVertex,
            &ans,
            type);
        double busTime = -1;
        return ans;
    }
    Array<double> dis;
    dis = campusMap[startCampus].singleSourceShortestPath(startVertex, type);
    int tot = 0;
    for (int index = 0; index < crossEdgeNum; index++) {
        CrossTimeNode e;
        e = crossEdge[index];
        if (e.e.x != startCampus || e.e.y != endCampus)
            continue;
        double t = dis[e.e.u] + curTime;
        if (e.timeTable[e.m - 1] < t)
            continue;
        int l = 0, r = e.m - 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (e.timeTable[mid] < t)
                r = mid + 1;
            else
                l = mid - 1;
        }
        ++tot;
        Route tmpx, tmpy;
        double ans1 = 1e18, ans2 = 1e18;
        tmpx = campusMap[startCampus].
            shortestPath(startVertex, e.e.u, &ans1, type);
        tmpy = campusMap[startCampus].
            shortestPath(e.e.v, endVertex, &ans2, type);
        double res = 1e18;
        if (type == 0)
            res = ans1 + ans2 + e.e.dis;
        double busTime = e.timeTable[l + 1];
        return ans;
    }
}

double Guider::shortestPath(
    int startCampus,
    int startVertex,
    int endCampus,
    int endVertex,
    double curTime,
    Vector<int> midVertex1,
    Vector<int> midVertex2,
    int type
) {
    double ans = 1e18;
    if (startCampus == endCampus)  {
        Route tmpx = campusMap[startCampus].shortestPath(
            startVertex,
            endVertex,
            midVertex1,
            &ans,
            type);
        double busTime = -1;
        return ans;
    }
    int tot = 0;
    for (int index = 0; index < crossEdgeNum; index++) {
        CrossTimeNode e;
        e = crossEdge[index];
        if (e.e.x != startCampus || e.e.y != endCampus)
            continue;
        Route tmpx, tmpy;
        CrossEdge tmpz;
        double ans1, ans2;
        tmpx = campusMap[startCampus].shortestPath(
            startVertex,
            e.e.u,
            midVertex1,
            &ans1,
            type);
        double t = ans1 + curTime;
        if (e.timeTable[e.m - 1] < t)
            continue;
        int l = 0, r = e.m - 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (e.timeTable[mid] < t)
                r = mid + 1;
            else
                l = mid - 1;
        }
        ++tot;
        printf("Campus %d:\n", startCampus);
        printf("%d ", startVertex);
        for (int index = 0; index < tmpx.getSize(); index++)
            printf("-> %d", tmpx[index].second);
        printf("\n");
        printf("From campus %d to campus %d:\n", e.e.x, e.e.y);
        printf("Route:%d Time:%lf\n", index, e.timeTable[l + 1]);
        tmpy = campusMap[endCampus].shortestPath(
            e.e.v,
            endVertex,
            midVertex2,
            &ans2,
            type);
        printf("Campus %d:\n", endCampus);
        printf("%d ", e.e.v);
        for (int index = 0; index < tmpy.getSize(); index++)
            printf("-> %d", tmpy[index].second);
        printf("\n");
    }
}
