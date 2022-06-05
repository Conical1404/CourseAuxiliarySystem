#pragma once

#include <cstdio>
#include "Activity.h"
#include "Basic.h"
#include "Pair.h"
#include "Vector.h"

class itinerary{
 private:
    Pair<Time, Time> t;  // 起止时间
    String name;  // 名称
    int campus;  // 校区
    int location;  // 地点
    int type;  // 类型，个人，集体，其他 = 0

 public:
    // Pair<Time, Time> t;
    // String name;
    // int campus;
    // int location;
    itinerary();  // 构造函数
    itinerary(Pair<Time, Time> tt, String n, int c, int l, int typ = 0);
    // 构造函数
    itinerary(const itinerary &other);  // 拷贝构造函数
    ~itinerary();  // 析构函数
    Pair<Time, Time> getTime();  // 获得起止时间
    void setTime(Pair<Time, Time> tt);  // 设置起止时间
    String getName();  // 获得名称
    void setName(String n);  // 设置名称
    int getCampus();  // 获得校区编号
    int getLocation();  // 获得地点
    int getType();  // 获得类型
    void setLocation(int c, int l);  // 设置校区地点
    void setType(int t);  // 设置类型
    bool operator < (const itinerary &other) const;
    bool operator > (const itinerary &other) const;
    bool operator == (const itinerary &other) const;
    // 重载比大小符号，日程大小取决于起止时间的大小
    itinerary operator = (const itinerary &other);
    // 重载赋值
    void print();
    // 日程显示函数，在命令行输出一个日程的基本信息
};

class segmentTree {
// 此线段树对时间区间的操作为左闭右闭，即活动开始时间也不能同结束时间相同
 private:
    int lazy[35105];
    struct SegNode {
        bool value;
        bool purity;
        itinerary* point;
    };
    SegNode timeSegment[35105];  // 一学期小时数(20*7*24)*4 true代表未被占用
    void pushUp(int index);
    void pushDown(int index);
    // start-end:要查询的区间 curLeft-curRight:
    // 当前递归到的区间边界 index:当前时间段对应的数组下标
    bool query(int start, int end, int curLeft, int curRight, int index);
    // start-end:要查询的区间 curLeft-curRight:当前递归到的区间边界
    // state:更新后的状态 index:当前时间段对应的数组下标
    void update(int start, int end, bool state, int curLeft, int curRight,
                int index);
    void update(int start, int end, bool state, int curLeft, int curRight,
                int index, itinerary* p);

 public:
    segmentTree();
    segmentTree(const segmentTree& other);
    bool insert(Pair<Time, Time> t, itinerary* p);
    void remove(Pair<Time, Time> t);
    void print(int index);
    void search_time_seg(int index, int ul, int ur, int l,
                        int r, itinerary* ans, int *asize);
};
