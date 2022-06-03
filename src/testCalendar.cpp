#include "Calendar.hpp"

// using namespace std;

int main() {
    Pair<Time, Time> p;
    p.first = 1000;
    p.second = 1002;
    Calendar a;
    Vector<itinerary> ans;
    char s[] = "NAME";
    String str;
    str = s;
    itinerary* b = a.newItinerary(p, str, 1, 1);
    p.first = 1003;
    p.second = 1004;
    itinerary* c = a.newItinerary(p, str, 2, 2);
    printf("***\n");
    ans = a.show_week(6);
    printf("?");
    printf("%d \n", ans.getSize());
    for (int i = 0; i < ans.getSize(); i++)
        ans[i].print();
    printf("?");
    printf("***\n");
    ans = a.show_hour(1003);
    printf("?");
    printf("%d \n", ans.getSize());
    for (int i = 0; i < ans.getSize(); i++)
        ans[i].print();
    printf("?");
    return 0;
}
