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

class Material {  // 课程资料或作业
 private:
    bool homework;
    String courseName;
    String name;  // 文件名
    ByteArray md5;  // md5
    Time updateTime;  // 更新时间
    String path;  // 存储路径
    Material* nextVersion;

 public:
    Material() {
        nextVersion = NULL;
    }
    Material(bool h, String name, \
            ByteArray m, String n, String p, Time u) {
        homework = h;
        courseName = name;
        name = n;
        md5 = m;
        path = p;
        updateTime = u;
        nextVersion = NULL;
    }
    explicit Material(const Material& other) {
        homework = other.homework;
        courseName = other.courseName;
        name = other.name;
        md5 = other.md5;
        path = other.path;
        updateTime = other.updateTime;
        nextVersion = other.nextVersion;
    }
    bool isHomework() {
        return homework;
    }
    bool isData() {
        return !homework;
    }
    String getCourseName() {
        return courseName;
    }
    String getName() {
        return name;
    }
    ByteArray getMd5() {
        return md5;
    }
    Time getTime() {
        return updateTime;
    }
    String getpath() {
        return path;
    }
    Material* getLatestVersion() {
        Material* latest = this;
        while(latest->nextVersion != NULL) {
            latest = latest->nextVersion;
        }
        return latest;
    }
    void setNextVersion(Material* m) {
        nextVersion = m;
    }
    Material* getNextVersion() {
        return nextVersion;
    }
};

struct MaterialPtr {
    Material* ptr;
    bool operator < (Material* other) {
        ByteArray md5 = ptr->getMd5();
        ByteArray oMd5 = other->getMd5();
        for(int i = 0; i < md5.getSize(); i++){
            if(md5[i] > oMd5[i])
                return false;
        }
        return true;
    }
    bool operator == (Material* other){
        ByteArray md5 = ptr->getMd5();
        ByteArray oMd5 = other->getMd5();
        for(int i = 0; i < md5.getSize(); i++){
            if(md5[i] != oMd5[i])
                return false;
        }
        return true;
    }
};

class MaterialSys {
 private:
    Vector<Material*> materials;
 public:
    MaterialSys() {    };
    ~MaterialSys() {
        for(int i = 0; i < materials.getSize(); i++){
            delete materials[i];
        }
    }
    bool addMaterials(Material* m) {
        for(int i = 0; i < materials.getSize(); i++) {
            if(materials[i]->getName() == m->getName()){
                Material* latest;
                latest = materials[i]->getLatestVersion();
                latest->setNextVersion(m);
                return true;
            }
        }
        materials.pushBack(m);
        return true;
    }
    Material* getHomeworkByName(const String& name) {
        Material* homework = NULL;
        for(int i = 0; i < materials.getSize(); i++) {
            if(materials[i]->getName() == name
                && materials[i]->isHomework()) {
                homework = materials[i]->getLatestVersion();
            }
        }
        return homework;
    }
    Material* getDataByName(const String& name) {
        Material* data = NULL;
        for(int i = 0; i < materials.getSize(); i++) {
            if(materials[i]->getName() == name
                && materials[i]->isData()) {
                data = materials[i]->getLatestVersion();
            }
        }
        return data;
    }
    Vector<Material*> search(const String& name) {
        Vector<Material*> result;
        for(int i = 0; i < materials.getSize(); i++) {
            KMP kmp(materials[i]->getName(), name);
            if(kmp.isExist()) {
                Material* tmp = materials[i]->getLatestVersion();
                result.pushBack(tmp);
            }
        }
        return result;
    }
    Material* getCertainVersion(const String& name,int t) {
        Material* m = NULL;
        for(int i = 0; i < materials.getSize(); i++) {
            if(materials[i]->getName() == name) {
                m = materials[i];
            }
        }
        while(t--){
            m = m->getNextVersion();
        }
        return m;
    }
};

class Test {  // 这是用来从文件读到课程里
 private:
    Pair<Time, Time> testTime;  // 包括一个开始时间和结束时间
    int cid;  // 对应课程的编号，并没有实际作用

 public:
    Test() {
        testTime.first = 0;
        testTime.second = 0;
    }
    Test(Time sTime, Time eTime){
        testTime.first = sTime;
        testTime.second =eTime;
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
    Test operator = (const Test other) {
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
    void handIn(String name) {
        int idx =  -1;
        for(int i = 0; i < toBeHandIn.getSize(); i++) {
            if(name == toBeHandIn[i]) {
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
    Course* getCourseByName(const String& name) const;
    Course* getCourseById(int id);
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
    for(int i = 0; i < courseArray.getSize(); i++) {
        courseName.pushBack(courseArray[i]->getName());
    }
    return courseName;
}

Course* CourseSys::getCourseByName(const String& name) const {
    for(int i = 0; i < courseArray.getSize(); i++) {
        if(courseArray[i]->getName() == name)
            return courseArray[i];
    }
    return NULL;
}

Course* CourseSys::getCourseById (int id) {
    for(int i = 0; i < courseArray.getSize(); i++) {
        if(courseArray[i]->getId() == id)
            return courseArray[i];
    }
    return NULL;
}