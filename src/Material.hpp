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

class Material {  // 课程资料或作业
 private:
    bool homework;  // 是否为家庭作业
    String courseName;
    String name;  // 文件名
    ByteArray md5;  // md5
    Time updateTime;  // 更新时间
    String path;  // 存储路径
    Material* nextVersion;  // 版本指针

 public:
    Material() {
        nextVersion = NULL;
    }
    Material(bool h, String nme, \
            ByteArray m, String n, String p, Time u) {
        homework = h;
        courseName = nme;
        name = n;
        md5 = m;
        printf("M! %d %d\n", m.getSize(), md5.getSize());
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
        // printf("M!%s\n", name.data());
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
    // 获得最新版本
        Material* latest = this;
        while (latest->nextVersion != NULL) {
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
