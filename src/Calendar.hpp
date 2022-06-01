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
    // 新建日程的话，使用这个接口可以新建 + 插入线段树
    // 这个函数用来插入真的很好用，周期性日程在外部加一个 for 循环修改 tt 即可
    bool insert(itinerary* x);  // 如果 itinerary 已经有的话，可以用这个
    void deleteItinerary(itinerary* x);
    void print();
    Vector<itinerary> show_week(int week);
    // 输入周数，把本周的所有日程返回，返回值是日程的Vector，返回前检查考试文件
};

Vector<itinerary> Calendar :: show_week(int week) {
    Vector<itinerary> ans;
    itinerary searchans[200];
    int asize = 0;
    int l = (week - 1) * 24 * 7;
    int r = week * 24 * 7;
    // printf("Begin\n");
    Seg.search_time_seg(1, 1, 3360, l, r, searchans, &asize);
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
                        String n, int c, int l) {
    // printf("Ready to new:\n");
    itinerary* x = new itinerary;
    // printf("Newed!\n");
    x->setLocation(c, l);
    // printf("?1\n");
    x->setTime(tt);
    // printf("?3\n");
    x->setName(n);
    // printf("?2\n");
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
