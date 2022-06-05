#include "Calendar.h"


Vector<itinerary> Calendar :: show_week(int week) {
    Vector<itinerary> ans;
    itinerary searchans[200];
    int asize = 0;
    int l = (week - 1) * 24 * 7;
    int r = week * 24 * 7;
    // printf("Begin\n");
    Seg.search_time_seg(1, 1, 8760, l, r, searchans, &asize);
    // printf("2\n");
    // printf("anssize = %d\n", asize);
    // for (int i = 0; i < asize; i ++) {
    //     searchans[i].print();
    //     printf("out Point : %p\n", &searchans[i]);
    // }
    // printf("?\n");
    // searchans[0].print();
    // ans.pushBack(searchans[0]);
    for (int i = 0; i < asize; i ++) ans.pushBack(searchans[i]);
    // printf("?\n");
    // printf("%d %d\n", asize, ans.getSize());
    // 在此处根据文件路径读入考试文件即可，或者可以在前端实现
    return ans;
}

Vector<itinerary> Calendar :: show_hour(int time) {
    Vector<itinerary> ans;
    itinerary searchans[200];
    int asize = 0;
    int l = time;
    int r = time;
    // printf("Begin\n");
    Seg.search_time_seg(1, 1, 8760, l, r, searchans, &asize);
    for (int i = 0; i < asize; i ++) ans.pushBack(searchans[i]);
    // printf("?\n");
    // printf("%d %d\n", asize, ans.getSize());
    // 在此处根据文件路径读入考试文件即可，或者可以在前端实现
    return ans;
}

Calendar :: Calendar() {
    size = 0;
}

bool Calendar :: isEmpty() {
    return size == 0;
}

bool Calendar :: insert(itinerary* x) {
    // printf("?1\n");
    Pair<Time, Time> t = x->getTime();
    // printf("%d %d\n", t.first.calHours(), t.second.calHours());
    // printf("?2\n");
    if (!Seg.insert(t, x)) return 0;  // 插入失败
    // printf("?3\n");
    size++;
    return 1;
}

itinerary* Calendar :: newItinerary(Pair<Time, Time> tt,
                        String n, int c, int l, int typ) {
    // printf("Ready to new:\n");
    itinerary* x = new itinerary;
    // printf("Newed!\n");
    x->setLocation(c, l);
    // printf("?1\n");
    x->setTime(tt);
    // printf("?3\n");
    x->setName(n);
    // printf("?2\n");
    x->setType(typ);
    if (x == NULL) return x;
    if (insert(x)) return x;
    // printf("Oops!\n");
    delete x;
    x = NULL;
    return x;
}

void Calendar :: deleteItinerary(itinerary* x) {
    Seg.remove(x->getTime());
    size--;
    delete x;
    x = NULL;
}

void Calendar :: print() {
    // printf("?Ready!\n");
    Seg.print(1);
    // printf("printEnded!\n");
    // 这个 print 函数不提供去重
}
