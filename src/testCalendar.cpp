#include "Calendar.hpp"

// using namespace std;

int main() {
    Pair<Time, Time> p, q;
    p.first = 1000;
    p.second = 1002;
    char s[] = "Name";
    String str;
    str = s;
    itinerary a(p, str, 1, 1);
    q = a.getTime();
    printf("%d %d %d\n%d %d %d\n", q.first.week, q.first.day,
        q.first.hour, q.second.week, q.second.day, q.second.hour);
    printf("%s\n", a.getName().data());
    printf("%d %d\n", a.getCampus(), a.getLocation());
    return 0;
}
