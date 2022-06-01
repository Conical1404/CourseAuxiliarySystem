#pragma once
#include <stdlib.h>
#include <stdio.h>

#define walkSpeed 1.5
#define bikeSpeed 5

struct EdgeNode {
    double dis;
    double crowdDegree;
    bool isBike;
    EdgeNode();
    EdgeNode(double d, double c, bool f);
    inline bool operator < (const EdgeNode & other) const;
};

EdgeNode :: EdgeNode() {
    dis = 0, isBike = 0, crowdDegree = 0;
}

EdgeNode :: EdgeNode(double d, double c, bool f) {
    dis = d, isBike = f, crowdDegree = c;
}

struct WalkCalc {
    double operator () (const EdgeNode &x) const {
        return walkSpeed * x.crowdDegree < 1e-9 ?
            1e18 : x.dis / (walkSpeed * x.crowdDegree);
    }
};

struct BikeCalc {
    double operator () (const EdgeNode &x) const {
        return x.isBike ? (bikeSpeed * x.crowdDegree < 1e-9 ?
            1e18 : x.dis / (bikeSpeed * x.crowdDegree)) : 1e18;
    }
};

struct DisCalc {
    double operator () (const EdgeNode &x) const {
        return x.dis;
    }
};
