#pragma once
#include <stdlib.h>
#include "Basic.hpp"
#include "String.hpp"
#include "Vector.hpp"
#include "Array.hpp"
#include "Pair.hpp"
#include "AVL.hpp"

class Course {
 private:
    String coursename;
    int location;       // 建筑ID
    String classroom;
    Pair<Time, Time> coursetime;
    Pair<int, int> courseweek;

    class Material {
     private:
        String name;
        ByteArray md5;
        Time updatetime;
        String path;

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

    class Test {
     private:
        Pair<Time, Time> testtime;

     public:
        Pair<Time, Time> gettime() {
            return testtime;
        }
    } test;

 public:
    String getname() {
        return coursename;
    }
    int getloc() {
        return location;
    }
    Pair<Time, Time> gettime() {
        return coursetime;
    }
    Pair<int, int> getweek() {
        return courseweek;
    }
    Pair<Time, Time> gettesttime() {
        test.gettime();
    }
};
