#pragma once
#include "SegmentTree.h"
#include "String.h"

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
                            String n, int c, int l, int typ = 0);
    // 新建日程的话，使用这个接口可以新建 + 插入线段树
    // 这个函数用来插入真的很好用，周期性日程在外部加一个 for 循环修改 tt 即可
    bool insert(itinerary* x);  // 如果 itinerary 已经有的话，可以用这个
    void deleteItinerary(itinerary* x);
    void print();
    Vector<itinerary> show_week(int week);
    // 输入周数，把本周的所有日程返回，返回值是日程的Vector，返回前检查考试文件
    Vector<itinerary> show_hour(int time);
    // time = (week - 1) * 24 * 7 + (day - 1) * 24 + hour
};
