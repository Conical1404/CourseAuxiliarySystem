#pragma once
#include <stdlib.h>
#include "Basic.h"
#include "String.h"
#include "Vector.h"
#include "Array.h"
#include "Pair.h"
#include "AVL.h"
#include "KMP.h"
#include "Material.h"
#include "src/rbtree.h"

class Test {  // 这是用来从文件读到课程里
// 已测试
 private:
    Pair<Time, Time> testTime;  // 包括一个开始时间和结束时间
    int cid;  // 对应课程的编号，并没有实际作用

 public:
    Test();
    Test(Time sTime, Time eTime, int id);
    Pair<Time, Time> getTime();
    Time getBeginTime();
    Time getEndTime();
    int getcid();
    Test& operator = (const Test &other);
};

class Course {
 private:
    int courseid;  // 课程编号，是用来方便查找和调用的
    // cid 可以根据需要删除
    String courseName;  // 课程名
    int location;       // 建筑ID，课程地点的int描述
    String classroom;  // 课程地点的字符串描述
    Pair<Time, Time> courseTime;  // 课程时间，包括开始和结束
    Pair<int, int> courseWeek;  // 课程周数，包括开始和结束
    Test test;  // 这里放考试信息
    Vector<String> handIn;
    Vector<String> toBeHandIn;

 public:
    Course();
    ~Course();
    Course(int id, String name, int loc, String cls,
            Pair<Time, Time> ctime, Pair<int, int> cweek);
    explicit Course(const Course &other);
    void addTest(Test t);
    void setTest(Time sTime, Time eTime);
    int getId();
    String getName();
    int getIntLoc();
    String getStringLoc();
    Pair<Time, Time> getTime();
    Time getBeginTime();
    Time getEndTime();
    int getBeginWeek();
    int getEndWeek();
    Pair<int, int> getWeek();
    Test getTest();
    void addHomework(String name);
    void handInHomework(String name);
    Vector<String> getToBeHandInHomework();
    Vector<String> getHandInHomework();
    Course& operator = (const Course &other);
};

struct Course_ptr {
    Course* ptr;
    bool operator < (Course_ptr other);
    bool operator == (Course_ptr other);
    Course_ptr& operator = (const Course_ptr &other);
    // 这里可以再重载其他运算符
};

class CourseSys {
 private:
    AVL<Course_ptr> courseTree;
    int cnt;
    Vector<Course*> courseArray;

 public:
    CourseSys();
    ~CourseSys();

    void addCourse(String name, String cls, int loc,
                    Time btime, Time etime, int bweek, int eweek);
    Vector<String> getAllCourseNames();
    // Course* getCourseByName(const String& name) const;
    Course* getCourseByName(const String& name);
    Course* getCourseById(int id);
    Vector<Course*> getAllCoursePtr();
    void sortId(int l, int r);
    void sortName(int l, int r);
};
