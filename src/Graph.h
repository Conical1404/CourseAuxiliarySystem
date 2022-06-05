#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "EdgeNode.h"
#include "DyadicArray.h"
#include "Vector.h"
#include "Array.h"
#include "Heap.h"
#include "Pair.h"

class Graph {
 private:
    Array<int> head;
    Vector<int> end, next;
    Vector<EdgeNode> weight;
    int vertexNum, edgeNum;

 public:
    Graph();
    explicit Graph(int n);
    ~Graph();
    void addDirectedEdge(int u, int v, EdgeNode w);
    void addUndirectedEdge(int u, int v, EdgeNode w);
    template<typename F>
    Vector<Pair<EdgeNode, int> > shortestPath
        (int startVertex, int endVertex, double *ans);
    template<typename F>
    Vector<Pair<EdgeNode, int> > shortestPath
        (int startVertex, int endVertex, Vector<int> midVertex, double *ans);
    template<typename F>
    Array<double> singleSourceShortestPath(int startVertex);
};
