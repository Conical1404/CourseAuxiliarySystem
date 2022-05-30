#pragma once
#include <stdlib.h>
#include "Basic.hpp"
#include "String.hpp"
#include "Vector.hpp"
#include "Array.hpp"
#include "Pair.hpp"
#include "AVL.hpp"

class Material {  // 课程资料或作业
 private:
    String name;  // 文件名
    ByteArray md5;  // md5
    Time updatetime;  // 更新时间
    String path;  // 存储路径

 public:
    Material() {    }
    Material(ByteArray m, String n, String p, Time u) {
        name = n;
        md5 = m;
        path = p;
        updatetime = u;
    }
    String getname() {
        return name;
    }
    ByteArray getmd5() {
        return md5;
    }
    Time gettime() {
        return updatetime;
    }
    String getpath() {
        return path;
    }
};

class Test {  // 这是用来从文件读到课程里
 private:
    Pair<Time, Time> testtime;  // 包括一个开始时间和结束时间
    int cid;  // 对应课程的编号，并没有实际作用

 public:
    Test() {
        testtime.first = 0;
        testtime.second = 0;
    }
    Pair<Time, Time> gettime() {
        return testtime;
    }
    Time get_begin_time() {
        return testtime.first;
    }
    Time get_end_time() {
        return testtime.second;
    }
};

class Course {
 private:
    int courseid;  // 课程编号，是用来方便查找和调用的
    // cid 可以根据需要删除
    String coursename;  // 课程名
    int location;       // 建筑ID，课程地点的int描述
    String classroom;  // 课程地点的字符串描述
    Pair<Time, Time> coursetime;  // 课程时间，包括开始和结束
    Pair<int, int> courseweek;  // 课程周数，包括开始和结束
    // 这里放一棵维护资料的平衡树的指针
    Test test;  // 这里放考试信息

 public:
    String getname() {  // 获得课程名称
        return coursename;
    }
    int get_int_loc() {  // 获得课程地点
        return location;
    }
    String get_string_loc() {  // 获得课程地点
        return classroom;
    }
    Pair<Time, Time> gettime() {  // 获得课程时间
        return coursetime;
    }
    Time get_begin_time() {
        return coursetime.first;
    }
    Time get_end_time() {
        return coursetime.second;
    }
    int get_begin_week() {
        return courseweek.first;
    }
    int get_end_week() {
        return courseweek.second;
    }
    Pair<int, int> getweek() {
        return courseweek;
    }
    Test get_test() {
        return test;
    }
};
