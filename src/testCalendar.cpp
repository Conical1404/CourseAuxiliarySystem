#include "Calendar.hpp"

// using namespace std;

int main() {
    Calendar ca;
    for (int i = 1; i <= 50; i++) {
        Pair<Time, Time> t;
        String n;
        // char str[111];
        int c;
        int l;
        printf("%d: \n", i);
        scanf("%d%d%d", &t.first.week, &t.first.day, &t.first.hour);
        // printf("%d %d %d\n", t.first.week, t.first.day, t.first.hour);
        scanf("%d%d%d", &t.second.week, &t.second.day, &t.second.hour);
        // printf("%d %d %d\n", t.second.week, t.second.day, t.second.hour);
        // scanf("%s", str);
        // int len = strlen(str);
        // for(int i = 0; i < len; i++) n.pushBack(str[i]);
        scanf("%d%d", &c, &l);
        // printf("%s %d %d\n", n.data(), c ,l);
        printf("%d %d", c, l);
       // printf("?\n");
        ca.newItinerary(t, n, c, l);
        // printf("?\n");
        ca.print();
        printf("Round %d ended!\n", i);
    }
}
