#pragma once
#include <stdlib.h>
#include "Basic.hpp"
#include "String.hpp"
#include "Vector.hpp"
#include "Array.hpp"
#include "Pair.hpp"
#include "AVL.hpp"
#include "KMP.hpp"
#include "Sort.hpp"
#include "rbtree.hpp"
#include "Material.hpp"

class Test {  // 这是用来从文件读到课程里
 private:
    Pair<Time, Time> testTime;  // 包括一个开始时间和结束时间
    int cid;  // 对应课程的编号，并没有实际作用

 public:
    Test() {
        testTime.first = 0;
        testTime.second = 0;
    }
    Test(Time sTime, Time eTime) {
        testTime.first = sTime;
        testTime.second = eTime;
    }
    Pair<Time, Time> getTime() {
        return testTime;
    }
    Time getBeginTime() {
        return testTime.first;
    }
    Time getEndTime() {
        return testTime.second;
    }
    Test operator = (const Test &other) {
        testTime = other.testTime;
        cid = other.cid;
    }
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
    Course() {  }
    ~Course() { }
    Course(int id, String name, int loc, String cls,
            Pair<Time, Time> ctime, Pair<int, int> cweek) {
        courseid = id;
        courseName = name;
        classroom = cls;
        courseTime = ctime;
        courseWeek = cweek;
    }
    explicit Course(const Course &other) {
        courseid = other.courseid;
        courseName = other.courseName;
        location = other.location;
        classroom = other.classroom;
        courseTime = other.courseTime;
        courseWeek = other.courseWeek;
        test = other.test;
    }
    void addTest(Test t) {
        test = t;
    }
    void setTest(Time sTime, Time eTime) {
        test = Test(sTime, eTime);
    }
    int getId() {
        return courseid;
    }
    String getName() {  // 获得课程名称
        return courseName;
    }
    int getIntLoc() {  // 获得课程地点
        return location;
    }
    String getStringLoc() {  // 获得课程地点
        return classroom;
    }
    Pair<Time, Time> getTime() {  // 获得课程时间
        return courseTime;
    }
    Time getBeginTime() {
        return courseTime.first;
    }
    Time getEndTime() {
        return courseTime.second;
    }
    int getBeginWeek() {
        return courseWeek.first;
    }
    int getEndWeek() {
        return courseWeek.second;
    }
    Pair<int, int> getWeek() {
        return courseWeek;
    }
    Test getTest() {
        return test;
    }
    void addHomework(String name) {
        toBeHandIn.pushBack(name);
    }
    void handInHomework(String name) {
        int idx =  -1;
        for (int i = 0; i < toBeHandIn.getSize(); i++) {
            if (name == toBeHandIn[i]) {
                Basic :: swapElement(&toBeHandIn[i],
                &toBeHandIn[toBeHandIn.getSize() - 1]);
                toBeHandIn.popBack();
                handIn.pushBack(name);
                break;
            }
        }
    }
    Vector<String> getToBeHandInHomework() {
        return toBeHandIn;
    }
    Vector<String> getHandInHomework() {
        return handIn;
    }
};

struct Course_ptr {
    Course* ptr;
    bool operator < (Course_ptr other) {
        return ptr->getName() < other.ptr->getName();
    }
    bool operator == (Course_ptr other) {
        return ptr->getName() == other.ptr->getName();
    }
    Course_ptr operator = (const Course_ptr &other) {
        ptr = other.ptr;
        return *this;
    }
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

CourseSys :: CourseSys() {
    cnt = 0;
}

CourseSys :: ~CourseSys() {
    for (int i = 0; i < cnt; i++) {
        delete courseArray[i];
    }
}

void CourseSys :: addCourse(String name, String cls, int loc,
                            Time btime, Time etime, int bweek, int eweek) {
    Pair<Time, Time> ctime;
    Pair<int, int> cweek;
    ctime.first = btime;
    ctime.second = etime;
    cweek.first = bweek;
    cweek.second = eweek;
    Course* newCourse = new Course(cnt++, name, loc, cls, ctime, cweek);
    courseArray.pushBack(newCourse);
    Course_ptr nc;
    nc.ptr = newCourse;
    if (courseTree.exist(*courseTree.getRoot(), nc)) return;
    courseTree.insert(courseTree.getRoot(), nc);
}

Vector<String> CourseSys::getAllCourseNames() {
    Vector<String> courseName;
    for (int i = 0; i < courseArray.getSize(); i++) {
        courseName.pushBack(courseArray[i]->getName());
    }
    return courseName;
}

Course* CourseSys::getCourseByName(const String& name) {
    // 在AVL中搜索
    Pair<Time, Time> ctime;
    Pair<int, int> cweek;
    String cls;
    Course* srh = new Course(0, name, 0, cls, ctime, cweek);
    Course_ptr nc;
    nc.ptr = srh;
    Course_ptr ans;
    courseTree.exist(*courseTree.getRoot(), nc);
    ans = courseTree.search(*courseTree.getRoot(), nc);
    if (ans == nc) return NULL;
    return ans.ptr;
    // for(int i = 0; i < courseArray.getSize(); i++) {
    //     if(courseArray[i]->getName() == name)
    //         return courseArray[i];
    // }
    // return NULL;
}

Course* CourseSys::getCourseById(int id) {
    for (int i = 0; i < courseArray.getSize(); i++) {
        if (courseArray[i]->getId() == id)
            return courseArray[i];
    }
    return NULL;
}

Vector<Course*> CourseSys :: getAllCoursePtr() {
    return courseArray;
}

void CourseSys :: sortId(int l, int r) {
    Course* mid = courseArray[(l + r) >> 1];
    int i = l;
    int j = r;
    do {
        while (courseArray[i]->getId() < mid->getId()) i++;
        while (courseArray[j]->getId() > mid->getId()) j--;
        if (i <= j) {
            Basic :: swapElement<Course*>(&courseArray[i], &courseArray[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j) sortId(l, j);
    if (i < r) sortId(i, r);
}

void CourseSys :: sortName(int l, int r) {
    Course* mid = courseArray[(l + r) >> 1];
    int i = l;
    int j = r;
    do {
        while (courseArray[i]->getName() < mid->getName()) i++;
        while (courseArray[j]->getName() > mid->getName()) j--;
        if (i <= j) {
            Basic :: swapElement<Course*>(&courseArray[i], &courseArray[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j) sortName(l, j);
    if (i < r) sortName(i, r);
}
