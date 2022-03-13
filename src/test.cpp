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
    return 0;
}
