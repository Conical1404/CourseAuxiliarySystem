#pragma once
#include "Activity.hpp"
#include "Basic.hpp"
#include "Pair.hpp"
#include "Vector.hpp"

class segmentTree {
 //此线段树对时间区间的操作为左闭右闭，即活动开始时间也不能同结束时间相同
 private:
    bool timeSegment[13445];  //一学期小时数(20*7*24)*4 true代表未被占用
    short lazy[13445];
    Vector<Pair<Time,Time>> arrangement;
    void pushUp(int index) {
        timeSegment[index] =
            timeSegment[index << 1] && timeSegment[index << 1 | 1];
    }
    void pushDown(int index) {
        if (lazy[index] != 0) {
            lazy[index << 1] = lazy[index];
            lazy[index << 1 | 1] = lazy[index];
        }
        if (lazy[index] == 1) {
            timeSegment[index << 1] = true;
            timeSegment[index << 1 | 1] = true;
            lazy[index] = 0;
        }
        if (lazy[index] == -1) {
            timeSegment[index << 1] = false;
            timeSegment[index << 1 | 1] = false;
            lazy[index] = 0;
        }
    }
    // start-end:要查询的区间 curLeft-curRight:当前递归到的区间边界 index:当前时间段对应的数组下标
    bool query(int start, int end, int curLeft, int curRight, int index) {
        if (start <= curLeft && end >= curRight)
            return timeSegment[index];
        else {
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
            timeSegment[index] = state ? 1 : -1;
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

 public:
    segmentTree() {
        for (int i = 0; i < 13440; i++) {
            timeSegment[i] = true;
            lazy[i] = 0;
        }
    }
    segmentTree(segmentTree& other) {
        for (int i = 0; i < 13440; i++) {
            timeSegment[i] = other.timeSegment[i];
            lazy[i] = other.lazy[i];
        }
    }

    bool insert(Pair<Time, Time> t) {
        int start = t.first.calHours();
        int end = t.second.calHours();
        if (!query(start, end, 1, 3360, 1))  // 3360 = 20*7*24(一周的分钟数)
            return false;
        else {
            update(start, end, false, 1, 3360, 1);
            return true;
        }
    }
    void remove(Pair<Time, Time> t) {
        int start = t.first.calHours();
        int end = t.second.calHours();
        update(start, end, true, 1, 3360, 1);
    }
};
