#include "Material.hpp"

// using namespace std;

int main() {
    // char s[] = "String1";
    // char t[] = "String";
    // String ss; ss = s;
    // String tt; tt = t;
    // KMP kmp(ss, tt);
    // printf("%d\n", kmp.isExist());

    MaterialSys sys;
    char s[] = "NAME";
    char c[] = "COURSE";
    char p[] = "PATH";
    char s1[] = "BNAME";
    char sh[] = "AME";
    ByteArray md(8, 'x');
    ByteArray mm(8, 'y');
    String sname; sname = s;
    String sname1; sname1 = s1;
    String cname; cname = c;
    String pname; pname = p;
    String srh; srh = sh;
    Time btime; btime = 1000;
    Time btime1; btime1 = 1002;
    Material* a = new Material(1, cname, md, sname, pname, btime);
    Material* b = new Material(1, cname, mm, sname, pname, btime1);
    int f = sys.addMaterials(a);
    f = sys.addMaterials(b);
    printf("%d\n", f);
    printf("---\n");
    Material* x = NULL;
    x = sys.getMaterialByTime(btime);
    // printf("%d %d\n", x->isData(), x->isHomework());
    printf("%p %p\n", a, x);
    // x = sys.getCertainVersion(sname, 0);
    // printf("%p %p\n", &a, x);
    // x = sys.getCertainVersion(sname, 1);
    printf("%p %p\n", b, x);
    x = sys.getMaterialByTime(btime1);
    printf("%p %p\n", a, x);
    printf("%p %p\n", b, x);
    // x = sys.getMaterialByTime(btime);
    // printf("%p %p\n", &a, x);
    // printf("---\n");
    // MaterialPtr ptr;
    // ptr.ptr = &a;
    // MaterialPtr qtr;
    // qtr.ptr = &b;
    // printf("%d %d\n", qtr < ptr, qtr == ptr);
    return 0;
}
