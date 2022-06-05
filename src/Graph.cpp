#include "src/Graph.h"

Graph :: Graph() : vertexNum(0), edgeNum(0), head() {
    end.pushBack(0);
    next.pushBack(0);
    weight.pushBack(*(new EdgeNode));
}

Graph :: Graph(int n) : vertexNum(n), edgeNum(0), head(n + 1, 0) {
    end.pushBack(0);
    next.pushBack(0);
    weight.pushBack(*(new EdgeNode));
}

Graph :: ~Graph() { }

void Graph :: addDirectedEdge(int u, int v, EdgeNode w) {
    ++edgeNum;
    next.pushBack(head[u]);
    end.pushBack(v);
    weight.pushBack(w);
    head[u] = edgeNum;
}

void Graph :: addUndirectedEdge(int u, int v, EdgeNode w) {
    addDirectedEdge(u, v, w);
    addDirectedEdge(v, u, w);
}

template<typename F>
Vector<Pair<EdgeNode, int> > Graph ::
shortestPath(int startVertex, int endVertex, double *ans) {
    Array<double> dis(vertexNum + 1, 1e18);
    Array<int> pre(vertexNum + 1, 0);
    Array<EdgeNode> preEdge(vertexNum + 1, infEdge);
    Heap<Pair<double, int>, Greater<Pair<double, int> > > Q;
    Vector<Pair<EdgeNode, int> > path;
    Q.push(Pair<double, int> (0, startVertex));
    dis[startVertex] = 0;
    int tot = 0;
    while (!Q.isEmpty()) {
        auto tmp = Q.top();
        Q.pop();
        if (dis[tmp.second] != tmp.first)
            continue;
        // fprintf(stderr, "%d %d %d\n", ++tot, tmp.second, (int) tmp.first);
        for (int index = head[tmp.second]; index != 0; index = next[index])
            if (dis[end[index]] > F()(weight[index]) + F()(tmp.first)) {
                // fprintf(stderr, "%d %d\n", tmp.second, end[index]);
                dis[end[index]] = F()(weight[index]) + F()(tmp.first);
                pre[end[index]] = tmp.second;
                preEdge[end[index]] = weight[index];
                Q.push(Pair<double, int> (dis[end[index]], end[index]));
            }
    }
    *ans = dis[endVertex];
    for (int vertex = endVertex; vertex != startVertex; vertex = pre[vertex])
        path.pushBack(Pair<EdgeNode, int> (preEdge[vertex], vertex));
    path.reverse();
    return path;
}

template<typename F>
Array<double> Graph :: singleSourceShortestPath(int startVertex) {
    Array<double> dis(vertexNum + 1, 1e18);
    Heap<Pair<double, int>, Greater<Pair<double, int> > > Q;
    Q.push(Pair<double, int> (0, startVertex));
    dis[startVertex] = 0;
    int tot = 0;
    while (!Q.isEmpty()) {
        auto tmp = Q.top();
        Q.pop();
        if (dis[tmp.second] != tmp.first)
            continue;
        for (int index = head[tmp.second]; index != 0; index = next[index])
            if (dis[end[index]] > F()(weight[index]) + F()(tmp.first)) {
                dis[end[index]] = F()(weight[index]) + F()(tmp.first);
                Q.push(Pair<double, int> (dis[end[index]], end[index]));
            }
    }
    return dis;
}

template<typename F>
Vector<Pair<EdgeNode, int> > Graph :: shortestPath(
    int startVertex,
    int endVertex,
    Vector<int> midVertex,
    double *ans
) {
    // T F[maxState][21];
    int num = midVertex.getSize();
    int maxVertex = num + 1;
    const int maxState = (1 << num) | 1;
    DyadicArray<double> f(maxState, maxVertex, 1e18);
    DyadicArray<int> pre(maxState, maxVertex, 0);
    Array<double> startDis = singleSourceShortestPath<F>(startVertex);
    Array<Array<double> > dis(num);
    for (int index = 0; index < num; index++) {
        dis[index] = singleSourceShortestPath<F>(midVertex[index]);
        f[1 << index][index] = startDis[midVertex[index]];
    }
    for (int state = 0; state < (1 << num); state++)
        for (int index = 0; index < num; index++) {
            if (~(state >> index) & 1) continue;
            double w = f[state][index];
            if (w > 1e9) continue;
            for (int vertex = 0; vertex < num; vertex++) {
                if ((state >> vertex) & 1) continue;
                int newState = state | (1 << vertex);
                if (f[newState][vertex] > w + dis[index][midVertex[vertex]]) {
                    f[newState][vertex] = w + dis[index][midVertex[vertex]];
                    pre[newState][vertex] = index;
                }
            }
        }
    double ansDis = 1e18;
    Array<int> nextVertex(vertexNum + 1);
    Vector<Pair<EdgeNode, int> > path;
    int tmp;
    for (int vertex = 0; vertex < num; vertex++)
        if (ansDis > f[(1 << num) - 1][vertex] + dis[vertex][endVertex]) {
            ansDis = f[(1 << num) - 1][vertex] + dis[vertex][endVertex];
            tmp = vertex;
        }
    *ans = ansDis;
    nextVertex[midVertex[tmp]] = endVertex;
    int state = (1 << num) - 1;
    while (state != (1 << tmp)) {
        int p = pre[state][tmp];
        nextVertex[midVertex[p]] = midVertex[tmp];
        state ^= (1 << tmp);
        tmp = p;
    }
    path = shortestPath(startVertex, midVertex[tmp]);
    for (tmp = midVertex[tmp]; tmp != endVertex; tmp = nextVertex[tmp])
        path = path + shortestPath(tmp, nextVertex[tmp]);
    return path;
}
