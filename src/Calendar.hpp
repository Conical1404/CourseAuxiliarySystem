#pragma once
#include "SegmentTree.hpp"
#include "String.hpp"

#define TESTPATH ""

class Calendar{
 private:
    int size;
    segmentTree Seg;
 public:
    Calendar();
    ~Calendar() {   }
    bool isEmpty();
    itinerary* newItinerary(Pair<Time, Time> tt,
                            String n, int c, int l);
    // 可以写一个周期性日程的重载
    bool insert(itinerary* x);
    void deleteItinerary(itinerary* x);
    void print();
    Vector<itinerary> show_week(int week);
    // 输入周数，把本周的所有日程返回，返回值是日程的Vector，返回前检查考试文件
};

Vector<itinerary> Calendar :: show_week(int week) {
    Vector<itinerary> ans;
    itinerary searchans[200];
    int asize = 0;
    int l = (week - 1) * 24;
    int r = week * 24;
    Seg.search_time_seg(1, 1, 3360, l, r, searchans, &asize);
    for (int i = 0; i < asize; i ++) ans.pushBack(searchans[i]);
    // 在此处根据文件路径读入考试文件即可，或者可以在前端实现
    // 具体在前端实现吧
    return ans;
}

Calendar :: Calendar() {
    size = 0;
}

bool Calendar :: isEmpty() {
    return size == 0;
}

bool Calendar :: insert(itinerary* x) {
    Pair<Time, Time> t = x->getTime();
    if (!Seg.insert(t, x)) return 0;  // 插入失败
    size++;
    return 1;
}

itinerary* Calendar :: newItinerary(Pair<Time, Time> tt,
                        String n, int c, int l) {
    printf("Ready to new:\n");
    itinerary* x = new itinerary;
    printf("Newed!\n");
    x->setLocation(c, l);
    printf("?1\n");
    x->setTime(tt);
    printf("?3\n");
    // x->setName(n);
    // printf("?2\n");
    if (x == NULL) return x;
    if (insert(x)) return x;
    printf("Oops!\n");
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
    printf("?Ready!\n");
    Seg.print(1);
    printf("printEnded!\n");
}
