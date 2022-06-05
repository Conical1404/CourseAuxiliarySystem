#include "src/Course.h"

Test::Test() {
    testTime.first = 0;
    testTime.second = 0;
}

Test::Test(Time sTime, Time eTime, int id) {
    testTime.first = sTime;
    testTime.second = eTime;
    cid = id;
}

Pair<Time, Time> Test::getTime() {
    return testTime;
}

Time Test::getBeginTime() {
    return testTime.first;
}

Time Test::getEndTime() {
    return testTime.second;
}

int Test::getcid() {
    return cid;
}

Test& Test::operator = (const Test &other) {
    testTime = other.testTime;
    cid = other.cid;
    return *this;
}

Course::Course() {  }

Course::~Course() { }

Course::Course(int id, String name, int loc, String cls,
        Pair<Time, Time> ctime, Pair<int, int> cweek) {
    courseid = id;
    courseName = name;
    classroom = cls;
    courseTime = ctime;
    courseWeek = cweek;
}

Course::Course(const Course &other) {
    courseid = other.courseid;
    courseName = other.courseName;
    location = other.location;
    classroom = other.classroom;
    courseTime = other.courseTime;
    courseWeek = other.courseWeek;
    test = other.test;
    handIn = other.handIn;
    toBeHandIn = other.toBeHandIn;
}

void Course::addTest(Test t) {
    test = t;
}

void Course::setTest(Time sTime, Time eTime) {
    test = Test(sTime, eTime, courseid);
}

int Course::getId() {
    return courseid;
}

String Course::getName() {  // 获得课程名称
    return courseName;
}

int Course::getIntLoc() {  // 获得课程地点
    return location;
}

String Course::getStringLoc() {  // 获得课程地点
    return classroom;
}

Pair<Time, Time> Course::getTime() {  // 获得课程时间
    return courseTime;
}

Time Course::getBeginTime() {
    return courseTime.first;
}

Time Course::getEndTime() {
    return courseTime.second;
}

int Course::getBeginWeek() {
    return courseWeek.first;
}

int Course::getEndWeek() {
    return courseWeek.second;
}

Pair<int, int> Course::getWeek() {
    return courseWeek;
}

Test Course::getTest() {
    return test;
}

void Course::addHomework(String name) {
    toBeHandIn.pushBack(name);
}

void Course::handInHomework(String name) {
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

Vector<String> Course::getToBeHandInHomework() {
    return toBeHandIn;
}

Vector<String> Course::getHandInHomework() {
    return handIn;
}

Course& Course::operator = (const Course &other) {
    courseid = other.courseid;
    courseName = other.courseName;
    location = other.location;
    classroom = other.classroom;
    courseTime = other.courseTime;
    courseWeek = other.courseWeek;
    test = other.test;
    handIn = other.handIn;
    toBeHandIn = other.toBeHandIn;
    return *this;
}

bool Course_ptr::operator < (Course_ptr other) {
    return ptr->getName() < other.ptr->getName();
}

bool Course_ptr::operator == (Course_ptr other) {
    return ptr->getName() == other.ptr->getName();
}

Course_ptr& Course_ptr::operator = (const Course_ptr &other) {
    ptr = other.ptr;
    return *this;
}

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
