#include "src/Material.h"


Material::Material() {
    nextVersion = NULL;
}

Material::Material(bool h, String nme, \
        ByteArray m, String n, String p, Time u) {
    homework = h;
    courseName = nme;
    name = n;
    md5 = m;
    // printf("M! %d %d\n", m.getSize(), md5.getSize());
    path = p;
    updateTime = u;
    nextVersion = NULL;
}

Material::~Material() {
    // printf("M! \n");
}

Material::Material(const Material& other) {
    homework = other.homework;
    courseName = other.courseName;
    name = other.name;
    md5 = other.md5;
    path = other.path;
    updateTime = other.updateTime;
    nextVersion = other.nextVersion;
}
bool Material::isHomework() {
    return homework;
}
bool Material::isData() {
    return !homework;
}
String Material::getCourseName() {
    return courseName;
}
String Material::getName() {
    // printf("M!%s\n", name.data());
    return name;
}
ByteArray Material::getMd5() {
    return md5;
}
Time Material::getTime() {
    return updateTime;
}
String Material::getpath() {
    return path;
}
Material* Material::getLatestVersion() {
// 获得最新版本
    Material* latest = this;
    while (latest->nextVersion != NULL) {
        latest = latest->nextVersion;
    }
    return latest;
}
void Material::setNextVersion(Material* m) {
    nextVersion = m;
}
Material* Material::getNextVersion() {
    return nextVersion;
}
Material& Material::operator = (const Material& other) {
    homework = other.homework;
    courseName = other.courseName;
    name = other.name;
    md5 = other.md5;
    path = other.path;
    updateTime = other.updateTime;
    nextVersion = other.nextVersion;
    return *this;
}


bool MaterialPtr::operator < (Material* other) {
    ByteArray md5 = ptr->getMd5();
    ByteArray oMd5 = other->getMd5();
    for (int i = 0; i < md5.getSize(); i++) {
        if (md5[i] >= oMd5[i])
            return false;
    }
    return true;
}

bool MaterialPtr::operator < (MaterialPtr other) {
    ByteArray md5 = ptr->getMd5();
    ByteArray oMd5 = other.ptr->getMd5();
    for (int i = 0; i < md5.getSize(); i++) {
        if (md5[i] >= oMd5[i])
            return false;
    }
    return true;
}

bool MaterialPtr::operator == (Material* other) {
    ByteArray md5 = ptr->getMd5();
    ByteArray oMd5 = other->getMd5();
    for (int i = 0; i < md5.getSize(); i++) {
        if (md5[i] != oMd5[i])
            return false;
    }
    return true;
}

bool MaterialPtr::operator == (MaterialPtr other) {
    ByteArray md5 = ptr->getMd5();
    ByteArray oMd5 = other.ptr->getMd5();
    for (int i = 0; i < md5.getSize(); i++) {
        if (md5[i] != oMd5[i])
            return false;
    }
    return true;
}

MaterialSys::MaterialSys() { }

MaterialSys::~MaterialSys() {
// 这个析构函数 RE 了，但是我不会调
    // printf("M! %d\n", materials.getSize());
    for (int i = 0; i < materials.getSize(); i++) {
        Material* u = materials[i];
        // printf("M! !\n");
        while (u) {
            Material* v = u;
            u = u->getNextVersion();
            delete v;
            // printf("M! x\n");
        }
        // printf("M! ?\n");
    }
    // printf("M! ---\n");
// 要注意 Material new 的时候务必确保不存在未初始化的野指针
// 还有声明 Material 的时候必须 new
}

bool MaterialSys::addMaterials(Material* m) {
// 这里运行完有一个非常可疑的停顿，我不确定是不是RE了
// 好像是析构函数的问题
    MaterialPtr km;
    km.ptr = m;
    if (materialTree.find(km)) return false;
    // 判断是否是重复文件
    Spair<String, int> p;
    p.first = m->getName();
    p.second = 0;
    Spair<Time, IntPair> tt;
    tt.first = m->getTime();
    // printf("!M !%d\n", m->getTime().calHours());
    int cnt = 0;
    if (nameTree.find(p)) {
        // printf("M! 1\n");
        int index = nameTree.search(p).second;
        Material* latest = materials[index];
        while (latest->getNextVersion() != NULL) {
            latest = latest->getNextVersion();
            cnt++;
        }
        latest->setNextVersion(m);
        materialTree.insert(km);
        tt.second.first = index;
        tt.second.second = cnt + 1;
        timeTree.insert(tt);
        return true;
    }
    // printf("M! 2\n");
    materials.pushBack(m);
    mForSort.pushBack(m);
    p.second = materials.getSize() - 1;
    materialTree.insert(km);
    nameTree.insert(p);
    tt.second.first = p.second;
    tt.second.second = 0;
    timeTree.insert(tt);
    // printf("!M *%d %d\n", timeTree.find(tt), tt.first.calHours());
    // printf("M! 3\n");
    return true;
}

Material* MaterialSys::getMaterialByName(const String& name) {
// 已测试
    Material* homework = NULL;
    Spair<String, int> p;
    p.first = name;
    p.second = 0;
    if (!nameTree.find(p)) return NULL;
    int index = nameTree.search(p).second;
    homework = materials[index]->getLatestVersion();
    return homework;
}

Material* MaterialSys::getMaterialByTime(const Time& t) {
// 重写
    Material* m = NULL;
    Spair<Time, IntPair> tt;
    tt.first = t;
    // printf("!M !%d %d\n", tt.first.calHours(), timeTree.find(tt));
    if (!timeTree.find(tt)) return NULL;
    tt = timeTree.search(tt);
    int index = tt.second.first;
    int index2 = tt.second.second;
    // printf("!M ?%d %d\n", index, index2);
    m = materials[index];
    while (index2--) {
        m = m->getNextVersion();
    }
    // printf("!M %p\n", m);
    return m;
}

Vector<Material*> MaterialSys::search(const String& name) {
// 已测试
    Vector<Material*> result;
    for (int i = 0; i < materials.getSize(); i++) {
        KMP kmp(materials[i]->getName(), name);
        if (kmp.isExist()) {
            Material* tmp = materials[i]->getLatestVersion();
            result.pushBack(tmp);
        }
    }
    return result;
}
Material* MaterialSys::getCertainVersion(const String& name, int t) {
// 版本编号从 0 开始计
// 已测试
    Material* m = NULL;
    Spair<String, int> p;
    p.first = name;
    p.second = 0;
    if (!nameTree.find(p)) return NULL;
    int index = nameTree.search(p).second;
    m = materials[index];
    while (t--) {
        if (m) m = m->getNextVersion();
    }
    return m;
}  // 取得特定版本

void MaterialSys::sortByTime(int l, int r) {
// 已测试
    Material* mid = mForSort[(l + r) >> 1];
    int i = l;
    int j = r;
    do {
        while (mForSort[i]->getLatestVersion()->getTime()
                < mid->getLatestVersion()->getTime()) i++;
        while (mForSort[j]->getLatestVersion()->getTime()
                > mid->getLatestVersion()->getTime()) j--;
        if (i <= j) {
            Basic :: swapElement(&mForSort[i], &mForSort[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j) sortByTime(l, j);
    if (i < r) sortByTime(i, r);
}

void MaterialSys::sortByName(int l, int r) {
// 已测试
    Material* mid = mForSort[(l + r) >> 1];
    int i = l;
    int j = r;
    do {
        while (mForSort[i]->getName() < mid->getName()) i++;
        while (mForSort[j]->getName() > mid->getName()) j--;
        if (i <= j) {
            Basic :: swapElement(&mForSort[i], &mForSort[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j) sortByName(l, j);
    if (i < r) sortByName(i, r);
}

Vector<Material*> MaterialSys::getAllMaterial() {
// 已测试
    return mForSort;
}
