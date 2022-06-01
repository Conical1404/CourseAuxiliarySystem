#pragma once
#include <cstdio>
#include "Activity.hpp"
#include "Basic.hpp"
#include "Pair.hpp"
#include "Vector.hpp"

class itinerary{
 private:
    // Pair<Time, Time> t;
    // String name;
    // int campus;
    // int location;
 public:
    Pair<Time, Time> t;
    String name;
    int campus;
    int location;
    itinerary();
    itinerary(Pair<Time, Time> tt, String n, int c, int l);
    itinerary(const itinerary &other);
    ~itinerary();
    Pair<Time, Time> getTime();
    void setTime(Pair<Time, Time> tt);
    String getName();
    void setName(String n);
    int getCampus();
    int getLocation();
    void setLocation(int c, int l);
    bool operator < (const itinerary &other) const;
    bool operator > (const itinerary &other) const;
    bool operator == (const itinerary &other) const;
    itinerary operator = (const itinerary &other);
    void print();
    // 日程显示函数，怎么打印出来好看
};

itinerary :: itinerary() {
    // printf("!!Init!!\n");
    campus = 0;
    location = 0;
}

itinerary :: ~itinerary() {
    // printf("!!released!!\n");
}

itinerary :: itinerary(Pair<Time, Time> tt, String n, int c, int l) {  // 1
    // printf("???\n");
    t = tt;
    // printf("1\n");
    name = n;
    // printf("2\n");
    campus = c;
    // printf("3\n");
    location = l;
    // printf("!!!\n");
}

itinerary :: itinerary(const itinerary &other) {
    t = other.t;
    name = other.name;
    campus = other.campus;
    location = other.location;
}

Pair<Time, Time> itinerary :: getTime() {  // 1
    return t;
}

void itinerary :: setTime(Pair<Time, Time> tt) {  // 1
    t = tt;
}

String itinerary :: getName() {  // 1
    return name;
}

void itinerary :: setName(String n) {  // 1
    // printf("Ready to RE!\n");
    name = n;
    // printf("Not RE.\n");
}

int itinerary :: getCampus() {  // 1
    return campus;
}

int itinerary :: getLocation() {  // 1
    return location;
}

void itinerary :: setLocation(int c, int l) {  // 1
    campus = c;
    location = l;
}

bool itinerary :: operator < (const itinerary &other) const {  // 1
    return t < other.t;
}

bool itinerary :: operator > (const itinerary &other) const {  // 1
    return t > other.t;
}

bool itinerary :: operator == (const itinerary &other) const {  // 1
    return t == other.t;
}

itinerary itinerary :: operator = (const itinerary &other) {
    t = other.t;
    name = other.name;
    campus = other.campus;
    location = other.location;
    // printf("! ");
    // print();
    return *this;
}

void itinerary :: print() {  // 1
    printf("Begin time: %d %d %d End time: %d %d %d ", t.first.week,
            t.first.day, t.first.hour, t.second.week,
            t.second.day, t.second.hour);
    // printf("Name: %s Location: %d %d\n", name.data(), campus, location);
    printf("Location: %d %d\n", campus, location);
}

class segmentTree {
// 此线段树对时间区间的操作为左闭右闭，即活动开始时间也不能同结束时间相同
 private:
    int lazy[13445];
    struct SegNode{
        bool value;
        bool purity;
        itinerary* point;
    };
    SegNode timeSegment[13445];  // 一学期小时数(20*7*24)*4 true代表未被占用
    void pushUp(int index) {
        timeSegment[index].value =
            timeSegment[index << 1].value && timeSegment[index << 1 | 1].value;
        if (timeSegment[index << 1].point &&
            timeSegment[index << 1 | 1].point &&
        timeSegment[index << 1].point == timeSegment[index << 1 | 1].point) {
            timeSegment[index].point = timeSegment[index << 1].point;
            timeSegment[index].purity = 1;
        } else {
            timeSegment[index].purity = 0;
            timeSegment[index].point = NULL;
        }
    }
    void pushDown(int index) {
        if (lazy[index] != 0) {
            lazy[index << 1] = lazy[index];
            lazy[index << 1 | 1] = lazy[index];
        }
        if (lazy[index] == 1) {
            timeSegment[index << 1].value = true;
            timeSegment[index << 1 | 1].value = true;
            timeSegment[index << 1].point = NULL;
            timeSegment[index << 1 | 1].point = NULL;
            lazy[index] = 0;
        }
        if (lazy[index] == -1) {
            timeSegment[index << 1].value = false;
            timeSegment[index << 1 | 1].value = false;
            timeSegment[index << 1].point = timeSegment[index].point;
            timeSegment[index << 1 | 1].point = timeSegment[index].point;
            lazy[index] = 0;
        }
    }
    // start-end:要查询的区间 curLeft-curRight:
    // 当前递归到的区间边界 index:当前时间段对应的数组下标
    bool query(int start, int end, int curLeft, int curRight, int index) {
        if (start <= curLeft && end >= curRight) {
            return timeSegment[index].value;
        } else {
            pushDown(index);
            bool res = true;
            int mid = curLeft + ((curRight - curLeft) >> 1);
            if (start <= mid)
                res = res && query(start, end, curLeft, mid, index << 1);
            if (end > mid)
                res =
                    res && query(start, end, mid + 1, curRight, index << 1 | 1);
            return res;
        }
    }
    // start-end:要查询的区间 curLeft-curRight:当前递归到的区间边界
    // state:更新后的状态 index:当前时间段对应的数组下标
    void update(int start, int end, bool state, int curLeft, int curRight,
                int index) {
        if (start <= curLeft && end >= curRight) {
            lazy[index] = state ? 1 : -1;
            timeSegment[index].value = state ? 1 : 0;
            timeSegment[index].purity = state ? 0 : 1;
        } else {
            pushDown(index);
            int mid = curLeft + ((curRight - curLeft) >> 1);
            if (start <= mid)
                update(start, end, state, curLeft, mid, index << 1);
            if (end > mid)
                update(start, end, state, mid + 1, curRight, index << 1 | 1);
            pushUp(index);
        }
    }
    void update(int start, int end, bool state, int curLeft, int curRight,
                int index, itinerary* p) {
        // printf("%d %d %d\n", index, curLeft, curRight);
        if (start <= curLeft && end >= curRight) {
            lazy[index] = state ? 1 : -1;
            timeSegment[index].value = state ? 1 : 0;
            timeSegment[index].point = state ? NULL : p;
            timeSegment[index].purity = state ? 0 : 1;
        } else {
            pushDown(index);
            int mid = curLeft + ((curRight - curLeft) >> 1);
            if (start <= mid)
                update(start, end, state, curLeft, mid, index << 1, p);
            if (end > mid)
                update(start, end, state, mid + 1, curRight, index << 1 | 1, p);
            pushUp(index);
        }
    }

 public:
    segmentTree() {
        for (int i = 0; i < 13445; i++) {
            timeSegment[i].value = true;
            timeSegment[i].purity = 0;
            timeSegment[i].point = NULL;
            lazy[i] = 0;
        }
    }
    segmentTree(const segmentTree& other) {
        for (int i = 0; i < 13445; i++) {
            timeSegment[i] = other.timeSegment[i];
            lazy[i] = other.lazy[i];
        }
    }

    bool insert(Pair<Time, Time> t, itinerary* p) {
        int start = t.first.calHours();
        int end = t.second.calHours();
        // printf("%d %d\n", start, end);
        if (!query(start, end, 1, 3360, 1)) {  // 3360 = 20*7*24(一周的分钟数)
            // printf("*1\n");
            return false;
        } else {
            // printf("Ready to insert!\n");
            update(start, end, false, 1, 3360, 1, p);
            return true;
        }
    }
    void remove(Pair<Time, Time> t) {
        int start = t.first.calHours();
        int end = t.second.calHours();
        update(start, end, true, 1, 3360, 1);
    }
    void print(int index) {
    // 这个输出函数不能判重，只适合看一下线段树里面有什么
        // for(int i = 1; i < 20001; i++)
        //     printf("%d %d\n", i, timeSegment[i].purity);
        // printf("index: %d purity: %d\n", index, timeSegment[index].purity);
        // printf("%d ", index);
        if (timeSegment[index].purity) {
            itinerary* p = timeSegment[index].point;
            p->print();
            // printf("Ended!\n");
        } else {
            if ((index << 1) > 13440) return;
            print(index << 1);
            if ((index << 1 | 1) > 13440) return;
            print(index << 1 | 1);
        }
    }
    void search_time_seg(int index, int ul, int ur, int l,
                        int r, itinerary* ans, int *asize) {
        if (ur < l || ul > r) return;
        // printf("%d %d %d %d %d\n", index, ul, ur, l, r);
        if (timeSegment[index].point) {
            // printf("!!! %d %d %d %d %d\n", index, ul, ur, l, r);
            if ((*asize) == 0 ||
                !(ans[(*asize) - 1] == *timeSegment[index].point)) {
                // printf("Begin to add\n");
                ans[(*asize)] = *timeSegment[index].point;
                // (*timeSegment[index].point).print();
                // ans[(*asize)].print();
                (*asize) = (*asize) + 1;
                // printf("Ended!\n");
            }
            return;
        } else {
            if (ul == ur) return;
            int mid = ul+ ((ur - ul) >> 1);
            // printf("? %d %d %d %d %d %d", ul, ur, ul, mid, mid + 1, ur);
            if ((index << 1) > 13440) return;
            search_time_seg(index << 1, ul, mid,
                            l, r, ans, asize);
            if ((index << 1 | 1) > 13440) return;
            search_time_seg(index << 1 | 1, mid + 1, ur,
                            l, r, ans, asize);
        }
    }
};
