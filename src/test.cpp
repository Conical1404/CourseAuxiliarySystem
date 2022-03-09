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
    for (int i = 1; i <= n; i++)
        printf("%d%c", G.Dijstra(1, i, 0x3f3f3f3f, 0), " \n" [i == n]);
    return 0;
}
