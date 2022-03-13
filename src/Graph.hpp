#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "DyadicArray.hpp"
#include "Vector.hpp"
#include "Array.hpp"
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
    Vector<Pair<T, int> > shortestPath(int startVertex, \
                                       int endVertex, T inf, T zero);
    Vector<T> singleSourceShortestPath(int startVertex, T inf, T zero);
    Vector<Pair<T, int> > shortestPath(int startVertex, int endVertex, \
                                       T inf, T zero, Vector<int> midVertex);
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
Vector<Pair<T, int> > Graph<T> ::
shortestPath(int startVertex, int endVertex, T inf, T zero) {
    Vector<T> dis(vertexNum + 1, inf);
    Vector<int> pre(vertexNum + 1, 0);
    Vector<T> preEdge(vertexNum + 1, inf);
    Heap<Pair<T, int>, Greater<Pair<T, int> > > Q;
    Vector<Pair<T, int> > path;
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
                // fprintf(stderr, "%d %d\n", tmp.second, end[index]);
                dis[end[index]] = weight[index] + tmp.first;
                pre[end[index]] = tmp.second;
                preEdge[end[index]] = weight[index];
                Q.push(Pair<T, int> (dis[end[index]], end[index]));
            }
    }
    for (int vertex = endVertex; vertex != startVertex; vertex = pre[vertex])
        path.pushBack(Pair<T, int> (preEdge[vertex], vertex));
    path.reverse();
    return path;
}

template<class T>
Vector<T> Graph<T> :: singleSourceShortestPath(int startVertex, T inf, T zero) {
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
        for (int index = head[tmp.second]; index != 0; index = next[index])
            if (dis[end[index]] > weight[index] + tmp.first) {
                dis[end[index]] = weight[index] + tmp.first;
                Q.push(Pair<T, int> (dis[end[index]], end[index]));
            }
    }
    return dis;
}

template<class T>
Vector<Pair<T, int> > Graph<T> ::
shortestPath(int startVertex, int endVertex, \
             T inf, T zero, Vector<int> midVertex) {
    const int maxVertex = 21;
    const int maxState = (1 << 20) | 1;
    // T F[maxState][21];
    DyadicArray<T> f(maxState, maxVertex, inf);
    DyadicArray<int> pre(maxState, maxVertex, 0);
    int num = midVertex.getSize();
    Vector<T> startDis = singleSourceShortestPath(startVertex, inf, zero);
    Array<Vector<T> > dis(num);
    for (int index = 0; index < num; index++) {
        dis[index] = singleSourceShortestPath(midVertex[index], inf, zero);
        f[1 << index][index] = startDis[midVertex[index]];
    }
    for (int state = 0; state < (1 << num); state++)
        for (int index = 0; index < num; index++) {
            if (~(state >> index) & 1) continue;
            int w = f[state][index];
            if (w == inf) continue;
            for (int vertex = 0; vertex < num; vertex++) {
                if ((state >> vertex) & 1) continue;
                int newState = state | (1 << vertex);
                if (f[newState][vertex] > w + dis[index][midVertex[vertex]]) {
                    f[newState][vertex] = w + dis[index][midVertex[vertex]];
                    pre[newState][vertex] = index;
                }
            }
        }
    T ansDis = inf;
    Array<int> nextVertex(vertexNum);
    Vector<Pair<T, int> > path;
    int tmp;
    for (int vertex = 0; vertex < num; vertex++)
        if (ansDis > f[(1 << num) - 1][vertex] + dis[vertex][endVertex]) {
            ansDis = f[(1 << num) - 1][vertex] + dis[vertex][endVertex];
            tmp = vertex;
        }
    nextVertex[midVertex[tmp]] = endVertex;
    int state = (1 << num) - 1;
    while (state != (1 << tmp)) {
        int p = pre[state][tmp];
        nextVertex[midVertex[p]] = midVertex[tmp];
        state ^= (1 << tmp);
        tmp = p;
    }
    path = shortestPath(startVertex, midVertex[tmp], inf, zero);
    for (tmp = midVertex[tmp]; tmp != endVertex; tmp = nextVertex[tmp])
        path = path + shortestPath(tmp, nextVertex[tmp], inf, zero);
    return path;
}
