#pragma once
#include <stdlib.h>
#include "Basic.h"
#include "String.h"
#include "Vector.h"
#include "Array.h"
#include "Pair.h"
#include "AVL.h"
#include "KMP.h"
#include "src/rbtree.h"

class Material {  // 课程资料或作业
 private:
    bool homework;  // 是否为家庭作业
    String courseName;
    String name;  // 文件名
    ByteArray md5;  // md5
    Time updateTime;  // 更新时间
    String path;  // 存储路径
    Material* nextVersion = NULL;  // 版本指针

 public:
    Material();
    Material(bool h, String nme, \
            ByteArray m, String n, String p, Time u);
    ~Material();
    explicit Material(const Material& other);
    bool isHomework();
    bool isData();
    String getCourseName();
    String getName();
    ByteArray getMd5();
    Time getTime();
    String getpath();
    Material* getLatestVersion();
    void setNextVersion(Material* m);
    Material* getNextVersion();
    Material& operator = (const Material& other);
};

struct MaterialPtr {
    Material* ptr;
    bool operator < (Material* other);
    bool operator < (MaterialPtr other);
    bool operator == (Material* other);
    bool operator == (MaterialPtr other);
};

class MaterialSys {
 private:
    Vector<Material*> materials;
    RBTree<MaterialPtr> materialTree;
    RBTree<Spair<String, int>> nameTree;
    RBTree<Spair<Time, IntPair>> timeTree;
    Vector<Material*> mForSort;

 public:
    MaterialSys();
    ~MaterialSys();
    bool addMaterials(Material* m);
    Material* getMaterialByName(const String& name);
    Material* getMaterialByTime(const Time& t);
    Vector<Material*> search(const String& name);
    Material* getCertainVersion(const String& name, int t);
    void sortByTime(int l, int r);
    void sortByName(int l, int r);
    Vector<Material*> getAllMaterial();
};
