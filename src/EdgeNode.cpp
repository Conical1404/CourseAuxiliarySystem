#include "src/EdgeNode.h"

EdgeNode :: EdgeNode() {
    dis = 0, isBike = 0, crowdDegree = 0;
}

EdgeNode :: EdgeNode(double d, double c, bool f) {
    dis = d, isBike = f, crowdDegree = c;
}

double WalkCalc::operator() (const EdgeNode &x) const {
    return walkSpeed * x.crowdDegree < 1e-9 ?
        1e18 : x.dis / (walkSpeed * x.crowdDegree);
}

double BikeCalc::operator() (const EdgeNode &x) const {
    return x.isBike ? (bikeSpeed * x.crowdDegree < 1e-9 ?
        1e18 : x.dis / (bikeSpeed * x.crowdDegree)) : 1e18;
}

double DisCalc::operator() (const EdgeNode &x) const {
    return x.dis;
}
