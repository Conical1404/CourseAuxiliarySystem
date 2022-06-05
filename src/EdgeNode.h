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

struct WalkCalc {
    double operator () (const EdgeNode &x) const;
};

struct BikeCalc {
    double operator () (const EdgeNode &x) const;
};

struct DisCalc {
    double operator () (const EdgeNode &x) const;
};
