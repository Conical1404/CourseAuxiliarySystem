#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "Vector.hpp"
#include "Heap.hpp"
#include "Pair.hpp"

template<class T>
class Graph {
 private:
    Vector<int> head, end, next;
    Vector<T> weight;
    int vertexNum, edgeNum;

 public:
    Graph();
    explicit Graph(int n);
    ~Graph();
    void addDirectedEdge(int u, int v, T w);
    void addUndirectedEdge(int u, int v, T w);
    T Dijstra(int startVertex, int endVertex, T inf, T zero);
};

template<class T>
Graph<T> :: Graph() : vertexNum(0), edgeNum(0) {
    head.pushBack(0);
    end.pushBack(0);
    next.pushBack(0);
    weight.pushBack(*(new T));
}

template<class T>
Graph<T> :: Graph(int n) : vertexNum(n), edgeNum(0) {
    for (int index = 0; index <= n; index++)
        head.pushBack(0);
    end.pushBack(0);
    next.pushBack(0);
    weight.pushBack(*(new T));
}

template<class T>
Graph<T> :: ~Graph() { }

template<class T>
void Graph<T> :: addDirectedEdge(int u, int v, T w) {
    ++edgeNum;
    next.pushBack(head[u]);
    end.pushBack(v);
    weight.pushBack(w);
    head[u] = edgeNum;
}

template<class T>
void Graph<T> :: addUndirectedEdge(int u, int v, T w) {
    addDirectedEdge(u, v, w);
    addDirectedEdge(v, u, w);
}

template<class T>
T Graph<T> :: Dijstra(int startVertex, int endVertex, T inf, T zero) {
    Vector<T> dis(vertexNum + 1, inf);
    Heap<Pair<T, int>, Greater<Pair<T, int> > > Q;
    Q.push(Pair<T, int> (zero, startVertex));
    dis[startVertex] = zero;
    int tot = 0;
    while (!Q.isEmpty()) {
        auto tmp = Q.top();
        Q.pop();
        if (dis[tmp.second] != tmp.first)
            continue;
        // fprintf(stderr, "%d %d %d\n", ++tot, tmp.second, (int) tmp.first);
        for (int index = head[tmp.second]; index != 0; index = next[index])
            if (dis[end[index]] > weight[index] + tmp.first) {
                fprintf(stderr, "%d %d\n", tmp.second, end[index]);
                dis[end[index]] = weight[index] + tmp.first;
                Q.push(Pair<T, int> (dis[end[index]], end[index]));
            }
    }
    fprintf(stderr, "-------------\n");
    return dis[endVertex];
}
