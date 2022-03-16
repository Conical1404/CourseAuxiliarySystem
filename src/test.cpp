#include <stdio.h>
#include "Graph.hpp"
#include "Heap.hpp"
#include "Pair.hpp"

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    Graph<int> G(n);
    for (int u, v, w; m--; ) {
        scanf("%d%d%d", &u, &v, &w);
        G.addDirectedEdge(u, v, w);
    }
    Array<int> dis = G.singleSourceShortestPath(1, 0x3f3f3f3f, 0);
    for (int i = 1; i <= n; i++)
        printf("%d%c", dis[i], " \n" [i == n]);
    Vector<int> midVex;
    midVex.pushBack(2);
    auto path = G.shortestPath(1, 6, 0x3f3f3f3f, 0, midVex);
    for (int i = 0; i < path.getSize(); i++) {
        printf("%d %d\n", path[i].first, path[i].second);
    }
    return 0;
}
